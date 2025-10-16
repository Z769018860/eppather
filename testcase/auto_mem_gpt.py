import os
import re
import glob
import json
import time
import shutil
import pandas as pd
import subprocess
import traceback
import requests
from typing import Tuple, Dict, Any, Optional

# =========================
# === GPT API 基本配置 ===
# =========================
# 优先读取环境变量，若未设置则 fallback 到你给的默认值
API_KEY = os.getenv("IFOPEN_API_KEY", "sk-yq2oZ7K1VAVYBOT4qTICVThcaimfcRbc8UHm08K0guYWuq9s")
BASE_URL = os.getenv("IFOPEN_BASE_URL", "https://api.ifopen.ai/v1")
MODEL_NAME = os.getenv("IFOPEN_MODEL", "gpt-4-turbo")

# ==============
# 工具函数
# ==============
def run_with_timeout(cmd, timeout=80):
    print(f"      [run] CMD: {' '.join(cmd)}")
    try:
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        try:
            out, err = proc.communicate(timeout=timeout)
            returncode = proc.returncode
        except subprocess.TimeoutExpired:
            proc.kill()
            out, err = proc.communicate()
            print("      [timeout] Walltime exceeded, process killed.")
            return out, err, 'Timeout'
        return out, err, returncode
    except Exception as e:
        print(f"      [exception] {e}")
        return '', str(e), 'Exception'

def error_status(output, error, retcode, time_tag_regex):
    err_combined = (output or "") + (error or "")
    if "Segmentation fault (core dumped)" in err_combined or "core dumped" in err_combined:
        return True, 'core dumped'
    if retcode == 'Timeout':
        return True, 'timeout'
    if retcode == 'Exception':
        return True, 'exception'
    if isinstance(retcode, int) and retcode != 0:
        return True, f'retcode_{retcode}'
    if re.search(time_tag_regex, output) is None:
        # 允许个别实现不打印时间，这里降级为仅告警而不直接当失败
        return False, 'no_time_output'
    return False, ''

def extract_greedy(output: str) -> Tuple[str, str]:
    mems_match = re.search(r"MEMS:\s*(\d+)", output)
    mems_val = mems_match.group(1) if mems_match else ''
    time_match = re.search(r"\[DP TIME COST\]:\s*([\d\.]+)\s*seconds", output)
    time_val = time_match.group(1) if time_match else ''
    return mems_val, time_val

def extract_time(output: str, tag_regex: str) -> str:
    match = re.search(tag_regex, output)
    return match.group(1) if match else ''

def short_err(err: str, length: int = 200) -> str:
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

# =======================
# GPT 交互与解析逻辑
# =======================
GPT_SYSTEM_PROMPT = (
    "You are a static program analysis assistant for C code. "
    "Your task: within at most 3 levels of function expansion (inline), "
    "determine a FEASIBLE execution path that maximizes the MEMS (memory accesses) metric. "
    "The path must be executable under some concrete inputs (feasible), not contradictory. "
    "Return STRICT JSON ONLY with this exact schema (no prose):\n"
    "{\n"
    '  "mems": <non-negative integer>,\n'
    '  "test_input_path_expr": "<path steps in the EXACT format used below>",\n'
    '  "reason": "<very brief note, one line>"\n'
    "}\n\n"
    "The required path steps format is EXACTLY like:\n"
    "[TEST INPUT PATH EXPR]:\\n"
    "@(cond1);\\n"
    "@(cond2);\\n"
    "x = y;\\n"
    "i = i - 1;\\n"
    "...\n"
    "No extra sections. No code fences. No markdown."
)

GPT_USER_PROMPT_TMPL = (
    "Given this C function (unit-style, single function), expand at most 3 times for any callee, "
    "ensure a FEASIBLE path, and output the MAX-MEMS path and its MEMS. "
    "Keep variable and control names consistent. Produce STRICT JSON per schema.\n\n"
    "-----BEGIN C CODE-----\n{code}\n-----END C CODE-----"
)

