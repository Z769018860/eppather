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
from typing import Tuple, Optional, Dict, Any


INPUT_FOLDER = "output_complete2"
OUTPUT_TRUE_FOLDER = "output_true3"
SUMMARY_CSV = "result_summary_true3.csv"
SUMMARY_XLSX = "result_summary_true3.xlsx"
TRUE_ONLY_CSV = "result_true_only3.csv"
TRUE_ONLY_XLSX = "result_true_only3.xlsx"


# =========================
# === GPT API 基本配置 ===
# =========================
# 优先 IFOPEN_*，其次 OPENAI_*（二选一）
API_KEY = (os.getenv("IFOPEN_API_KEY") or os.getenv("OPENAI_API_KEY") or "sk-yq2oZ7K1VAVYBOT4qTICVThcaimfcRbc8UHm08K0guYWuq9s").strip()
BASE_URL = (os.getenv("IFOPEN_BASE_URL") or os.getenv("OPENAI_BASE_URL") or "https://api.ifopen.ai/v1").strip()
MODEL_NAME = (os.getenv("IFOPEN_MODEL") or os.getenv("OPENAI_MODEL") or "gpt-4-turbo").strip()

# 可选：注入额外 headers（某些代理/网关需要）
# 例：
# export IFOPEN_HEADERS_JSON='{"X-Api-Key":"xxxxx","X-Org":"yyy"}'
EXTRA_HEADERS_JSON = (os.getenv("IFOPEN_HEADERS_JSON") or "").strip()


def _mask_key(k: str) -> str:
    if not k:
        return ""
    if len(k) <= 8:
        return "*" * len(k)
    return k[:3] + "***" + k[-3:] + f"(len={len(k)})"


def _load_extra_headers() -> Dict[str, str]:
    if not EXTRA_HEADERS_JSON:
        return {}
    try:
        obj = json.loads(EXTRA_HEADERS_JSON)
        if isinstance(obj, dict):
            out: Dict[str, str] = {}
            for kk, vv in obj.items():
                if isinstance(kk, str) and isinstance(vv, str):
                    out[kk] = vv
            return out
    except Exception:
        pass
    return {}


if not API_KEY:
    raise RuntimeError("Missing API key. Please set IFOPEN_API_KEY (preferred) or OPENAI_API_KEY in your environment.")

print("==== API CONFIG ====")
print(f"  BASE_URL : {BASE_URL}")
print(f"  MODEL    : {MODEL_NAME}")
print(f"  API_KEY  : {_mask_key(API_KEY)}")
if EXTRA_HEADERS_JSON:
    print("  EXTRA_HEADERS_JSON : [provided]")
else:
    print("  EXTRA_HEADERS_JSON : [none]")
print("====================\n")


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
            return out, err, "Timeout"
        return out, err, returncode
    except Exception as e:
        print(f"      [exception] {e}")
        return "", str(e), "Exception"


def error_status(output, error, retcode, time_tag_regex):
    err_combined = (output or "") + (error or "")
    if "Segmentation fault (core dumped)" in err_combined or "core dumped" in err_combined:
        return True, "core dumped"
    if retcode == "Timeout":
        return True, "timeout"
    if retcode == "Exception":
        return True, "exception"
    if isinstance(retcode, int) and retcode != 0:
        return True, f"retcode_{retcode}"
    if re.search(time_tag_regex, output) is None:
        return False, "no_time_output"
    return False, ""


def extract_greedy(output: str) -> Tuple[str, str]:
    mems_match = re.search(r"MEMS:\s*(\d+)", output)
    mems_val = mems_match.group(1) if mems_match else ""
    time_match = re.search(r"\[DP TIME COST\]:\s*([\d\.]+)\s*seconds", output)
    time_val = time_match.group(1) if time_match else ""
    return mems_val, time_val


def short_err(err: str, length: int = 200) -> str:
    if not err:
        return ""
    lines = err.strip().splitlines()
    if len(lines) == 0:
        return ""
    head = lines[0]
    more = f" ... ({len(lines)} lines)" if len(lines) > 1 else ""
    text = head + more
    if len(text) > length:
        text = text[:length] + "..."
    return text


