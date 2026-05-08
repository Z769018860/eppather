import subprocess
import glob
import re
import pandas as pd
import os
import shutil
import statistics
import argparse

def run_with_timeout(cmd, timeout=100):
    print(f"      [run] CMD: {' '.join(cmd)}")
    try:
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        try:
            out, err = proc.communicate(timeout=timeout)
            returncode = proc.returncode
        except subprocess.TimeoutExpired:
            proc.kill()
            out, err = proc.communicate()
            print("        [timeout] Walltime exceeded, process killed.")
            return out, err, 'Timeout'
        return out, err, returncode
    except Exception as e:
        print(f"        [exception] {e}")
        return '', str(e), 'Exception'

def error_status(output, error, retcode, time_tag):
    err_combined = (output or "") + (error or "")
    if "Segmentation fault (core dumped)" in err_combined or "core dumped" in err_combined:
        return True, 'core dumped'
    if retcode == 'Timeout':
        return True, 'timeout'
    if re.search(time_tag, output) is None:
        return True, 'no_time_output'
    return False, ''

def extract_greedy(output):
    mems_match = re.search(r"MEMS:\s*(-?\d+)", output)
    mems_val = mems_match.group(1) if mems_match else ''
    time_match = re.search(r"\[DP TIME COST\]: ([\d\.]+) seconds", output)
    time_val = time_match.group(1) if time_match else ''
    return mems_val, time_val

def extract_time(output, tag):
    match = re.search(tag, output)
    return match.group(1) if match else ''

def to_float(x):
    try:
        return float(x)
    except:
        return float('nan')

def short_err(err, length=200):
    if not err:
        return ''
    lines = err.strip().splitlines()
    if len(lines) == 0:
        return ''
    head = lines[0]
    more = f" ... ({len(lines)} lines)" if len(lines) > 1 else ""
    text = (head + more)
    if len(text) > length:
        text = text[:length] + "..."
    return text

def get_folder(filename, folders):
    for folder in folders:
        if filename.startswith(folder + os.sep) or filename.startswith(folder + '/'):
            return folder
    return 'other'

def summarize_and_save(results, folders, summary_path, overview_path):
    df = pd.DataFrame(results, columns=[
        'filename', 'source_path', 'folder',
        'dfs_time', 'dfs_max_mems', 'dfs_min_mems',
        'greedy_time', 'greedy_mems', 'greedy_path',
        'f_error', 'g_error', 'success', 'mems_equal'
    ])
    df.to_csv(summary_path, index=False)
    print(f"  [CSV] 已保存至 {summary_path}")

    total = len(df)
    success_count = int(df['success'].sum()) if total else 0
    mems_equal_count = int(df['mems_equal'].sum()) if total else 0
    success_rate = (success_count / total) if total else 0.0
    equal_rate = (mems_equal_count / success_count) if success_count else 0.0

    print("\n==== 统计结果 ====")
    print(f"  总文件数: {total}")
    print(f"  成功: {success_count} ({success_rate:.2%})")
    print(f"  mems相同准确率: {mems_equal_count}/{success_count} = {equal_rate:.2%} (仅统计成功样本)")

    if total:
        df['_dfs_t'] = df['dfs_time'].apply(to_float)
        df['_dp_t']  = df['greedy_time'].apply(to_float)

        valid = df[(df['success'] == True) &
                   (df['_dfs_t'] > 0.0) &
                   (df['_dp_t'] > 0.0)]
        speedups = (valid['_dfs_t'] / valid['_dp_t']).tolist()

        if speedups:
            avg_speedup = statistics.mean(speedups)
            med_speedup = statistics.median(speedups)
            print(f"  DP 相对 DFS 加速比（仅成功且时间有效样本）:")
            print(f"    样本数: {len(speedups)}")
            print(f"    平均: {avg_speedup:.2f}x")
            print(f"    中位数: {med_speedup:.2f}x")
        else:
            print("  DP 相对 DFS 加速比：无可统计样本（可能时间缺失或为0）。")

    print("\n==== 分文件夹成功率 ====")
    folder_rows = []
    for folder in folders:
        folder_df = df[df['folder'] == folder]
        n = len(folder_df)
        n_success = int(folder_df['success'].sum()) if n else 0
        rate = (n_success / n) if n else 0.0
        print(f"  {folder}: {n_success}/{n} ({rate:.2%})")
        folder_rows.append({
            "folder": folder,
            "total": n,
            "success": n_success,
            "success_rate": rate
        })

    overview_df = pd.DataFrame(folder_rows)
    overview_df.loc[len(overview_df)] = {
        "folder": "ALL",
        "total": total,
        "success": success_count,
        "success_rate": success_rate
    }
    overview_df.to_csv(overview_path, index=False)
    print(f"  [CSV] 聚合统计已保存至 {overview_path}")

def parse_args():
    parser = argparse.ArgumentParser(description="批量执行 DFS/Greedy 并汇总结果")
    parser.add_argument("--folders", nargs="+", default=["output_true2", "output_complete2"],
                        help="要扫描的 .c 文件目录列表")
    parser.add_argument("--summary", default="result_summary.csv",
                        help="逐文件统计输出 CSV")
    parser.add_argument("--overview", default="result_overview.csv",
                        help="聚合统计输出 CSV")
    return parser.parse_args()