def call_gpt_for_mems(code: str, max_retries: int = 2, timeout_sec: int = 90) -> Tuple[Optional[int], str, str]:
    """
    返回: (mems_int_or_None, path_text, raw_response_text)
    path_text 需要是以 [TEST INPUT PATH EXPR]: 开头的多行文本；若解析失败则为空串。
    """
    url = f"{BASE_URL.rstrip('/')}/chat/completions"
    headers = {
        "Authorization": f"Bearer {API_KEY}",
        "Content-Type": "application/json",
    }
    payload = {
        "model": MODEL_NAME,
        "messages": [
            {"role": "system", "content": GPT_SYSTEM_PROMPT},
            {"role": "user", "content": GPT_USER_PROMPT_TMPL.format(code=code)}
        ],
        "temperature": 0.0,
        "response_format": {"type": "text"}  # 兼容 OpenAI 格式
    }

    last_text = ""
    for attempt in range(max_retries + 1):
        try:
            resp = requests.post(url, headers=headers, data=json.dumps(payload), timeout=timeout_sec)
            if resp.status_code != 200:
                last_text = f"[HTTP {resp.status_code}] {resp.text}"
                print(f"      [GPT] HTTP error: {last_text}")
                time.sleep(1.0)
                continue
            data = resp.json()
            # 兼容 OpenAI Chat Completions 返回格式
            text = data.get("choices", [{}])[0].get("message", {}).get("content", "") or ""
            last_text = text.strip()
            mems, path_expr = parse_gpt_output(last_text)
            if mems is not None and path_expr:
                return mems, path_expr, last_text
            else:
                print("      [GPT] Parse failed, retrying...")
                time.sleep(1.0)
        except Exception as e:
            last_text = f"[EXCEPTION] {repr(e)}\n{traceback.format_exc()}"
            print(f"      [GPT] Exception: {short_err(last_text)}")
            time.sleep(1.0)
    return None, "", last_text

def parse_gpt_output(text: str) -> Tuple[Optional[int], str]:
    """
    解析顺序：
    1) 严格 JSON 解析，读取 mems 和 test_input_path_expr
    2) 若失败，尝试从三引号或代码块中截取 JSON 再解析
    3) 兜底：正则提取 MEMS 数字 + 提取 [TEST INPUT PATH EXPR]: 区块
    """
    # 1) 直接当 JSON
    mems, path_expr = _parse_json_payload(text)
    if _valid_mems_path(mems, path_expr):
        return mems, path_expr

    # 2) 尝试从 ```json ... ``` 中抽取
    fenced = re.search(r"```(?:json)?\s*({[\s\S]+?})\s*```", text, re.IGNORECASE)
    if fenced:
        mems, path_expr = _parse_json_payload(fenced.group(1))
        if _valid_mems_path(mems, path_expr):
            return mems, path_expr

    # 3) 兜底正则：MEMS 与 PATH
    mems_rgx = re.search(r'"?mems"?\s*[:=]\s*"?(\d+)"?', text, re.IGNORECASE)
    mems_val = int(mems_rgx.group(1)) if mems_rgx else None

    path_block = _extract_path_block(text)
    if _valid_mems_path(mems_val, path_block):
        return mems_val, path_block

    return None, ""

def _parse_json_payload(js_text: str) -> Tuple[Optional[int], str]:
    try:
        obj = json.loads(js_text)
        mems = obj.get("mems", None)
        if isinstance(mems, str) and mems.isdigit():
            mems = int(mems)
        if isinstance(mems, (int,)) and mems >= 0:
            path_expr = obj.get("test_input_path_expr", "")
            # 兼容有的人在 path 里漏写标题
            if path_expr and not path_expr.strip().startswith("[TEST INPUT PATH EXPR]:"):
                # 尝试补齐
                path_expr = "[TEST INPUT PATH EXPR]:\n" + path_expr.strip()
            return mems, path_expr
    except Exception:
        pass
    return None, ""

def _extract_path_block(text: str) -> str:
    m = re.search(
        r"(\[TEST INPUT PATH EXPR\]:\s*[\s\S]+?)(?=\n{0,2}\[DP TIME COST\]:|\Z)",
        text
    )
    if m:
        return m.group(1).strip()
    return ""

def _valid_mems_path(mems: Optional[int], path: str) -> bool:
    if not isinstance(mems, int) or mems is None or mems < 0:
        return False
    if not path or "[TEST INPUT PATH EXPR]:" not in path:
        return False
    # 轻量可行性/格式校验：行数、非法字符、语句结束符
    lines = [ln.strip() for ln in path.splitlines() if ln.strip()]
    if len(lines) < 2:
        return False
    if not lines[0].startswith("[TEST INPUT PATH EXPR]:"):
        return False
    # 每条语句应以 ; 结尾（标题行除外）
    for ln in lines[1:]:
        if not ln.endswith(";"):
            return False
    return True

