import subprocess
import glob
import re
import pandas as pd
import os
import shutil  # 新增

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
    # 允许负数（例如 MEMS: -1）
    mems_match = re.search(r"MEMS:\s*(-?\d+)", output)
    mems_val = mems_match.group(1) if mems_match else ''
    time_match = re.search(r"\[DP TIME COST\]: ([\d\.]+) seconds", output)
    time_val = time_match.group(1) if time_match else ''
    return mems_val, time_val

def extract_time(output, tag):
    match = re.search(tag, output)
    return match.group(1) if match else ''

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

def main():
    print("==== 扫描目标文件夹 ====")
    folders = ["output_c_files_gemini", "output_c_files_gpt", "output_c_files_ds"]
    c_files = []
    for folder in folders:
        files = glob.glob(os.path.join(folder, "*.c"))
        print(f"  {folder}: 找到 {len(files)} 个 .c 文件")
        c_files += files
    print(f"== 共 {len(c_files)} 个 C 文件将被处理 ==\n")

    if not c_files:
        print("[终止] 未在指定文件夹下发现任何 .c 文件。")
        return

    # 确保 output_complete 文件夹存在
    os.makedirs("output_complete", exist_ok=True)

    results = []
    try:
        for idx, cfile in enumerate(c_files):
            print(f"\n====== 文件 {idx+1}/{len(c_files)}: {cfile} ======")
            entry = {'filename': cfile}
            folder = get_folder(cfile, folders)
            entry['folder'] = folder

            # Step 1: ../cnip -q
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
                # 允许负数
                dfs_max = re.search(r"\[DFS MAX MEMS\]:\s*(-?\d+)", out_f)
                dfs_min = re.search(r"\[DFS MIN MEMS\]:\s*(-?\d+)", out_f)
                entry['dfs_max_mems'] = dfs_max.group(1) if dfs_max else ''
                entry['dfs_min_mems'] = dfs_min.group(1) if dfs_min else ''
                entry['f_error'] = ''
                print(f"    [OK] DFS time: {entry['dfs_time']} | max mems: {entry['dfs_max_mems']} | min mems: {entry['dfs_min_mems']}")

            # Step 2: ../cnip -g
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
                # 提取路径内容
                path_match = re.search(r"\[TEST INPUT PATH EXPR\]:\s*([\s\S]+?)(?=\n*\[DP TIME COST\]:|\Z)", out_g)
                entry['greedy_path'] = path_match.group(1).strip() if path_match else ""
                print(f"    [OK] Greedy time: {greedy_time} | mems: {greedy_mems}")

            entry['success'] = not fail_flag
            entry['mems_equal'] = (entry.get('dfs_max_mems', None) == entry.get('greedy_mems', None)
                                and entry.get('dfs_max_mems', '') not in ('', 'error'))
            print(f"  [总结] 本文件执行 {'成功' if entry['success'] else '失败'} | mems是否一致: {entry['mems_equal']}")

            # ✅ 新增：复制成功的文件到 output_complete
            if entry['success']:
                try:
                    shutil.copy2(cfile, "output_complete")
                    print(f"    [已复制] 成功文件保存到 output_complete/{os.path.basename(cfile)}")
                except Exception as e:
                    print(f"    [复制失败] {e}")

            results.append(entry)

    except KeyboardInterrupt:
        print("\n[用户中断] 提前退出，已保存已完成的数据。")

    print("\n==== 写入CSV和统计信息 ====")
    df = pd.DataFrame(results, columns=[
        'filename', 'folder', 'dfs_time', 'dfs_max_mems', 'dfs_min_mems',
        'greedy_time', 'greedy_mems', 'greedy_path',
        'f_error', 'g_error', 'success', 'mems_equal'
    ])
    df.to_csv("result_summary.csv", index=False)
    print("  [CSV] 已保存至 result_summary.csv")

    total = len(df)
    success_count = df['success'].sum()
    mems_equal_count = df['mems_equal'].sum()
    success_rate = success_count / total if total else 0
    mems_equal_rate = mems_equal_count / success_count if success_count else 0
    print("\n==== 统计结果 ====")
    print(f"  总文件数: {total}")
    print(f"  成功: {success_count} ({success_rate:.2%})")
    print(f"  mems相同准确率: {mems_equal_count}/{success_count} = {mems_equal_rate:.2%} (仅统计成功样本)")

    print("\n==== 分文件夹成功率 ====")
    for folder in folders:
        folder_df = df[df['folder'] == folder]
        n = len(folder_df)
        n_success = folder_df['success'].sum()
        rate = n_success / n if n else 0
        print(f"  {folder}: {n_success}/{n} ({rate:.2%})")

if __name__ == "__main__":
    main()