def _sanitize_secrets(text: str) -> str:
    if not text:
        return text
    text = re.sub(r"sk-[A-Za-z0-9_\-]{10,}", "sk-***REDACTED***", text)
    text = re.sub(r"(Bearer)\s+[A-Za-z0-9_\-\.]{10,}", r"\1 ***REDACTED***", text)
    return text


def _strip_code_fences(s: str) -> str:
    if not s:
        return s
    m = re.search(r"```(?:json)?\s*([\s\S]+?)\s*```", s, re.IGNORECASE)
    if m:
        return m.group(1).strip()
    return s.strip()


def _extract_first_json_object(text: str) -> str:
    if not text:
        return ""
    s = text.strip()
    start = s.find("{")
    if start < 0:
        return ""
    depth = 0
    for i in range(start, len(s)):
        if s[i] == "{":
            depth = depth + 1
        elif s[i] == "}":
            depth = depth - 1
            if depth == 0:
                return s[start : i + 1]
    return ""


def _normalize_path_expr(path_expr: str) -> str:
    if not path_expr:
        return ""
    p = path_expr.strip()
    if not p.startswith("[TEST INPUT PATH EXPR]:"):
        p = "[TEST INPUT PATH EXPR]:\n" + p
    lines = p.splitlines()
    if len(lines) <= 1:
        return p
    out_lines = []
    out_lines.append(lines[0].strip())
    for ln in lines[1:]:
        t = ln.strip()
        if not t:
            continue
        if not t.endswith(";"):
            t = t + ";"
        out_lines.append(t)
    return "\n".join(out_lines).strip()


def _valid_mems_path(mems: Optional[int], path: str) -> bool:
    if mems is None or (not isinstance(mems, int)) or mems < 0:
        return False
    if not path or "[TEST INPUT PATH EXPR]:" not in path:
        return False
    lines = [ln.rstrip() for ln in path.splitlines() if ln.strip()]
    if len(lines) < 2:
        return False
    if not lines[0].lstrip().startswith("[TEST INPUT PATH EXPR]:"):
        return False
    for ln in lines[1:]:
        t = ln.strip()
        if not t:
            continue
        if not t.endswith(";"):
            return False
    return True


def _parse_json_payload(js_text: str) -> Tuple[Optional[int], str]:
    try:
        obj = json.loads(js_text)
        mems = obj.get("mems", None)
        if isinstance(mems, str) and mems.isdigit():
            mems = int(mems)
        if not isinstance(mems, int) or mems < 0:
            return None, ""
        path_expr = obj.get("test_input_path_expr", "")
        path_expr = _normalize_path_expr(path_expr)
        return mems, path_expr
    except Exception:
        return None, ""


def _extract_path_block(text: str) -> str:
    if not text:
        return ""
    m = re.search(
        r"(\[TEST INPUT PATH EXPR\]:\s*[\s\S]+?)(?=\n{0,2}\[DP TIME COST\]:|\Z)",
        text,
    )
    if m:
        return _normalize_path_expr(m.group(1).strip())
    return ""


def parse_gpt_output(text: str) -> Tuple[Optional[int], str]:
    if not text:
        return None, ""
    raw = text.strip()

    mems, path_expr = _parse_json_payload(raw)
    if _valid_mems_path(mems, path_expr):
        return mems, path_expr

    unfenced = _strip_code_fences(raw)
    mems, path_expr = _parse_json_payload(unfenced)
    if _valid_mems_path(mems, path_expr):
        return mems, path_expr

    first_obj = _extract_first_json_object(unfenced)
    if first_obj:
        mems, path_expr = _parse_json_payload(first_obj)
        if _valid_mems_path(mems, path_expr):
            return mems, path_expr

    mems_rgx = re.search(r'"?mems"?\s*[:=]\s*"?(\d+)"?', unfenced, re.IGNORECASE)
    mems_val = int(mems_rgx.group(1)) if mems_rgx else None
    path_block = _extract_path_block(unfenced)
    if _valid_mems_path(mems_val, path_block):
        return mems_val, path_block

    return None, ""