def main():
    args = parse_args()
    print("==== 扫描目标文件夹 ====")
    folders = args.folders
    c_files = []
    seen = set()
    for folder in folders:
        files = sorted(glob.glob(os.path.join(folder, "*.c")))
        print(f"  {folder}: 找到 {len(files)} 个 .c 文件")
        for file in files:
            norm = os.path.normpath(file)
            if norm not in seen:
                c_files.append(file)
                seen.add(norm)
    print(f"== 共 {len(c_files)} 个 C 文件将被处理 ==\n")

    if not c_files:
        print("[终止] 未在指定文件夹下发现任何 .c 文件。")
        return

    # 分类结果目录（不再移动输入目录文件）
    os.makedirs("output_analyzed_complete", exist_ok=True)
    os.makedirs("output_analyzed_true", exist_ok=True)

    results = []
    try:
        for idx, cfile in enumerate(c_files):
            print(f"\n====== 文件 {idx+1}/{len(c_files)}: {cfile} ======")
            entry = {}

            entry['source_path'] = cfile
            entry['filename'] = os.path.basename(cfile)
            folder = get_folder(cfile, folders)
            entry['folder'] = folder

            print(f"  [1/2] 执行 DFS 分析: ../cnip -q {cfile}")
            cmd_f = ["../cnip", "-q", cfile]
            out_f, err_f, ret_f = run_with_timeout(cmd_f, timeout=180)
            dfs_error, dfs_reason = error_status(
                out_f, err_f, ret_f, r"\[DFS TIME COST\]: ([\d\.]+) seconds"
            )
            fail_flag = False
            if dfs_error:
                print(f"    [失败] DFS 阶段错误类型: {dfs_reason}")
                entry.update({
                    'dfs_time': 'error',
                    'dfs_max_mems': 'error',
                    'dfs_min_mems': 'error',
                    'f_error': dfs_reason
                })
                fail_flag = True
            else:
                entry['dfs_time'] = extract_time(out_f, r"\[DFS TIME COST\]: ([\d\.]+) seconds")
                dfs_max = re.search(r"\[DFS MAX MEMS\]:\s*(-?\d+)", out_f)
                dfs_min = re.search(r"\[DFS MIN MEMS\]:\s*(-?\d+)", out_f)
                entry['dfs_max_mems'] = dfs_max.group(1) if dfs_max else ''
                entry['dfs_min_mems'] = dfs_min.group(1) if dfs_min else ''
                entry['f_error'] = ''
                print(f"    [OK] DFS time: {entry['dfs_time']} | max mems: {entry['dfs_max_mems']} | min mems: {entry['dfs_min_mems']}")

            print(f"  [2/2] 执行 Greedy 路径分析: ../cnip -g {cfile}")
            cmd_g = ["../cnip", "-g", cfile]
            out_g, err_g, ret_g = run_with_timeout(cmd_g, timeout=180)
            greedy_error, greedy_reason = error_status(
                out_g, err_g, ret_g, r"\[DP TIME COST\]: ([\d\.]+) seconds"
            )
            if greedy_error:
                print(f"    [失败] Greedy 阶段错误类型: {greedy_reason}")
                entry.update({
                    'greedy_time': 'error',
                    'greedy_mems': 'error',
                    'greedy_path': '',
                    'g_error': greedy_reason
                })
                fail_flag = True
            else:
                greedy_mems, greedy_time = extract_greedy(out_g)
                entry['greedy_mems'] = greedy_mems
                entry['greedy_time'] = greedy_time
                entry['g_error'] = ''
                path_match = re.search(r"\[TEST INPUT PATH EXPR\]:\s*([\s\S]+?)(?=\n*\[DP TIME COST\]:|\Z)", out_g)
                entry['greedy_path'] = path_match.group(1).strip() if path_match else ""
                print(f"    [OK] Greedy time: {greedy_time} | mems: {greedy_mems}")

            entry['success'] = not fail_flag
            entry['mems_equal'] = (entry.get('dfs_max_mems', None) == entry.get('greedy_mems', None)
                                   and entry.get('dfs_max_mems', '') not in ('', 'error'))

            print(f"  [总结] 本文件执行 {'成功' if entry['success'] else '失败'} | mems是否一致: {entry['mems_equal']}")

            # 复制到分析结果目录，保留源数据不变
            try:
                mems = entry.get('greedy_mems', '')
                need_copy = (mems not in ('', 'error') and mems not in ('0', '-1'))

                if need_copy:
                    dst_complete = os.path.join("output_analyzed_complete", os.path.basename(cfile))
                    shutil.copy2(cfile, dst_complete)
                    print(f"    [已复制] -> output_analyzed_complete/{os.path.basename(cfile)}")

                    if entry['mems_equal']:
                        dst_true = os.path.join("output_analyzed_true", os.path.basename(cfile))
                        shutil.copy2(cfile, dst_true)
                        print(f"    [已复制] -> output_analyzed_true/{os.path.basename(cfile)}")
                else:
                    print("    [跳过复制] greedy_mems 为 0 或 -1 或无效。")
            except Exception as e:
                print(f"    [复制失败] {e}")

            results.append(entry)

    except KeyboardInterrupt:
        print("\n[用户中断] 提前退出，正在生成中间统计...")

    finally:
        print("\n==== 写入CSV和统计信息（可含中间结果） ====")
        summarize_and_save(results, folders, args.summary, args.overview)

if __name__ == "__main__":
    main()