# ================================
# 主流程：GPT(替代DFS) + DP 对照
# ================================
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

            # 读取 C 源码
            try:
                with open(cfile, 'r', encoding='utf-8', errors='ignore') as f:
                    code_text = f.read()
            except Exception as e:
                print(f"  [失败] 读取源码失败: {e}")
                entry.update({
                    'gpt_time': 'error',
                    'gpt_mems': 'error',
                    'gpt_path': '',
                    'gpt_raw': short_err(str(e)),
                    'gpt_error': 'read_source_fail'
                })
                # 仍尝试运行 DP 以便保留对照
                code_text = ""

            # Step 1: 调 GPT（替代 DFS）
            print("  [1/2] 调用 GPT 进行 3 次展开内的可行最大 MEMS 路径分析")
            t0 = time.time()
            gpt_mems, gpt_path, gpt_raw = call_gpt_for_mems(code_text) if code_text else (None, "", "")
            t1 = time.time()
            entry['gpt_time'] = f"{t1 - t0:.4f}"

            if gpt_mems is None or not gpt_path:
                print("  [失败] GPT 阶段解析失败")
                entry.update({
                    'gpt_mems': 'error',
                    'gpt_path': '',
                    'gpt_raw': short_err(gpt_raw, 500),
                    'gpt_error': 'parse_fail'
                })
            else:
                entry.update({
                    'gpt_mems': str(gpt_mems),
                    'gpt_path': gpt_path,
                    'gpt_raw': '',       # 原始结果过长，不落表；若需要可单独保存
                    'gpt_error': ''
                })
                print(f"  [OK] GPT time: {entry['gpt_time']} | mems: {entry['gpt_mems']}")

            # Step 2: ../cnip -g （DP/Greedy）
            print(f"  [2/2] 执行 DP/Greedy 路径分析: ../cnip -g {cfile}")
            cmd_g = ["../cnip", "-g", cfile]
            out_g, err_g, ret_g = run_with_timeout(cmd_g, timeout=180)
            greedy_error, greedy_reason = error_status(
                out_g, err_g, ret_g, r"\[DP TIME COST\]:\s*([\d\.]+)\s*seconds"
            )
            if greedy_error:
                print(f"  [失败] DP 阶段错误类型: {greedy_reason}")
                entry.update({
                    'greedy_time': 'error',
                    'greedy_mems': 'error',
                    'greedy_path': '',
                    'g_error': greedy_reason
                })
            else:
                greedy_mems, greedy_time = extract_greedy(out_g)
                entry['greedy_mems'] = greedy_mems
                entry['greedy_time'] = greedy_time
                entry['g_error'] = ''
                path_match = re.search(r"\[TEST INPUT PATH EXPR\]:\s*([\s\S]+?)(?=\n*\[DP TIME COST\]:|\Z)", out_g)
                entry['greedy_path'] = path_match.group(1).strip() if path_match else ""
                print(f"  [OK] DP time: {greedy_time} | mems: {greedy_mems}")

            # 汇总状态
            success_gpt = entry.get('gpt_error', '') == ''
            success_dp = entry.get('g_error', '') == ''
            entry['success'] = success_gpt and success_dp

            # 一致性：GPT 的 MEMS 与 DP 的 MEMS 是否一致（仅在两侧都有合法值时计算）
            gpt_mems_val = entry.get('gpt_mems', '')
            dp_mems_val = entry.get('greedy_mems', '')
            entry['mems_equal'] = (gpt_mems_val.isdigit() and dp_mems_val.isdigit()
                                   and int(gpt_mems_val) == int(dp_mems_val))

            print(f"  [总结] 本文件执行 {'成功' if entry['success'] else '失败'} | mems是否一致: {entry['mems_equal']}")

            # 成功样本复制
            if entry['success']:
                try:
                    shutil.copy2(cfile, "output_complete")
                    print(f"  [已复制] 成功文件保存到 output_complete/{os.path.basename(cfile)}")
                except Exception as e:
                    print(f"  [复制失败] {e}")

            results.append(entry)

    except KeyboardInterrupt:
        print("\n[用户中断] 提前退出，已保存已完成的数据。")

    # ==============
    # 写 CSV & 统计
    # ==============
    print("\n==== 写入CSV和统计信息 ====")
    cols = [
        'filename', 'folder',
        'gpt_time', 'gpt_mems', 'gpt_path', 'gpt_error',
        'greedy_time', 'greedy_mems', 'greedy_path', 'g_error',
        'success', 'mems_equal'
    ]
    df = pd.DataFrame(results, columns=cols)
    df.to_csv("result_summary_gpt.csv", index=False, encoding='utf-8')
    print("  [CSV] 已保存至 result_summary_gpt.csv")

    total = len(df)
    success_count = int(df['success'].sum()) if total else 0
    equal_count = int(df['mems_equal'].sum()) if total else 0
    success_rate = (success_count / total) if total else 0.0
    equal_rate = (equal_count / success_count) if success_count else 0.0

    print("\n==== 统计结果 ====")
    print(f"  总文件数: {total}")
    print(f"  成功: {success_count} ({success_rate:.2%})")
    print(f"  GPT vs DP mems一致率: {equal_count}/{success_count} = {equal_rate:.2%} (仅统计成功样本)")

    print("\n==== 分文件夹成功率 ====")
    for folder in ["output_c_files_gemini", "output_c_files_gpt", "output_c_files_ds"]:
        folder_df = df[df['folder'] == folder]
        n = len(folder_df)
        n_success = int(folder_df['success'].sum()) if n else 0
        rate = (n_success / n) if n else 0.0
        print(f"  {folder}: {n_success}/{n} ({rate:.2%})")

if __name__ == "__main__":
    main()