def build_system_prompt() -> str:
    return (
        "You are a static program analysis assistant for C code.\n"
        "Goal: within at most 3 levels of function expansion (inline), find a FEASIBLE execution path "
        "that maximizes MEMS.\n"
        "The path must be executable under some concrete inputs (feasible).\n\n"
        "MEMS counting rules (MUST follow exactly):\n"
        "- MEMS = (#reads + #writes) of program objects along the path.\n"
        "- Reading an object as rvalue counts +1. Writing an object counts +1.\n"
        "- Objects include: locals/params/globals, array element arr[i], struct/union field s.f, "
        "deref *p and p->f.\n"
        "- In arr[i], reading index i counts as a read (+1) each time it is evaluated.\n"
        "- In *p / p->f, reading pointer variable p counts as a read (+1) each time it is evaluated.\n"
        "- Assignment L = E: count reads in E + 1 write for L.\n"
        "- Compound assignment x += y: treat as x = x + y.\n"
        "- ++x / x++ / --x / x--: read x + write x.\n"
        "- Conditions: count reads in the condition expression. Respect short-circuit for && and ||.\n"
        "- Function calls: inline-expand at most 3 levels. Count MEMS from expanded bodies. "
        "Do NOT add ABI/call overhead. Still count reads inside argument expressions.\n"
        "- Do NOT assume undefined behavior; ensure a plausible feasible path.\n\n"
        "Return STRICT JSON ONLY with this exact schema (no prose):\n"
        "{\n"
        '  "mems": <non-negative integer>,\n'
        '  "test_input_path_expr": "<path steps in the EXACT format used below>",\n'
        '  "reason": "<very brief note, one line>"\n'
        "}\n\n"
        "The required path steps format is EXACTLY like:\n"
        "[TEST INPUT PATH EXPR]:\n"
        "@(cond1);\n"
        "@(cond2);\n"
        "x = y;\n"
        "i = i - 1;\n"
        "...\n"
        "Every non-empty line after the title MUST end with ';'.\n"
        "No extra sections. No code fences. No markdown."
    )


def build_user_prompt(code: str) -> str:
    return (
        "Given this C function (unit-style, single function), expand at most 3 times for any callee, "
        "ensure a FEASIBLE path, and output the MAX-MEMS path and its MEMS. "
        "Keep variable and control names consistent. Produce STRICT JSON per schema.\n\n"
        "-----BEGIN C CODE-----\n"
        f"{code}\n"
        "-----END C CODE-----"
    )


def _extract_api_error(resp_text: str) -> Dict[str, str]:
    try:
        obj = json.loads(resp_text)
        err = obj.get("error", {})
        if isinstance(err, dict):
            msg = str(err.get("message", "") or "")
            typ = str(err.get("type", "") or "")
            code = str(err.get("code", "") or "")
            return {"message": msg, "type": typ, "code": code}
    except Exception:
        pass
    return {"message": resp_text.strip(), "type": "", "code": ""}


def _extract_content_from_response(data: Any) -> str:
    if not isinstance(data, dict):
        return ""
    choices = data.get("choices", None)
    if isinstance(choices, list) and len(choices) > 0:
        c0 = choices[0]
        if isinstance(c0, dict):
            msg = c0.get("message", None)
            if isinstance(msg, dict):
                content = msg.get("content", "")
                if isinstance(content, str):
                    return content
            txt = c0.get("text", "")
            if isinstance(txt, str):
                return txt
    if "message" in data and isinstance(data["message"], dict):
        content = data["message"].get("content", "")
        if isinstance(content, str):
            return content
    return ""


def call_gpt_for_mems(code: str, max_retries: int = 2, timeout_sec: int = 90) -> Tuple[Optional[int], str, str]:
    url = f"{BASE_URL.rstrip('/')}/chat/completions"
    headers = {
        "Authorization": f"Bearer {API_KEY}",
        "Content-Type": "application/json",
    }
    headers.update(_load_extra_headers())

    payload = {
        "model": MODEL_NAME,
        "messages": [
            {"role": "system", "content": build_system_prompt()},
            {"role": "user", "content": build_user_prompt(code)},
        ],
        "temperature": 0.0,
        "response_format": {"type": "text"},
    }

    last_text = ""
    for attempt in range(max_retries + 1):
        try:
            resp = requests.post(url, headers=headers, data=json.dumps(payload), timeout=timeout_sec)
            if resp.status_code != 200:
                err_info = _extract_api_error(resp.text)
                msg = err_info.get("message", "")
                typ = err_info.get("type", "")
                code_ = err_info.get("code", "")
                line = f"[HTTP {resp.status_code}] type={typ} code={code_} msg={msg}"
                line = _sanitize_secrets(line)
                print(f"      [GPT] HTTP error: {short_err(line, 380)}")

                if resp.status_code in (401, 403):
                    return None, "", line
                time.sleep(1.0)
                continue

            data = resp.json()
            text = _extract_content_from_response(data).strip()
            last_text = text

            mems, path_expr = parse_gpt_output(last_text)
            if mems is not None and path_expr:
                return mems, path_expr, last_text

            print("      [GPT] Parse failed, retrying...")
            time.sleep(1.0)
        except Exception as e:
            last_text = _sanitize_secrets(f"[EXCEPTION] {repr(e)}\n{traceback.format_exc()}")
            print(f"      [GPT] Exception: {short_err(last_text)}")
            time.sleep(1.0)

    return None, "", last_text


def main():
    print("==== 扫描目标文件夹 ====")
    c_files = glob.glob(os.path.join(INPUT_FOLDER, "*.c"))
    print(f"  {INPUT_FOLDER}: 找到 {len(c_files)} 个 .c 文件")

    print(f"== 共 {len(c_files)} 个 C 文件将被处理 ==\n")
    if not c_files:
        print("[终止] 未在指定文件夹下发现任何 .c 文件。")
        return

    os.makedirs(OUTPUT_TRUE_FOLDER, exist_ok=True)

    results = []
    try:
        for idx, cfile in enumerate(c_files):
            print(f"\n====== 文件 {idx+1}/{len(c_files)}: {cfile} ======")

            entry = {"filename": cfile, "basename": os.path.basename(cfile)}

            try:
                with open(cfile, "r", encoding="utf-8", errors="ignore") as f:
                    code_text = f.read()
            except Exception as e:
                print(f"  [失败] 读取源码失败: {e}")
                entry.update(
                    {
                        "gpt_time": "error",
                        "gpt_mems": "error",
                        "gpt_path": "",
                        "gpt_error": "read_source_fail",
                        "greedy_time": "error",
                        "greedy_mems": "error",
                        "greedy_path": "",
                        "g_error": "read_source_fail",
                        "success_gpt": False,
                        "success_dp": False,
                        "mems_equal": False,
                        "is_true": False,
                        "worst_mems": "",
                        "worst_path": "",
                    }
                )
                results.append(entry)
                continue

            print("  [1/2] 调用 GPT 进行 3 次展开内的可行最大 MEMS 路径分析")
            t0 = time.time()
            gpt_mems, gpt_path, gpt_raw = call_gpt_for_mems(code_text)
            t1 = time.time()
            entry["gpt_time"] = f"{t1 - t0:.4f}"

            if gpt_mems is None or not gpt_path:
                print("  [失败] GPT 阶段解析失败")
                entry.update(
                    {
                        "gpt_mems": "error",
                        "gpt_path": "",
                        "gpt_error": short_err(_sanitize_secrets(gpt_raw), 300) or "parse_fail",
                    }
                )
                success_gpt = False
            else:
                entry.update(
                    {
                        "gpt_mems": str(gpt_mems),
                        "gpt_path": gpt_path,
                        "gpt_error": "",
                    }
                )
                print(f"  [OK] GPT time: {entry['gpt_time']} | mems: {entry['gpt_mems']}")
                success_gpt = True

            print(f"  [2/2] 执行 DP/Greedy 路径分析: ../cnip -g {cfile}")
            cmd_g = ["../cnip", "-g", cfile]
            out_g, err_g, ret_g = run_with_timeout(cmd_g, timeout=180)
            greedy_error, greedy_reason = error_status(
                out_g, err_g, ret_g, r"\[DP TIME COST\]:\s*([\d\.]+)\s*seconds"
            )

            if greedy_error:
                print(f"  [失败] DP 阶段错误类型: {greedy_reason}")
                entry.update(
                    {
                        "greedy_time": "error",
                        "greedy_mems": "error",
                        "greedy_path": "",
                        "g_error": greedy_reason,
                    }
                )
                success_dp = False
            else:
                greedy_mems, greedy_time = extract_greedy(out_g)
                entry["greedy_mems"] = greedy_mems
                entry["greedy_time"] = greedy_time
                entry["g_error"] = ""
                path_match = re.search(
                    r"(\[TEST INPUT PATH EXPR\]:\s*[\s\S]+?)(?=\n*\[DP TIME COST\]:|\Z)", out_g
                )
                entry["greedy_path"] = path_match.group(1).strip() if path_match else ""
                print(f"  [OK] DP time: {greedy_time} | mems: {greedy_mems}")
                success_dp = True

            entry["success_gpt"] = bool(success_gpt)
            entry["success_dp"] = bool(success_dp)

            gpt_mems_val = entry.get("gpt_mems", "")
            dp_mems_val = entry.get("greedy_mems", "")

            mems_equal = (
                success_gpt
                and success_dp
                and gpt_mems_val.isdigit()
                and dp_mems_val.isdigit()
                and int(gpt_mems_val) == int(dp_mems_val)
            )
            entry["mems_equal"] = bool(mems_equal)

            entry["worst_mems"] = entry["greedy_mems"] if success_dp else ""
            entry["worst_path"] = entry["greedy_path"] if success_dp else ""
            entry["is_true"] = bool(mems_equal)

            print(
                f"  [总结] GPT成功={entry['success_gpt']} | DP成功={entry['success_dp']} | "
                f"mems一致={entry['mems_equal']} | TRUE保存={entry['is_true']}"
            )

            if entry["is_true"]:
                try:
                    dst = os.path.join(OUTPUT_TRUE_FOLDER, os.path.basename(cfile))
                    shutil.copy2(cfile, dst)
                    print(f"  [已保存] {dst}")
                except Exception as e:
                    print(f"  [保存失败] {e}")

            results.append(entry)

    except KeyboardInterrupt:
        print("\n[用户中断] 提前退出，已保存已完成的数据。")

    print("\n==== 写入表格与统计 ====")
    cols = [
        "filename",
        "basename",
        "gpt_time",
        "gpt_mems",
        "gpt_path",
        "gpt_error",
        "greedy_time",
        "greedy_mems",
        "greedy_path",
        "g_error",
        "success_gpt",
        "success_dp",
        "mems_equal",
        "is_true",
        "worst_mems",
        "worst_path",
    ]

    df = pd.DataFrame(results, columns=cols)
    df.to_csv(SUMMARY_CSV, index=False, encoding="utf-8")
    df.to_excel(SUMMARY_XLSX, index=False)

    df_true = df[df["is_true"] == True].copy()
    df_true.to_csv(TRUE_ONLY_CSV, index=False, encoding="utf-8")
    df_true.to_excel(TRUE_ONLY_XLSX, index=False)

    total = len(df)
    true_count = int(df["is_true"].sum()) if total else 0
    dp_ok = int(df["success_dp"].sum()) if total else 0
    gpt_ok = int(df["success_gpt"].sum()) if total else 0

    print(f"  [表格] 汇总CSV: {SUMMARY_CSV}")
    print(f"  [表格] 汇总XLSX: {SUMMARY_XLSX}")
    print(f"  [表格] TRUE子集CSV: {TRUE_ONLY_CSV}")
    print(f"  [表格] TRUE子集XLSX: {TRUE_ONLY_XLSX}")

    print("\n==== 统计结果 ====")
    if total:
        print(f"  总文件数: {total}")
        print(f"  GPT成功: {gpt_ok}/{total} ({gpt_ok/total:.2%})")
        print(f"  DP成功:  {dp_ok}/{total} ({dp_ok/total:.2%})")
        print(f"  TRUE(一致并已保存到{OUTPUT_TRUE_FOLDER}): {true_count}/{total} ({true_count/total:.2%})")
    else:
        print("  总文件数: 0")


if __name__ == "__main__":
    main()
