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
from typing import Tuple, Optional, Dict, Any, List


SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
REPO_ROOT = os.path.abspath(os.path.join(SCRIPT_DIR, ".."))

INPUT_FOLDER = os.path.join(SCRIPT_DIR, "output_complete2")

RUN_TAG = time.strftime("%Y%m%d_%H%M%S")
RESULT_DIR = os.path.join(SCRIPT_DIR, f"auto_mems_results_true3_{RUN_TAG}")
os.makedirs(RESULT_DIR, exist_ok=True)

OUTPUT_TRUE_FOLDER = os.path.join(RESULT_DIR, "output_true3")

SUMMARY_CSV = os.path.join(RESULT_DIR, "result_summary_true3.csv")
SUMMARY_XLSX = os.path.join(RESULT_DIR, "result_summary_true3.xlsx")

TRUE_ONLY_CSV = os.path.join(RESULT_DIR, "result_true_only3.csv")
TRUE_ONLY_XLSX = os.path.join(RESULT_DIR, "result_true_only3.xlsx")

GPT_FAIL_CSV = os.path.join(RESULT_DIR, "result_gpt_fail3.csv")
GPT_FAIL_XLSX = os.path.join(RESULT_DIR, "result_gpt_fail3.xlsx")
RUN_STATS_JSON = os.path.join(RESULT_DIR, "run_stats_true3.json")
RUN_STATS_CSV = os.path.join(RESULT_DIR, "run_stats_true3.csv")

PROMPT_HISTORY_JSON = os.path.join(RESULT_DIR, "prompt_backtrack_history_true3.json")
FINAL_PROMPT_TXT = os.path.join(RESULT_DIR, "prompt_final_true3.txt")
INPUT_GLOB = (os.getenv("AUTO_MEM_INPUT_GLOB") or "*.c").strip()
INPUT_RECURSIVE = (os.getenv("AUTO_MEM_INPUT_RECURSIVE") or "1").strip() != "0"
MAX_FILES = int((os.getenv("AUTO_MEM_MAX_FILES") or "0").strip() or "0")
MAX_LOOP = int((os.getenv("AUTO_MEM_MAX_LOOP") or "3").strip() or "3")
MAX_INLINE = int((os.getenv("AUTO_MEM_MAX_INLINE") or "3").strip() or "3")
MAX_BACKTRACK_ROUNDS = int((os.getenv("AUTO_MEM_MAX_BACKTRACK_ROUNDS") or "5").strip() or "5")
AUTO_BATCH_STAGES_ENV = (os.getenv("AUTO_MEM_BATCH_STAGES") or "5,10,20,100,1000").strip()
REQUIRE_GPT_DP_MATCH = (
    os.getenv("AUTO_MEM_REQUIRE_GPT_DP_MATCH")
    or os.getenv("AUTO_MEM_REQUIRE_GPT_DFS_MATCH")
    or "1"
).strip() != "0"
REQUIRE_EPATH_FEASIBLE = (os.getenv("AUTO_MEM_REQUIRE_EPATH_FEASIBLE") or "1").strip() != "0"
EPATH_FEASIBILITY_API = (os.getenv("AUTO_MEM_EPATH_FEASIBILITY_API") or "").strip()
EPATH_FEASIBILITY_TIMEOUT = int((os.getenv("AUTO_MEM_EPATH_FEASIBILITY_TIMEOUT") or "20").strip() or "20")
BASELINE_STAGE1 = int((os.getenv("AUTO_MEM_BASELINE_STAGE1") or "5").strip() or "5")
BASELINE_STAGE2 = int((os.getenv("AUTO_MEM_BASELINE_STAGE2") or "20").strip() or "20")
BASELINE_PASS_THRESHOLD = float((os.getenv("AUTO_MEM_BASELINE_PASS_THRESHOLD") or "0.5").strip() or "0.5")
ENABLE_METHOD_RETRY = (os.getenv("AUTO_MEM_ENABLE_METHOD_RETRY") or "1").strip() != "0"
CALIBRATION_SIZE = int((os.getenv("AUTO_MEM_CALIBRATION_SIZE") or "5").strip() or "5")
CALIBRATION_MAX_EXAMPLES = int((os.getenv("AUTO_MEM_CALIBRATION_MAX_EXAMPLES") or "5").strip() or "5")
CALIBRATION_CODE_CHAR_LIMIT = int((os.getenv("AUTO_MEM_CALIBRATION_CODE_CHAR_LIMIT") or "800").strip() or "800")
CALIBRATION_PATH_LINE_LIMIT = int((os.getenv("AUTO_MEM_CALIBRATION_PATH_LINE_LIMIT") or "8").strip() or "8")
INCLUDE_CALIBRATION_SOURCE = (os.getenv("AUTO_MEM_INCLUDE_CALIBRATION_SOURCE") or "0").strip() != "0"
TARGET_CODE_CHAR_LIMIT = int((os.getenv("AUTO_MEM_TARGET_CODE_CHAR_LIMIT") or "16000").strip() or "16000")
GPT_TIMEOUT_SEC = int((os.getenv("AUTO_MEM_GPT_TIMEOUT_SEC") or "180").strip() or "180")
GPT_MAX_RETRIES = int((os.getenv("AUTO_MEM_GPT_MAX_RETRIES") or "1").strip() or "1")
SWITCH_MODEL_ON_TIMEOUT = (os.getenv("AUTO_MEM_SWITCH_MODEL_ON_TIMEOUT") or "1").strip() != "0"

CNIP_CANDIDATES = [
    os.path.join(REPO_ROOT, "cnip"),
    os.path.join(SCRIPT_DIR, "..", "cnip"),
    "cnip",
]
CNIP_LIB_DIRS = [
    os.path.join(REPO_ROOT, "C"),
    os.path.join(REPO_ROOT, "common"),
]


# =========================
# === GPT API 基本配置 ===
# =========================
# 优先 IFOPEN_*，其次 OPENAI_*（二选一）
API_KEY = (os.getenv("IFOPEN_API_KEY") or os.getenv("OPENAI_API_KEY") or "sk-yq2oZ7K1VAVYBOT4qTICVThcaimfcRbc8UHm08K0guYWuq9s").strip()
BASE_URL = (os.getenv("IFOPEN_BASE_URL") or os.getenv("OPENAI_BASE_URL") or "https://api.ifopen.ai/v1").strip()
MODEL_NAME = (os.getenv("IFOPEN_MODEL") or os.getenv("OPENAI_MODEL") or "gpt-5-nano").strip()
MODEL_CANDIDATES_ENV = (
    os.getenv("IFOPEN_MODEL_CANDIDATES") or os.getenv("OPENAI_MODEL_CANDIDATES") or ""
).strip()

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


def _load_model_candidates() -> list:
    candidates = []
    if MODEL_NAME:
        candidates.append(MODEL_NAME)

    if MODEL_CANDIDATES_ENV:
        for item in MODEL_CANDIDATES_ENV.split(","):
            m = item.strip()
            if m:
                candidates.append(m)

    candidates.extend(["deepseek-v4-flash", "deepseek-v4-pro", "gpt-4o-mini", "gpt-4.1-mini", "gpt-4o", "gpt-4.1", "gpt-5-nano", "gpt-5-mini"])

    out = []
    seen = set()
    for m in candidates:
        if m not in seen:
            out.append(m)
            seen.add(m)
    return out


MODEL_CANDIDATES = _load_model_candidates()


def _resolve_cnip_path() -> str:
    for p in CNIP_CANDIDATES:
        if os.path.isfile(p) and os.access(p, os.X_OK):
            return os.path.abspath(p)
    return CNIP_CANDIDATES[0]


def _build_run_env() -> Dict[str, str]:
    env = os.environ.copy()
    existing = env.get("LD_LIBRARY_PATH", "")
    libs = [d for d in CNIP_LIB_DIRS if os.path.isdir(d)]
    if libs:
        env["LD_LIBRARY_PATH"] = ":".join(libs + ([existing] if existing else []))
    return env


CNIP_BIN = _resolve_cnip_path()
RUN_ENV = _build_run_env()
PROMPT_FEEDBACK_HISTORY: List[str] = []
FILE_FEEDBACK_HISTORY: Dict[str, List[str]] = {}
PROMPT_SNAPSHOTS: List[Dict[str, Any]] = []
BASELINE_ACCURACY_HISTORY: Dict[int, List[float]] = {}
CALIBRATION_EXAMPLES: List[Dict[str, Any]] = []
CALIBRATION_FEEDBACK_HISTORY: List[str] = []


if not API_KEY:
    raise RuntimeError("Missing API key. Please set IFOPEN_API_KEY (preferred) or OPENAI_API_KEY in your environment.")

print("==== API CONFIG ====")
print(f"  BASE_URL : {BASE_URL}")
print(f"  MODEL    : {MODEL_NAME}")
print(f"  MODEL_CANDIDATES : {MODEL_CANDIDATES}")
print(f"  API_KEY  : {_mask_key(API_KEY)}")
print(f"  GPT_TIMEOUT_SEC : {GPT_TIMEOUT_SEC}")
print(f"  GPT_MAX_RETRIES : {GPT_MAX_RETRIES}")
print(f"  TARGET_CODE_CHAR_LIMIT : {TARGET_CODE_CHAR_LIMIT}")
print(f"  CALIBRATION_CODE_CHAR_LIMIT : {CALIBRATION_CODE_CHAR_LIMIT}")
print(f"  CALIBRATION_PATH_LINE_LIMIT : {CALIBRATION_PATH_LINE_LIMIT}")
print(f"  INCLUDE_CALIBRATION_SOURCE : {INCLUDE_CALIBRATION_SOURCE}")
if EXTRA_HEADERS_JSON:
    print("  EXTRA_HEADERS_JSON : [provided]")
else:
    print("  EXTRA_HEADERS_JSON : [none]")
print("====================\n")
print("==== LOCAL TOOL CONFIG ====")
print(f"  CNIP_BIN : {CNIP_BIN}")
print(f"  LD_LIBRARY_PATH(add) : {':'.join([d for d in CNIP_LIB_DIRS if os.path.isdir(d)]) or '[none]'}")
print("===========================\n")


def run_with_timeout(cmd, timeout=80, env=None):
    print(f"      [run] CMD: {' '.join(cmd)}")
    try:
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, env=env)
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
    mems_match = re.search(r"MEMS:\s*(-?\d+)", output)
    mems_val = mems_match.group(1) if mems_match else ""
    time_match = re.search(r"\[DP TIME COST\]:\s*([\d\.]+)\s*seconds", output)
    time_val = time_match.group(1) if time_match else ""
    return mems_val, time_val


def _to_test_input_expr(raw_path: str) -> str:
    if not raw_path:
        return ""
    lines = []
    for ln in raw_path.splitlines():
        t = ln.strip()
        if not t:
            continue
        if not t.endswith(';'):
            t += ';'
        lines.append(t)
    if not lines:
        return ""
    return "[TEST INPUT PATH EXPR]:\n" + "\n".join(lines)


def extract_dfs_summary(output: str) -> Dict[str, str]:
    out: Dict[str, str] = {
        "dfs_time": "",
        "dfs_max_mems": "",
        "dfs_min_mems": "",
        "dfs_best_path": "",
    }
    m_time = re.search(r"\[DFS TIME COST\]:\s*([\d\.]+)\s*seconds", output)
    m_max = re.search(r"\[DFS MAX MEMS\]:\s*(-?\d+)", output)
    m_min = re.search(r"\[DFS MIN MEMS\]:\s*(-?\d+)", output)
    out["dfs_time"] = m_time.group(1) if m_time else ""
    out["dfs_max_mems"] = m_max.group(1) if m_max else ""
    out["dfs_min_mems"] = m_min.group(1) if m_min else ""

    target_mem = int(out["dfs_max_mems"]) if re.fullmatch(r"-?\d+", out["dfs_max_mems"]) else None
    best_mem = None
    best_path = ""
    fallback_mem = None
    fallback_path = ""

    feasible_matches = list(re.finditer(r"Path:(.*?)\nfeasible!!!\s*\n\[mem\]:\s*(-?\d+)", output, re.DOTALL))
    for m in feasible_matches:
        path_block = m.group(1).strip()
        mem = int(m.group(2))
        if fallback_mem is None or mem > fallback_mem:
            fallback_mem = mem
            fallback_path = path_block
        if target_mem is not None and mem == target_mem:
            best_mem = mem
            best_path = path_block
            break

    if not best_path and fallback_path:
        best_mem = fallback_mem
        best_path = fallback_path

    if best_path:
        out["dfs_best_path"] = _to_test_input_expr(best_path)
    elif not feasible_matches:
        if out["dfs_max_mems"] == "":
            out["dfs_max_mems"] = "-1"
        if out["dfs_min_mems"] == "":
            out["dfs_min_mems"] = "-1"
        out["dfs_best_path"] = "[NO FEASIBLE PATH]"

    return out


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
    if mems is None or (not isinstance(mems, int)):
        return False
    if mems == -1:
        return (path or "").strip() in ("", "[NO FEASIBLE PATH]")
    if mems < 0:
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
        if isinstance(mems, str) and re.fullmatch(r"-?\d+", mems):
            mems = int(mems)
        if not isinstance(mems, int):
            return None, ""
        if mems < -1:
            return None, ""
        path_expr = obj.get("test_input_path_expr", "")
        if mems == -1:
            path_expr = str(path_expr or "").strip()
            if path_expr not in ("", "[NO FEASIBLE PATH]"):
                path_expr = "[NO FEASIBLE PATH]"
            return mems, path_expr
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

    mems_rgx = re.search(r'"?mems"?\s*[:=]\s*"?(-?\d+)"?', unfenced, re.IGNORECASE)
    mems_val = int(mems_rgx.group(1)) if mems_rgx else None
    if mems_val == -1:
        return -1, "[NO FEASIBLE PATH]"
    path_block = _extract_path_block(unfenced)
    if _valid_mems_path(mems_val, path_block):
        return mems_val, path_block

    return None, ""


def _extract_predicates_from_path(path_expr: str) -> List[str]:
    out: List[str] = []
    if not path_expr or "[TEST INPUT PATH EXPR]:" not in path_expr:
        return out
    for ln in path_expr.splitlines()[1:]:
        t = ln.strip()
        if t.startswith("@(") and t.endswith(");"):
            out.append(t[2:-2].strip())
    return out


def _normalize_cond_text(cond: str) -> str:
    return re.sub(r"\s+", "", cond or "")


def _update_interval(interval: Dict[str, Any], op: str, val: int) -> bool:
    lb = interval.get("lb", None)
    ub = interval.get("ub", None)
    eq = interval.get("eq", None)
    neq = interval.setdefault("neq", set())

    if op == "==":
        if eq is not None and eq != val:
            return False
        if val in neq:
            return False
        if lb is not None and val < lb:
            return False
        if ub is not None and val > ub:
            return False
        interval["eq"] = val
        return True
    if op == "!=":
        if eq is not None and eq == val:
            return False
        neq.add(val)
        return True
    if op == ">":
        lb2 = val + 1
        interval["lb"] = lb2 if lb is None else max(lb, lb2)
    elif op == ">=":
        interval["lb"] = val if lb is None else max(lb, val)
    elif op == "<":
        ub2 = val - 1
        interval["ub"] = ub2 if ub is None else min(ub, ub2)
    elif op == "<=":
        interval["ub"] = val if ub is None else min(ub, val)

    lb = interval.get("lb", None)
    ub = interval.get("ub", None)
    eq = interval.get("eq", None)
    if lb is not None and ub is not None and lb > ub:
        return False
    if eq is not None and ((lb is not None and eq < lb) or (ub is not None and eq > ub) or (eq in neq)):
        return False
    return True


def _judge_path_feasible_local(path_expr: str) -> Tuple[str, str]:
    if not path_expr:
        return "unknown", "empty_path"
    p = path_expr.strip()
    if p == "[NO FEASIBLE PATH]":
        return "true", "explicit_no_feasible_path_marker"
    if "[TEST INPUT PATH EXPR]:" not in p:
        return "false", "missing_path_header"

    predicates = _extract_predicates_from_path(p)
    norms = {_normalize_cond_text(x) for x in predicates if x.strip()}
    for n in list(norms):
        if n.startswith("!") and n[1:] in norms:
            return "false", f"contradictory_predicates:{n} vs {n[1:]}"
        if ("!" + n) in norms:
            return "false", f"contradictory_predicates:{n} vs !{n}"

    var_constraints: Dict[str, Dict[str, Any]] = {}
    atom_re = re.compile(r"^([A-Za-z_]\w*)\s*(==|!=|<=|>=|<|>)\s*(-?\d+)$")
    for cond in predicates:
        parts = re.split(r"&&|\|\|", cond)
        for part in parts:
            c = part.strip()
            if c.startswith("(") and c.endswith(")"):
                c = c[1:-1].strip()
            m = atom_re.fullmatch(c)
            if not m:
                continue
            vname, op, sval = m.group(1), m.group(2), int(m.group(3))
            slot = var_constraints.setdefault(vname, {})
            if not _update_interval(slot, op, sval):
                return "false", f"numeric_constraint_conflict:{vname}"

    return "true", "no_obvious_conflict_by_local_parser"


def judge_path_feasibility(cfile: str, code_text: str, path_expr: str) -> Tuple[str, str, str]:
    if EPATH_FEASIBILITY_API:
        try:
            resp = requests.post(
                EPATH_FEASIBILITY_API,
                json={
                    "filename": os.path.basename(cfile),
                    "code": code_text,
                    "test_input_path_expr": path_expr,
                },
                timeout=EPATH_FEASIBILITY_TIMEOUT,
            )
            if resp.status_code == 200:
                data = resp.json() if resp.text.strip() else {}
                feasible_raw = str(
                    data.get("feasible", data.get("is_feasible", data.get("result", data.get("status", "unknown"))))
                ).strip().lower()
                reason = str(data.get("reason", data.get("message", ""))).strip() or "api_ok"
                if feasible_raw in ("true", "1", "yes", "feasible", "ok"):
                    return "true", reason, "api"
                if feasible_raw in ("false", "0", "no", "infeasible", "fail"):
                    return "false", reason, "api"
                return "unknown", reason, "api"
            return "unknown", f"api_http_{resp.status_code}", "api"
        except Exception as e:
            return "unknown", f"api_exception:{short_err(str(e), 120)}", "api"
    local_judge, local_reason = _judge_path_feasible_local(path_expr)
    return local_judge, local_reason, "local_parser"


def _sanitize_feedback_for_prompt(text: str) -> str:
    if not text:
        return ""
    s = str(text)
    s = re.sub(r"\[TEST INPUT PATH EXPR\]:[\s\S]*", "[PATH_HIDDEN]", s)
    s = re.sub(
        r"\b(dp_mems|dfs_max_mems|dfs_min_mems|gpt_mems|gpt_dp_mems_diff|gpt_dfs_mems_diff|dp_dfs_mems_diff|diff)\s*[:=]\s*-?\d+",
        r"\1=[hidden]",
        s,
        flags=re.IGNORECASE,
    )
    s = re.sub(r"\b(dp|dfs|gpt)\s*=\s*-?\d+", r"\1=[hidden]", s, flags=re.IGNORECASE)
    s = re.sub(r"\bmems\s*=\s*-?\d+", "mems=[hidden]", s, flags=re.IGNORECASE)
    s = re.sub(r"目标\s*dp_mems\s*=\s*-?\d+", "目标dp_mems=[hidden]", s, flags=re.IGNORECASE)
    s = re.sub(r"硬校准目标\s*:\s*dp_mems\s*=\s*-?\d+", "硬校准目标: dp_mems=[hidden]", s, flags=re.IGNORECASE)
    s = re.sub(r"GPT\s*=\s*-?\d+\s*与\s*DP\s*=\s*-?\d+", "GPT与DP数值不一致", s, flags=re.IGNORECASE)
    s = re.sub(r"gpt\s*=\s*-?\d+\s*,\s*dp\s*=\s*-?\d+\s*,\s*diff\s*=\s*-?\d+", "gpt/dp/diff=[hidden]", s, flags=re.IGNORECASE)
    s = re.sub(r"DFS给出可行mems\s*=\s*-?\d+", "DFS给出可行结果", s)
    return s.strip()

def _to_optional_int(v: Any) -> Optional[int]:
    if isinstance(v, int):
        return v
    if isinstance(v, str) and re.fullmatch(r"-?\d+", v.strip()):
        return int(v.strip())
    return None


def _direction_feedback(gpt_val: Any, target_val: Any, label: str = "外部目标结果") -> str:
    g = _to_optional_int(gpt_val)
    t = _to_optional_int(target_val)
    if g is None or t is None:
        return ""
    if g > t:
        return (
            f"方向反馈: 上轮输出的 MEMS 高于{label}。"
            "请重点排查是否过计数了隐含临时量、重复计算左值、把未实际执行的短路分支也计入、"
            "或把不可行/超出循环上限的路径当成候选。"
        )
    if g < t:
        return (
            f"方向反馈: 上轮输出的 MEMS 低于{label}。"
            "请重点排查是否漏算了条件读、数组下标读、指针/结构体访问、函数实参读、return变量读、"
            "循环最终退出条件，或漏掉了更高MEMS的可行分支。"
        )
    return (
        f"方向反馈: 上轮输出的 MEMS 与{label}数值方向上已对齐，但仍未完全通过一致性检查。"
        "请重点排查路径表达式、分支顺序、循环退出条件和可行性谓词。"
    )


def _public_counting_examples() -> str:
    return (
        "Counting examples (method only):\n"
        "- x=y+z => read(y)+read(z)+write(x)=3.\n"
        "- i++ => read(i)+write(i)=2.\n"
        "- if (a&&b) x=x+1 true branch => read(a)+read(b)+read(x)+write(x)=4; if a is false => read(a)=1.\n"
        "- arr[i]=arr[i]+v => RHS read(i)+read(arr[i])+read(v), LHS read(i)+write(arr[i]) => 5.\n"
        "- while(i<n){i++;} with 2 taken + final exit => 3 condition checks*(read i+n) + 2 updates*(read+write i)=10.\n"
    )



def _compact_for_prompt(text: str, max_chars: int) -> str:
    if not text:
        return ""
    t = str(text).strip()
    if max_chars <= 0 or len(t) <= max_chars:
        return t
    head = max_chars // 2
    tail = max_chars - head - 80
    if tail < 0:
        tail = 0
    return t[:head].rstrip() + "\n... [truncated for prompt] ...\n" + t[-tail:].lstrip()


def _compact_path_for_prompt(path_expr: str, max_lines: int = None, max_chars: int = None) -> str:
    if not path_expr:
        return ""
    if max_lines is None:
        max_lines = CALIBRATION_PATH_LINE_LIMIT
    if max_chars is None:
        max_chars = max(600, CALIBRATION_CODE_CHAR_LIMIT)
    lines = [ln.rstrip() for ln in str(path_expr).splitlines() if ln.strip()]
    if max_lines > 0 and len(lines) > max_lines:
        half = max_lines // 2
        tail = max_lines - half - 1
        lines = lines[:half] + ["... [path truncated for prompt] ..."] + (lines[-tail:] if tail > 0 else [])
    return _compact_for_prompt("\n".join(lines), max_chars)


def _format_calibration_examples_for_prompt() -> str:
    if not CALIBRATION_EXAMPLES:
        return ""
    parts: List[str] = []
    parts.append(
        "Fixed calibration examples: use them only to learn counting style; do not infer the current file's hidden answer."
    )
    for idx, ex in enumerate(CALIBRATION_EXAMPLES[:CALIBRATION_MAX_EXAMPLES], 1):
        name = str(ex.get("basename", f"calibration_{idx}"))
        dp_mems = str(ex.get("dp_mems", "")).strip()
        dp_path = _compact_path_for_prompt(str(ex.get("dp_path", "")), CALIBRATION_PATH_LINE_LIMIT, max(600, CALIBRATION_CODE_CHAR_LIMIT))
        agree_note = str(ex.get("agree_note", "")).strip()
        part: List[str] = []
        part.append(f"Example {idx}: {name}")
        if dp_mems:
            part.append(f"analyzer_mems={dp_mems}")
        if dp_path:
            part.append("analyzer_path_snippet:")
            part.append(dp_path)
        if INCLUDE_CALIBRATION_SOURCE:
            code_excerpt = _compact_for_prompt(str(ex.get("code_excerpt", "")), CALIBRATION_CODE_CHAR_LIMIT)
            if code_excerpt:
                part.append("source_excerpt:")
                part.append(code_excerpt)
        if agree_note:
            part.append(agree_note)
        parts.append("\n".join(part))
    return "\n\n" + "\n\n".join(parts) + "\n"


def _calibration_example_exists(basename: str) -> bool:
    return any(str(ex.get("basename", "")) == basename for ex in CALIBRATION_EXAMPLES)


def _build_calibration_method_summary(rows: List[Dict[str, Any]]) -> str:
    if not rows:
        return ""
    high = 0
    low = 0
    equal_bad = 0
    parse_bad = 0
    infeasible_bad = 0
    for r in rows:
        if not r.get("success_gpt", False):
            parse_bad = parse_bad + 1
            continue
        if r.get("success_gpt", False) and str(r.get("gpt_mems", "")).strip() != "-1" and r.get("eppath_feasible", "unknown") != "true":
            infeasible_bad = infeasible_bad + 1
        g = _to_optional_int(r.get("gpt_mems", ""))
        d = _to_optional_int(r.get("dp_mems", ""))
        if g is None or d is None:
            continue
        if g > d:
            high = high + 1
        elif g < d:
            low = low + 1
        elif not r.get("gpt_eq_dp_mems", False):
            equal_bad = equal_bad + 1
    out: List[str] = []
    if high > 0:
        out.append(f"校准集方向统计: 有 {high} 个样例输出高于校准目标；优先减少隐含临时量、重复左值、未执行短路分支和超界循环路径的过计数。")
    if low > 0:
        out.append(f"校准集方向统计: 有 {low} 个样例输出低于校准目标；优先补充条件读、数组下标读、指针/结构体访问、函数实参读、return变量读、循环最终退出条件。")
    if equal_bad > 0:
        out.append(f"校准集方向统计: 有 {equal_bad} 个样例MEMS方向接近但路径未完全通过；优先修正路径顺序、谓词格式和循环退出条件。")
    if parse_bad > 0:
        out.append(f"校准集方向统计: 有 {parse_bad} 个样例输出解析失败；必须保持严格JSON和路径格式。")
    if infeasible_bad > 0:
        out.append(f"校准集方向统计: 有 {infeasible_bad} 个样例路径可行性失败；必须消除矛盾谓词。")
    return " ".join(out).strip()

def build_system_prompt() -> str:
    base = (
        "You are a C static-analysis assistant. Derive a feasible bounded path with maximum MEMS from source.\n"
        f"Bounds: loop_unroll={MAX_LOOP}, inline_depth={MAX_INLINE}. Recursion is bounded/fixpoint-style; never expand unboundedly.\n"
        "MEMS rules: variable read +1, lvalue write +1; count locals/params/globals, arrays, fields, pointer derefs, conditions, function args, return variable reads. "
        "Assignment counts RHS reads + one LHS write. ++/-- and compound assignments count read+write. Respect &&/|| short-circuit. "
        "Ignore constants, keywords, declarations without side effects, ABI/register/hidden temporary operations.\n"
        "Path rules: source execution order; reject contradictory predicates; for loops emit taken guards and final exit guard when applicable; do not invent statements.\n"
        "Calibration rule: fixed examples below may teach counting style. For the current file, never use or guess hidden DP/DFS values or paths; use only source plus direction feedback.\n"
        + _public_counting_examples()
        + _format_calibration_examples_for_prompt()
        + "Output STRICT JSON only: {\"mems\": integer, \"test_input_path_expr\": string, \"reason\": string}. "
          "Path string format: [TEST INPUT PATH EXPR]: then one @(cond); or stmt; per line. Every path line ends with ';'. "
          "If no feasible bounded path exists: mems=-1 and test_input_path_expr='[NO FEASIBLE PATH]'."
    )
    if PROMPT_FEEDBACK_HISTORY:
        safe_feedback = [_sanitize_feedback_for_prompt(x) for x in PROMPT_FEEDBACK_HISTORY[-3:]]
        safe_feedback = [x for x in safe_feedback if x]
        if safe_feedback:
            base += "\nRecent diagnostic feedback (no target values):\n" + "\n".join(f"- {x}" for x in safe_feedback)
    return base


def build_user_prompt(code: str, guidance: str = "") -> str:
    code_for_prompt = _compact_for_prompt(code, TARGET_CODE_CHAR_LIMIT)
    prompt = (
        "Analyze the following C file. Return the feasible bounded MAX-MEMS path. "
        "Use source code only for this target file; calibration examples are method examples only.\n"
        "Steps: build constraints, enumerate feasible paths, count MEMS, choose max, self-check.\n\n"
        "-----BEGIN C CODE-----\n"
        f"{code_for_prompt}\n"
        "-----END C CODE-----"
    )
    if guidance:
        safe_guidance = _sanitize_feedback_for_prompt(guidance)
        if safe_guidance:
            prompt += f"\n\nDiagnostic feedback, no DP/DFS answer values:\n{safe_guidance}"
    return prompt


def record_prompt_snapshot(tag: str, note: str = "") -> None:
    try:
        snap = {
            "tag": tag,
            "note": note,
            "feedback_count": len(PROMPT_FEEDBACK_HISTORY),
            "feedback_tail": [_sanitize_feedback_for_prompt(x) for x in PROMPT_FEEDBACK_HISTORY[-6:]],
            "prompt": build_system_prompt(),
        }
        PROMPT_SNAPSHOTS.append(snap)
    except Exception as e:
        PROMPT_SNAPSHOTS.append({
            "tag": tag,
            "note": f"{note} | snapshot_error={e}",
            "feedback_count": len(PROMPT_FEEDBACK_HISTORY),
            "feedback_tail": [_sanitize_feedback_for_prompt(x) for x in PROMPT_FEEDBACK_HISTORY[-6:]],
            "prompt": "",
        })


def _format_file_guidance(entry: Dict[str, Any], filename: str) -> str:
    hints: List[str] = []
    base = os.path.basename(filename)

    if base in FILE_FEEDBACK_HISTORY and FILE_FEEDBACK_HISTORY[base]:
        hints.extend(FILE_FEEDBACK_HISTORY[base][-3:])

    if PROMPT_FEEDBACK_HISTORY:
        safe_global = [_sanitize_feedback_for_prompt(x) for x in PROMPT_FEEDBACK_HISTORY[-2:]]
        safe_global = [x for x in safe_global if x]
        if safe_global:
            hints.append("全局近期方法级失败摘要: " + " || ".join(safe_global))

    if not hints:
        hints.append(
            "本文件没有答案级提示。请只根据源码重新进行约束构造、可行路径枚举、显式读写计数和路径自检。"
        )

    cleaned: List[str] = []
    for item in hints:
        t = _sanitize_feedback_for_prompt(str(item))
        if t:
            cleaned.append(t)

    return "\n".join(cleaned).strip()


def _record_file_feedback(entry: Dict[str, Any]) -> None:
    base = entry.get("basename", "")
    if not base:
        return

    fb: List[str] = []

    if entry.get("success_dp", False) and (not entry.get("gpt_eq_dp_mems", False)):
        direction = _direction_feedback(entry.get("gpt_mems", ""), entry.get("dp_mems", ""), "外部目标结果")
        if direction:
            fb.append(f"{base}: {direction}")
        else:
            fb.append(
                f"{base}: 上轮输出未通过外部一致性检查。"
                "下轮不要猜测目标MEMS；必须从源码重新枚举可行路径并逐行统计显式读写。"
            )

    if entry.get("success_dfs", False) and (not entry.get("gpt_eq_dfs_mems", False)):
        dfs_direction = _direction_feedback(entry.get("gpt_mems", ""), entry.get("dfs_max_mems", ""), "外部可行路径参考")
        if dfs_direction:
            fb.append(f"{base}: {dfs_direction}")
        else:
            fb.append(
                f"{base}: 上轮输出未通过可行路径/最大路径一致性检查。"
                "下轮重点复查分支可行性、循环展开上限、短路逻辑和路径顺序。"
            )

    if not entry.get("success_gpt", False):
        fb.append(
            f"{base}: 上轮 GPT 输出解析失败。"
            "下轮必须返回严格 JSON，且 test_input_path_expr 必须符合路径格式。"
        )

    if (
        entry.get("success_gpt", False)
        and str(entry.get("gpt_mems", "")).strip() != "-1"
        and entry.get("eppath_feasible", "unknown") != "true"
    ):
        fb.append(
            f"{base}: 上轮路径可行性检查失败或不确定。"
            "下轮必须避免冲突谓词，确保所有分支条件能在同一次具体执行中同时成立。"
        )

    if fb:
        safe_fb = [_sanitize_feedback_for_prompt(x) for x in fb[-3:]]
        safe_fb = [x for x in safe_fb if x]
        FILE_FEEDBACK_HISTORY.setdefault(base, []).extend(safe_fb)

def _parse_batch_stages(max_total: int) -> List[int]:
    vals: List[int] = []
    for part in AUTO_BATCH_STAGES_ENV.split(","):
        t = part.strip()
        if not t:
            continue
        if t.isdigit():
            n = int(t)
            if n > 0:
                vals.append(n)
    if not vals:
        vals = [5, 10, 20, 100, 1000]
    out: List[int] = []
    seen = set()
    for n in vals:
        k = min(n, max_total)
        if k > 0 and k not in seen:
            out.append(k)
            seen.add(k)
    if max_total > 0 and max_total not in seen:
        out.append(max_total)
    return out


def _safe_variance(vals: List[float]) -> float:
    if not vals or len(vals) <= 1:
        return 0.0
    mean = sum(vals) / len(vals)
    return sum((x - mean) ** 2 for x in vals) / len(vals)


def _stage_accuracy(rows: List[Dict[str, Any]]) -> float:
    if not rows:
        return 0.0
    hits = sum(1 for r in rows if r.get("gpt_eq_dp_mems", False))
    return hits / len(rows)


def _add_feedback_from_failures(failed_entries: List[Dict[str, Any]]) -> str:
    reasons: List[str] = []
    examples: List[str] = []

    for e in failed_entries[:10]:
        name = e.get("basename", "")
        if not e.get("success_gpt", False):
            reasons.append(
                f"{name}: GPT输出失败或解析失败，需要严格返回 JSON，并保证路径格式可解析。"
            )
        if not e.get("success_dfs", False):
            reasons.append(
                f"{name}: 外部可行路径检查阶段失败。下轮应更谨慎处理分支谓词、循环退出条件和不可达路径。"
            )
        if not e.get("success_dp", False):
            reasons.append(
                f"{name}: 外部最大路径评估阶段失败。下轮应检查路径格式、源码执行顺序和计数自洽性。"
            )
        if (
            e.get("success_gpt", False)
            and str(e.get("gpt_mems", "")).strip() != "-1"
            and e.get("eppath_feasible", "unknown") != "true"
        ):
            reasons.append(
                f"{name}: 输出路径未通过可行性检查。请修正分支谓词矛盾，确保路径能由同一次具体执行产生。"
            )
        if (
            e.get("success_gpt", False)
            and e.get("success_dp", False)
            and (not e.get("gpt_eq_dp_mems", False))
        ):
            direction = _direction_feedback(e.get("gpt_mems", ""), e.get("dp_mems", ""), "外部目标结果")
            if direction:
                reasons.append(f"{name}: {direction}")
            else:
                reasons.append(
                    f"{name}: 输出未通过外部一致性检查。不要使用目标数值校准；请从源码重新枚举候选并逐行计数。"
                )
            if len(examples) < 3:
                examples.append(
                    f"方法样例{len(examples)+1}: `x = y + z;` 应计为 read(y)+read(z)+write(x)，总计3。"
                )
            if len(examples) < 3:
                examples.append(
                    f"方法样例{len(examples)+1}: `if (a && b) x = x + 1;` 真分支计 read(a)+read(b)+read(x)+write(x)，总计4；若 a 为假，条件短路只计 read(a)。"
                )
            if len(examples) < 3:
                examples.append(
                    f"方法样例{len(examples)+1}: `arr[i] = arr[i] + v;` 计 RHS 的 read(i)+read(arr[i])+read(v) 与 LHS 的 read(i)+write(arr[i])，总计5。"
                )

    if not reasons:
        reasons.append("批量执行出现失败，请提高路径可行性、路径格式稳定性和 MEMS 计数自洽性。")

    feedback = " | ".join(reasons[:6])
    if examples:
        feedback += " | " + " | ".join(examples[:3])
    feedback = _sanitize_feedback_for_prompt(feedback)
    PROMPT_FEEDBACK_HISTORY.append(feedback)
    return feedback

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


def _is_model_access_error(resp_status: int, message: str, code: str) -> bool:
    msg = (message or "").lower()
    code_s = (code or "").lower()
    if resp_status in (401, 403):
        return True
    keys = ["no access", "not allowed", "not found", "does not exist", "permission", "model"]
    if any(k in msg for k in keys):
        return True
    if any(k in code_s for k in ["model", "permission", "access"]):
        return True
    return False


def call_gpt_for_mems(code: str, max_retries: int = None, timeout_sec: int = None, guidance: str = "") -> Tuple[Optional[int], str, str]:
    if max_retries is None:
        max_retries = GPT_MAX_RETRIES
    if timeout_sec is None:
        timeout_sec = GPT_TIMEOUT_SEC

    url = f"{BASE_URL.rstrip('/')}/chat/completions"
    headers = {
        "Authorization": f"Bearer {API_KEY}",
        "Content-Type": "application/json",
    }
    headers.update(_load_extra_headers())

    system_prompt = build_system_prompt()
    user_prompt = build_user_prompt(code, guidance=guidance)
    print(
        f"      [GPT] prompt chars: system={len(system_prompt)}, user={len(user_prompt)}, "
        f"timeout={timeout_sec}s, retries={max_retries}"
    )

    last_text = ""
    for model_name in MODEL_CANDIDATES:
        print(f"      [GPT] trying model: {model_name}")
        for attempt in range(max_retries + 1):
            payload = {
                "model": model_name,
                "messages": [
                    {"role": "system", "content": system_prompt},
                    {"role": "user", "content": user_prompt},
                ],
                "temperature": 0.0,
            }

            try:
                resp = requests.post(url, headers=headers, json=payload, timeout=timeout_sec)

                if resp.status_code != 200:
                    err_info = _extract_api_error(resp.text)
                    msg = err_info.get("message", "")
                    typ = err_info.get("type", "")
                    code_ = err_info.get("code", "")
                    line = f"model={model_name} [HTTP {resp.status_code}] type={typ} code={code_} msg={msg}"
                    line = _sanitize_secrets(line)
                    print(f"      [GPT] HTTP error: {short_err(line, 380)}")
                    last_text = line
                    if _is_model_access_error(resp.status_code, msg, code_):
                        break
                    if resp.status_code in (408, 409, 429, 500, 502, 503, 504):
                        time.sleep(1.5)
                        continue
                    break

                try:
                    data = resp.json()
                except Exception as e:
                    content_type = resp.headers.get("Content-Type", "")
                    body_preview = (resp.text or "").strip()
                    if len(body_preview) > 800:
                        body_preview = body_preview[:800] + " ... [truncated]"
                    last_text = _sanitize_secrets(
                        f"model={model_name} [HTTP {resp.status_code}] non-json response; "
                        f"content-type={content_type}; json_error={repr(e)}; body={body_preview}"
                    )
                    print(f"      [GPT] Non-JSON response: {short_err(last_text, 500)}")
                    break

                text = _extract_content_from_response(data).strip()
                last_text = text

                mems, path_expr = parse_gpt_output(last_text)
                if mems is not None and path_expr:
                    return mems, path_expr, last_text

                print("      [GPT] Parse failed, retrying...")
                time.sleep(1.0)
            except requests.exceptions.ReadTimeout as e:
                last_text = _sanitize_secrets(f"[TIMEOUT] model={model_name} timeout={timeout_sec}s {repr(e)}")
                print(f"      [GPT] Timeout: {short_err(last_text, 300)}")
                if SWITCH_MODEL_ON_TIMEOUT:
                    break
                time.sleep(1.0)
            except requests.exceptions.Timeout as e:
                last_text = _sanitize_secrets(f"[TIMEOUT] model={model_name} timeout={timeout_sec}s {repr(e)}")
                print(f"      [GPT] Timeout: {short_err(last_text, 300)}")
                if SWITCH_MODEL_ON_TIMEOUT:
                    break
                time.sleep(1.0)
            except requests.exceptions.RequestException as e:
                last_text = _sanitize_secrets(f"[REQUEST_EXCEPTION] model={model_name} {repr(e)}")
                print(f"      [GPT] Request exception: {short_err(last_text, 300)}")
                break
            except Exception as e:
                last_text = _sanitize_secrets(f"[EXCEPTION] {repr(e)}\n{traceback.format_exc()}")
                print(f"      [GPT] Exception: {short_err(last_text)}")
                time.sleep(1.0)

    return None, "", last_text


def main():
    print("==== 扫描目标文件夹 ====")
    search_pattern = os.path.join(INPUT_FOLDER, INPUT_GLOB)
    c_files = glob.glob(search_pattern, recursive=INPUT_RECURSIVE)
    c_files = [p for p in c_files if os.path.isfile(p) and p.lower().endswith(".c")]
    c_files = sorted(set(os.path.abspath(p) for p in c_files))
    if MAX_FILES > 0:
        c_files = c_files[:MAX_FILES]
    print(
        f"  {INPUT_FOLDER}: 找到 {len(c_files)} 个 .c 文件 "
        f"(glob={INPUT_GLOB}, recursive={INPUT_RECURSIVE}, max_files={MAX_FILES})"
    )

    print(f"== 共 {len(c_files)} 个 C 文件将被处理 ==\n")
    if not c_files:
        print("[终止] 未在指定文件夹下发现任何 .c 文件。")
        return

    os.makedirs(OUTPUT_TRUE_FOLDER, exist_ok=True)
    analyzer_cache: Dict[str, Dict[str, Any]] = {}
    latest_stage_results: List[Dict[str, Any]] = []

    def _print_stage_summary(tag: str, rows: List[Dict[str, Any]]) -> None:
        total = len(rows)
        if total == 0:
            print(f"[{tag}] 空结果")
            return
        g_ok = sum(1 for r in rows if r.get("success_gpt", False))
        d_ok = sum(1 for r in rows if r.get("success_dp", False))
        f_ok = sum(1 for r in rows if r.get("success_dfs", False))
        g_eq_d = sum(1 for r in rows if r.get("gpt_eq_dp_mems", False))
        g_eq_f = sum(1 for r in rows if r.get("gpt_eq_dfs_mems", False))
        print(
            f"[{tag}] total={total}, GPT成功={g_ok}, DP成功={d_ok}, DFS成功={f_ok}, "
            f"GPT=DP={g_eq_d}, GPT=DFS={g_eq_f}"
        )

    def prepare_calibration_examples(files: List[str]) -> None:
        if CALIBRATION_EXAMPLES:
            print(f"[校准集] 已存在 {len(CALIBRATION_EXAMPLES)} 个校准样例，复用。")
            return
        if not files:
            print("[校准集] 无可用校准文件。")
            return
        print(f"\n==== 构建方法校准集: 前 {len(files)} 个文件 ====")
        for idx, cfile in enumerate(files):
            base = os.path.basename(cfile)
            print(f"  [校准 {idx+1}/{len(files)}] {base}")
            try:
                with open(cfile, "r", encoding="utf-8", errors="ignore") as f:
                    code_text = f.read()
            except Exception as e:
                print(f"    [跳过] 读取源码失败: {e}")
                continue

            cache_key = os.path.abspath(cfile)
            cached = analyzer_cache.get(cache_key)
            if cached is None:
                entry: Dict[str, Any] = {"filename": cfile, "basename": base}
                print(f"    [校准工具] 执行 DFS: {CNIP_BIN} -q {cfile}")
                out_f, err_f, ret_f = run_with_timeout([CNIP_BIN, "-q", cfile], timeout=300, env=RUN_ENV)
                dfs_error, dfs_reason = error_status(out_f, err_f, ret_f, r"\[DFS TIME COST\]:\s*([\d\.]+)\s*seconds")
                if dfs_error:
                    entry.update({"dfs_time": "error", "dfs_max_mems": "error", "dfs_min_mems": "error", "dfs_best_path": "", "dfs_error": dfs_reason})
                    success_dfs = False
                    print(f"    [DFS失败] {dfs_reason}")
                else:
                    dfs_info = extract_dfs_summary(out_f)
                    entry.update({
                        "dfs_time": dfs_info.get("dfs_time", ""),
                        "dfs_max_mems": dfs_info.get("dfs_max_mems", ""),
                        "dfs_min_mems": dfs_info.get("dfs_min_mems", ""),
                        "dfs_best_path": dfs_info.get("dfs_best_path", ""),
                        "dfs_error": "",
                    })
                    success_dfs = True
                    print(f"    [DFS OK] max mems: {entry['dfs_max_mems']}")

                print(f"    [校准工具] 执行 DP: {CNIP_BIN} -g {cfile}")
                out_g, err_g, ret_g = run_with_timeout([CNIP_BIN, "-g", cfile], timeout=300, env=RUN_ENV)
                dp_error, dp_reason = error_status(out_g, err_g, ret_g, r"\[DP TIME COST\]:\s*([\d\.]+)\s*seconds")
                if dp_error:
                    entry.update({"dp_time": "error", "dp_mems": "error", "dp_path": "", "dp_error": dp_reason})
                    success_dp = False
                    print(f"    [DP失败] {dp_reason}")
                else:
                    dp_mems, dp_time = extract_greedy(out_g)
                    path_match = re.search(r"(\[TEST INPUT PATH EXPR\]:\s*[\s\S]+?)(?=\n*\[DP TIME COST\]:|\Z)", out_g)
                    entry.update({
                        "dp_mems": dp_mems,
                        "dp_time": dp_time,
                        "dp_error": "",
                        "dp_path": path_match.group(1).strip() if path_match else "",
                    })
                    success_dp = True
                    print(f"    [DP OK] mems: {dp_mems}")

                cached = {
                    "dfs_time": entry.get("dfs_time", "error"),
                    "dfs_max_mems": entry.get("dfs_max_mems", "error"),
                    "dfs_min_mems": entry.get("dfs_min_mems", "error"),
                    "dfs_best_path": entry.get("dfs_best_path", ""),
                    "dfs_error": entry.get("dfs_error", ""),
                    "dp_time": entry.get("dp_time", "error"),
                    "dp_mems": entry.get("dp_mems", "error"),
                    "dp_path": entry.get("dp_path", ""),
                    "dp_error": entry.get("dp_error", ""),
                    "success_dfs": success_dfs,
                    "success_dp": success_dp,
                }
                analyzer_cache[cache_key] = cached
            else:
                print("    [校准工具] 复用缓存的 DFS/DP 结果。")

            if not cached.get("success_dp", False):
                print("    [跳过] DP 不成功，不能作为校准样例。")
                continue

            dp_val = str(cached.get("dp_mems", "")).strip()
            if not re.fullmatch(r"-?\d+", dp_val):
                print("    [跳过] DP MEMS 不可解析，不能作为校准样例。")
                continue

            agree_note = ""
            dfs_val = str(cached.get("dfs_max_mems", "")).strip()
            if cached.get("success_dfs", False) and re.fullmatch(r"-?\d+", dfs_val):
                agree_note = "DFS and DP agree on MEMS for this calibration example." if dfs_val == dp_val else "DFS and DP differ on this calibration example; prefer DP counting style."

            CALIBRATION_EXAMPLES.append({
                "filename": cfile,
                "basename": base,
                "code_excerpt": _compact_for_prompt(code_text, CALIBRATION_CODE_CHAR_LIMIT),
                "dp_mems": dp_val,
                "dp_path": cached.get("dp_path", ""),
                "dfs_max_mems": dfs_val,
                "agree_note": agree_note,
            })

            if len(CALIBRATION_EXAMPLES) >= CALIBRATION_MAX_EXAMPLES:
                break

        print(f"[校准集] 已构建 {len(CALIBRATION_EXAMPLES)} 个校准样例。")

    def process_files(files: List[str]) -> List[Dict[str, Any]]:
        local_results: List[Dict[str, Any]] = []
        for idx, cfile in enumerate(files):
            print(f"\n====== 文件 {idx+1}/{len(files)}: {cfile} ======")
            entry = {"filename": cfile, "basename": os.path.basename(cfile)}
            try:
                with open(cfile, "r", encoding="utf-8", errors="ignore") as f:
                    code_text = f.read()
            except Exception as e:
                print(f"  [失败] 读取源码失败: {e}")
                entry.update({"gpt_time": "error", "gpt_mems": "error", "gpt_path": "", "gpt_error": "read_source_fail",
                              "dfs_time": "error", "dfs_max_mems": "error", "dfs_min_mems": "error", "dfs_best_path": "", "dfs_error": "read_source_fail",
                              "dp_time": "error", "dp_mems": "error", "dp_path": "", "dp_error": "read_source_fail"})
                success_gpt, success_dfs, success_dp = False, False, False
            else:
                cache_key = os.path.abspath(cfile)
                cached = analyzer_cache.get(cache_key)
                if cached is None:
                    print(f"  [1/3] 执行 DFS 完全遍历(仅首轮/首见执行): {CNIP_BIN} -q {cfile}")
                    out_f, err_f, ret_f = run_with_timeout([CNIP_BIN, "-q", cfile], timeout=300, env=RUN_ENV)
                    dfs_error, dfs_reason = error_status(out_f, err_f, ret_f, r"\[DFS TIME COST\]:\s*([\d\.]+)\s*seconds")
                    if dfs_error:
                        print(f"  [失败] DFS 阶段错误类型: {dfs_reason}")
                        entry.update({"dfs_time": "error", "dfs_max_mems": "error", "dfs_min_mems": "error", "dfs_best_path": "", "dfs_error": dfs_reason})
                        success_dfs = False
                    else:
                        dfs_info = extract_dfs_summary(out_f)
                        entry.update({"dfs_time": dfs_info.get("dfs_time", ""), "dfs_max_mems": dfs_info.get("dfs_max_mems", ""),
                                      "dfs_min_mems": dfs_info.get("dfs_min_mems", ""), "dfs_best_path": dfs_info.get("dfs_best_path", ""), "dfs_error": ""})
                        print(f"  [OK] DFS time: {entry['dfs_time']} | max mems: {entry['dfs_max_mems']} | min mems: {entry['dfs_min_mems']}")
                        success_dfs = True

                    print(f"  [2/3] 执行 DP/Greedy(仅首轮/首见执行): {CNIP_BIN} -g {cfile}")
                    out_g, err_g, ret_g = run_with_timeout([CNIP_BIN, "-g", cfile], timeout=300, env=RUN_ENV)
                    dp_error, dp_reason = error_status(out_g, err_g, ret_g, r"\[DP TIME COST\]:\s*([\d\.]+)\s*seconds")
                    if dp_error:
                        print(f"  [失败] DP 阶段错误类型: {dp_reason}")
                        entry.update({"dp_time": "error", "dp_mems": "error", "dp_path": "", "dp_error": dp_reason})
                        success_dp = False
                    else:
                        dp_mems, dp_time = extract_greedy(out_g)
                        path_match = re.search(r"(\[TEST INPUT PATH EXPR\]:\s*[\s\S]+?)(?=\n*\[DP TIME COST\]:|\Z)", out_g)
                        entry.update({"dp_mems": dp_mems, "dp_time": dp_time, "dp_error": "", "dp_path": path_match.group(1).strip() if path_match else ""})
                        print(f"  [OK] DP time: {dp_time} | mems: {dp_mems}")
                        success_dp = True

                    analyzer_cache[cache_key] = {
                        "dfs_time": entry.get("dfs_time", "error"),
                        "dfs_max_mems": entry.get("dfs_max_mems", "error"),
                        "dfs_min_mems": entry.get("dfs_min_mems", "error"),
                        "dfs_best_path": entry.get("dfs_best_path", ""),
                        "dfs_error": entry.get("dfs_error", ""),
                        "dp_time": entry.get("dp_time", "error"),
                        "dp_mems": entry.get("dp_mems", "error"),
                        "dp_path": entry.get("dp_path", ""),
                        "dp_error": entry.get("dp_error", ""),
                        "success_dfs": success_dfs,
                        "success_dp": success_dp,
                    }
                else:
                    print("  [1/3] 复用缓存的 DFS/DP 结果（回溯阶段不重复执行）。")
                    entry.update({
                        "dfs_time": cached.get("dfs_time", "error"),
                        "dfs_max_mems": cached.get("dfs_max_mems", "error"),
                        "dfs_min_mems": cached.get("dfs_min_mems", "error"),
                        "dfs_best_path": cached.get("dfs_best_path", ""),
                        "dfs_error": cached.get("dfs_error", ""),
                        "dp_time": cached.get("dp_time", "error"),
                        "dp_mems": cached.get("dp_mems", "error"),
                        "dp_path": cached.get("dp_path", ""),
                        "dp_error": cached.get("dp_error", ""),
                    })
                    success_dfs = bool(cached.get("success_dfs", False))
                    success_dp = bool(cached.get("success_dp", False))

                file_guidance = _format_file_guidance(entry, cfile)
                print("  [3/3] 调用 GPT 分析（使用固定5例校准方法 + 当前源码；不注入当前文件DP/DFS答案）")
                t0 = time.time()
                gpt_mems, gpt_path, gpt_raw = call_gpt_for_mems(code_text, guidance=file_guidance)
                entry["gpt_time"] = f"{time.time() - t0:.4f}"
                if gpt_mems is None or (not gpt_path and gpt_mems != -1):
                    print("  [失败] GPT 阶段解析失败")
                    entry.update({"gpt_mems": "error", "gpt_path": "", "gpt_error": short_err(_sanitize_secrets(gpt_raw), 300) or "parse_fail"})
                    success_gpt = False
                else:
                    entry.update({"gpt_mems": str(gpt_mems), "gpt_path": gpt_path, "gpt_error": ""})
                    print(f"  [OK] GPT time: {entry['gpt_time']} | mems: {entry['gpt_mems']}")
                    success_gpt = True

            entry["success_gpt"], entry["success_dfs"], entry["success_dp"] = bool(success_gpt), bool(success_dfs), bool(success_dp)

            def to_int(sv: Any) -> Optional[int]:
                if isinstance(sv, int):
                    return sv
                if isinstance(sv, str) and re.fullmatch(r"-?\d+", sv):
                    return int(sv)
                return None

            gpt_mems_val, dp_mems_val, dfs_mems_val = to_int(entry.get("gpt_mems", "")), to_int(entry.get("dp_mems", "")), to_int(entry.get("dfs_max_mems", ""))
            entry["gpt_eq_dp_mems"] = bool(success_gpt and success_dp and gpt_mems_val is not None and dp_mems_val is not None and gpt_mems_val == dp_mems_val)
            entry["gpt_eq_dfs_mems"] = bool(success_gpt and success_dfs and gpt_mems_val is not None and dfs_mems_val is not None and gpt_mems_val == dfs_mems_val)

            if ENABLE_METHOD_RETRY and success_gpt and success_dp and (not entry["gpt_eq_dp_mems"]):
                retry_guidance_parts: List[str] = []
                if file_guidance:
                    retry_guidance_parts.append(file_guidance)
                direction_hint = _direction_feedback(gpt_mems_val, dp_mems_val, "外部目标结果")
                if direction_hint:
                    retry_guidance_parts.append(direction_hint)
                retry_guidance_parts.append(
                    "本文件首次输出未通过外部一致性检查。"
                    "不要使用任何外部目标MEMS数值或 oracle path。"
                    "可以利用上面的偏大/偏小方向反馈修正方法，但必须只根据源码重新执行“建约束→枚举可行候选→逐路径计数→选择最大MEMS→自检”。"
                    "重点检查：是否漏算条件读、数组下标读、指针/结构体访问、短路逻辑、循环最终退出条件，以及是否误算隐含临时量。"
                )
                retry_guidance = _sanitize_feedback_for_prompt("\n".join(retry_guidance_parts))

                print("  [3/3-重试] GPT 未通过外部一致性检查，触发一次方法级重试")
                t1 = time.time()
                rg_mems, rg_path, rg_raw = call_gpt_for_mems(code_text, guidance=retry_guidance)
                entry["gpt_time"] = f"{(float(entry['gpt_time']) + (time.time() - t1)):.4f}"

                if rg_mems is not None and (rg_path or rg_mems == -1):
                    entry.update({"gpt_mems": str(rg_mems), "gpt_path": rg_path, "gpt_error": ""})
                    gpt_mems_val = to_int(entry.get("gpt_mems", ""))
                    entry["gpt_eq_dp_mems"] = bool(
                        success_dp
                        and gpt_mems_val is not None
                        and dp_mems_val is not None
                        and gpt_mems_val == dp_mems_val
                    )
                    entry["gpt_eq_dfs_mems"] = bool(
                        success_dfs
                        and gpt_mems_val is not None
                        and dfs_mems_val is not None
                        and gpt_mems_val == dfs_mems_val
                    )
                    print(f"  [重试结果] gpt_mems={entry['gpt_mems']} | 与外部评估一致={entry['gpt_eq_dp_mems']}")
                else:
                    entry["gpt_error"] = short_err(_sanitize_secrets(rg_raw), 300) or entry.get("gpt_error", "retry_parse_fail")
                    print("  [重试结果] 解析失败，保留首轮 GPT 结果")

            # 保护规则：当DP给出可行(>=0)时，GPT不得随意输出-1
            if success_gpt and success_dp and gpt_mems_val is not None and dp_mems_val is not None:
                if dp_mems_val >= 0 and gpt_mems_val == -1:
                    entry["gpt_error"] = "invalid_no_feasible_path_when_dp_feasible"
                    entry["gpt_eq_dp_mems"] = False
                    entry["is_true"] = False
                    print("  [约束] DP可行但GPT输出-1，标记为无效结果并要求后续回溯修正")
            entry["dp_eq_dfs_mems"] = bool(success_dp and success_dfs and dp_mems_val is not None and dfs_mems_val is not None and dp_mems_val == dfs_mems_val)
            entry["gpt_dp_mems_diff"] = "" if (gpt_mems_val is None or dp_mems_val is None) else str(gpt_mems_val - dp_mems_val)
            entry["gpt_dfs_mems_diff"] = "" if (gpt_mems_val is None or dfs_mems_val is None) else str(gpt_mems_val - dfs_mems_val)
            entry["dp_dfs_mems_diff"] = "" if (dp_mems_val is None or dfs_mems_val is None) else str(dp_mems_val - dfs_mems_val)
            if success_gpt:
                feas, feas_reason, feas_source = judge_path_feasibility(cfile, code_text, entry.get("gpt_path", ""))
            else:
                feas, feas_reason, feas_source = "unknown", "gpt_failed", "none"
            entry["eppath_feasible"] = feas
            entry["eppath_feasible_reason"] = feas_reason
            entry["eppath_feasible_source"] = feas_source
            entry["gpt_path_feasible_by_eppath"] = (feas == "true")
            entry["worst_mems_dp"] = entry.get("dp_mems", "") if success_dp else ""
            entry["worst_path_dp"] = entry.get("dp_path", "") if success_dp else ""
            entry["worst_mems_dfs"] = entry.get("dfs_max_mems", "") if success_dfs else ""
            entry["worst_path_dfs"] = entry.get("dfs_best_path", "") if success_dfs else ""
            entry["is_true"] = bool(entry["gpt_eq_dp_mems"] and entry["gpt_eq_dfs_mems"])
            print(f"  [总结] GPT={entry['success_gpt']} DFS={entry['success_dfs']} DP={entry['success_dp']} | "
                  f"GPT=DP:{entry['gpt_eq_dp_mems']} GPT=DFS:{entry['gpt_eq_dfs_mems']} DP=DFS:{entry['dp_eq_dfs_mems']}")
            print(f"  [可行性] eppather判定={entry['eppath_feasible']} ({entry['eppath_feasible_source']}:{entry['eppath_feasible_reason']})")
            if entry["is_true"]:
                try:
                    dst = os.path.join(OUTPUT_TRUE_FOLDER, os.path.basename(cfile))
                    shutil.copy2(cfile, dst)
                    print(f"  [已保存] {dst}")
                except Exception as e:
                    print(f"  [保存失败] {e}")
            local_results.append(entry)
            latest_stage_results[:] = local_results
        return local_results

    results: List[Dict[str, Any]] = []
    all_stage_results: List[Dict[str, Any]] = []
    stage_accuracy_records: List[Dict[str, Any]] = []

    cols = [
        "filename",
        "basename",
        "gpt_time",
        "gpt_mems",
        "gpt_path",
        "gpt_error",
        "dfs_time",
        "dfs_max_mems",
        "dfs_min_mems",
        "dfs_best_path",
        "dfs_error",
        "dp_time",
        "dp_mems",
        "dp_path",
        "dp_error",
        "success_gpt",
        "success_dfs",
        "success_dp",
        "gpt_eq_dp_mems",
        "gpt_eq_dfs_mems",
        "dp_eq_dfs_mems",
        "gpt_dp_mems_diff",
        "gpt_dfs_mems_diff",
        "dp_dfs_mems_diff",
        "eppath_feasible",
        "eppath_feasible_reason",
        "eppath_feasible_source",
        "gpt_path_feasible_by_eppath",
        "is_true",
        "worst_mems_dp",
        "worst_path_dp",
        "worst_mems_dfs",
        "worst_path_dfs",
        "run_round",
        "run_stage",
        "run_stage_tag",
    ]

    CHECKPOINT_DIR = os.path.join(RESULT_DIR, "checkpoints")
    os.makedirs(CHECKPOINT_DIR, exist_ok=True)

    def _safe_tag(tag: str) -> str:
        return re.sub(r"[^A-Za-z0-9_.-]+", "_", str(tag)).strip("_") or "checkpoint"

    def _numeric_values_from_column(df: pd.DataFrame, column: str) -> List[float]:
        vals: List[float] = []
        if df.empty or column not in df.columns:
            return vals
        for v in df[column].tolist():
            if isinstance(v, int):
                vals.append(float(v))
            elif isinstance(v, float):
                vals.append(v)
            elif isinstance(v, str) and re.fullmatch(r"-?\d+(\.\d+)?", v.strip()):
                vals.append(float(v.strip()))
        return vals

    def _write_outputs(
        rows: List[Dict[str, Any]],
        tag: str,
        note: str = "",
        write_main_summary: bool = True,
    ) -> Dict[str, Any]:
        safe_tag = _safe_tag(tag)
        os.makedirs(RESULT_DIR, exist_ok=True)
        os.makedirs(OUTPUT_TRUE_FOLDER, exist_ok=True)
        os.makedirs(CHECKPOINT_DIR, exist_ok=True)

        df = pd.DataFrame(rows, columns=cols)

        if "is_true" in df.columns:
            df_true = df[df["is_true"] == True].copy()
        else:
            df_true = pd.DataFrame(columns=cols)
        if "success_gpt" in df.columns:
            df_gpt_fail = df[df["success_gpt"] == False].copy()
        else:
            df_gpt_fail = pd.DataFrame(columns=cols)
        if write_main_summary:
            df.to_csv(SUMMARY_CSV, index=False, encoding="utf-8")
            df.to_excel(SUMMARY_XLSX, index=False)
            df_true.to_csv(TRUE_ONLY_CSV, index=False, encoding="utf-8")
            df_true.to_excel(TRUE_ONLY_XLSX, index=False)
            df_gpt_fail.to_csv(GPT_FAIL_CSV, index=False, encoding="utf-8")
            df_gpt_fail.to_excel(GPT_FAIL_XLSX, index=False)

        final_prompt = build_system_prompt()
        with open(FINAL_PROMPT_TXT, "w", encoding="utf-8") as f:
            f.write(final_prompt)
            f.write("\n")

        with open(PROMPT_HISTORY_JSON, "w", encoding="utf-8") as f:
            json.dump(PROMPT_SNAPSHOTS, f, ensure_ascii=False, indent=2)

        checkpoint_summary_csv = os.path.join(CHECKPOINT_DIR, f"{safe_tag}_summary.csv")
        checkpoint_summary_xlsx = os.path.join(CHECKPOINT_DIR, f"{safe_tag}_summary.xlsx")
        checkpoint_true_csv = os.path.join(CHECKPOINT_DIR, f"{safe_tag}_true_only.csv")
        checkpoint_gpt_fail_csv = os.path.join(CHECKPOINT_DIR, f"{safe_tag}_gpt_fail.csv")
        checkpoint_prompt_txt = os.path.join(CHECKPOINT_DIR, f"{safe_tag}_prompt.txt")
        checkpoint_prompt_history_json = os.path.join(CHECKPOINT_DIR, f"{safe_tag}_prompt_history.json")
        checkpoint_stats_json = os.path.join(CHECKPOINT_DIR, f"{safe_tag}_stats.json")

        df.to_csv(checkpoint_summary_csv, index=False, encoding="utf-8")
        df.to_excel(checkpoint_summary_xlsx, index=False)
        df_true.to_csv(checkpoint_true_csv, index=False, encoding="utf-8")
        df_gpt_fail.to_csv(checkpoint_gpt_fail_csv, index=False, encoding="utf-8")
        with open(checkpoint_prompt_txt, "w", encoding="utf-8") as f:
            f.write(final_prompt)
            f.write("\n")
        with open(checkpoint_prompt_history_json, "w", encoding="utf-8") as f:
            json.dump(PROMPT_SNAPSHOTS, f, ensure_ascii=False, indent=2)

        total = len(df)
        true_count = int(df["is_true"].sum()) if total and "is_true" in df.columns else 0
        dp_ok = int(df["success_dp"].sum()) if total and "success_dp" in df.columns else 0
        dfs_ok = int(df["success_dfs"].sum()) if total and "success_dfs" in df.columns else 0
        gpt_ok = int(df["success_gpt"].sum()) if total and "success_gpt" in df.columns else 0
        gpt_eq_dp = int(df["gpt_eq_dp_mems"].sum()) if total and "gpt_eq_dp_mems" in df.columns else 0
        gpt_eq_dfs = int(df["gpt_eq_dfs_mems"].sum()) if total and "gpt_eq_dfs_mems" in df.columns else 0
        dp_eq_dfs = int(df["dp_eq_dfs_mems"].sum()) if total and "dp_eq_dfs_mems" in df.columns else 0
        eppath_ok = int((df["eppath_feasible"] == "true").sum()) if total and "eppath_feasible" in df.columns else 0

        gpt_dp_diffs = _numeric_values_from_column(df, "gpt_dp_mems_diff")
        gpt_dfs_diffs = _numeric_values_from_column(df, "gpt_dfs_mems_diff")
        dp_dfs_diffs = _numeric_values_from_column(df, "dp_dfs_mems_diff")

        baseline_acc_samples: List[float] = []
        for cp in sorted(BASELINE_ACCURACY_HISTORY.keys()):
            baseline_acc_samples.extend(BASELINE_ACCURACY_HISTORY.get(cp, []))

        stats = {
            "tag": tag,
            "note": note,
            "result_dir": RESULT_DIR,
            "total": total,
            "gpt_ok": gpt_ok,
            "dfs_ok": dfs_ok,
            "dp_ok": dp_ok,
            "gpt_eq_dp": gpt_eq_dp,
            "gpt_eq_dfs": gpt_eq_dfs,
            "dp_eq_dfs": dp_eq_dfs,
            "eppath_ok": eppath_ok,
            "true_count": true_count,
            "gpt_success_rate": (gpt_ok / total) if total else 0.0,
            "dfs_success_rate": (dfs_ok / total) if total else 0.0,
            "dp_success_rate": (dp_ok / total) if total else 0.0,
            "gpt_eq_dp_rate": (gpt_eq_dp / total) if total else 0.0,
            "gpt_eq_dfs_rate": (gpt_eq_dfs / total) if total else 0.0,
            "dp_eq_dfs_rate": (dp_eq_dfs / total) if total else 0.0,
            "true_rate": (true_count / total) if total else 0.0,
            "gpt_dp_mems_diff_variance": _safe_variance(gpt_dp_diffs),
            "gpt_dfs_mems_diff_variance": _safe_variance(gpt_dfs_diffs),
            "dp_dfs_mems_diff_variance": _safe_variance(dp_dfs_diffs),
            "baseline_accuracy_variance": _safe_variance(baseline_acc_samples),
            "stage_accuracy_records": stage_accuracy_records,
            "baseline_accuracy_history": BASELINE_ACCURACY_HISTORY,
        }
        with open(checkpoint_stats_json, "w", encoding="utf-8") as f:
            json.dump(stats, f, ensure_ascii=False, indent=2)

        run_stats = {
            "run_tag": RUN_TAG,
            "input_folder": INPUT_FOLDER,
            "input_glob": INPUT_GLOB,
            "input_recursive": INPUT_RECURSIVE,
            "files_detected": len(c_files),
            "files_processed": len(rows),
            "max_files": MAX_FILES,
            "max_backtrack_rounds": MAX_BACKTRACK_ROUNDS,
            "baseline_pass_threshold": BASELINE_PASS_THRESHOLD,
            "gate_stages": gate_stages,
            "current_tag": tag,
            "current_note": note,
            "result_dir": RESULT_DIR,
            "summary_csv": SUMMARY_CSV,
            "summary_xlsx": SUMMARY_XLSX,
            "true_only_csv": TRUE_ONLY_CSV,
            "gpt_fail_csv": GPT_FAIL_CSV,
            "checkpoint_stats_json": checkpoint_stats_json,
            "latest_metrics": {
                "total": total,
                "true_count": true_count,
                "gpt_ok": gpt_ok,
                "dfs_ok": dfs_ok,
                "dp_ok": dp_ok,
                "gpt_eq_dp": gpt_eq_dp,
                "gpt_eq_dfs": gpt_eq_dfs,
                "dp_eq_dfs": dp_eq_dfs,
                "eppath_ok": eppath_ok,
            },
            "stage_accuracy_records": stage_accuracy_records,
        }
        with open(RUN_STATS_JSON, "w", encoding="utf-8") as f:
            json.dump(run_stats, f, ensure_ascii=False, indent=2)
        pd.DataFrame(stage_accuracy_records).to_csv(RUN_STATS_CSV, index=False, encoding="utf-8")

        print(f"\n==== 已保存阶段结果: {tag} ====")
        if note:
            print(f"  [说明] {note}")
        print(f"  [目录] RESULT_DIR: {RESULT_DIR}")
        print(f"  [表格] 汇总CSV: {SUMMARY_CSV}")
        print(f"  [表格] 汇总XLSX: {SUMMARY_XLSX}")
        print(f"  [表格] TRUE子集CSV: {TRUE_ONLY_CSV}")
        print(f"  [表格] TRUE子集XLSX: {TRUE_ONLY_XLSX}")
        print(f"  [表格] GPT失败子集CSV: {GPT_FAIL_CSV}")
        print(f"  [表格] GPT失败子集XLSX: {GPT_FAIL_XLSX}")
        print(f"  [提示词] 回溯历史JSON: {PROMPT_HISTORY_JSON}")
        print(f"  [提示词] 最终提示词TXT: {FINAL_PROMPT_TXT}")
        print(f"  [统计] 运行汇总JSON: {RUN_STATS_JSON}")
        print(f"  [统计] 阶段准确率CSV: {RUN_STATS_CSV}")
        print(f"  [阶段备份] {checkpoint_summary_csv}")
        print(f"  [阶段提示词] {checkpoint_prompt_txt}")

        if total:
            print("\n==== 当前统计结果 ====")
            print(f"  总文件数: {total}")
            print(f"  GPT成功:  {gpt_ok}/{total} ({gpt_ok/total:.2%})")
            print(f"  GPT失败:  {total - gpt_ok}/{total} ({(total - gpt_ok)/total:.2%})")
            print(f"  DFS成功:  {dfs_ok}/{total} ({dfs_ok/total:.2%})")
            print(f"  DP成功:   {dp_ok}/{total} ({dp_ok/total:.2%})")
            print(f"  GPT=DP:   {gpt_eq_dp}/{total} ({gpt_eq_dp/total:.2%})")
            print(f"  GPT=DFS:  {gpt_eq_dfs}/{total} ({gpt_eq_dfs/total:.2%})")
            print(f"  DP=DFS:   {dp_eq_dfs}/{total} ({dp_eq_dfs/total:.2%})")
            print(f"  eppather判定可行: {eppath_ok}/{total} ({eppath_ok/total:.2%})")
            print(f"  TRUE(三方一致并已保存到{OUTPUT_TRUE_FOLDER}): {true_count}/{total} ({true_count/total:.2%})")
            print("\n==== 稳定性方差 ====")
            print(f"  baseline准确率方差(stage-level): {stats['baseline_accuracy_variance']:.6f}")
            print(f"  GPT-DP mems差值方差(file-level): {stats['gpt_dp_mems_diff_variance']:.6f}")
            print(f"  GPT-DFS mems差值方差(file-level): {stats['gpt_dfs_mems_diff_variance']:.6f}")
            print(f"  DP-DFS mems差值方差(file-level): {stats['dp_dfs_mems_diff_variance']:.6f}")
        else:
            print("  总文件数: 0")

        return stats

    def _build_application_stages(total_files: int, calibration_count: int) -> List[int]:
        # 新策略：前 CALIBRATION_SIZE 个文件只作为方法校准集；应用阶段固定为 20 -> 100 -> 全量。
        # 若文件总数不足 20，则全量阶段会自然退化为 total_files。
        desired = [20, 100, total_files]
        out: List[int] = []
        seen = set()
        for x in desired:
            if x <= 0:
                continue
            stage = min(x, total_files)
            if stage > 0 and stage not in seen:
                out.append(stage)
                seen.add(stage)
        if not out and total_files > 0:
            out.append(total_files)
        return out

    calibration_count = min(max(CALIBRATION_SIZE, 0), len(c_files))
    calibration_files = c_files[:calibration_count]
    prepare_calibration_examples(calibration_files)

    gate_stages = _build_application_stages(len(c_files), calibration_count)
    print(
        f"[批量策略] calibration_size={calibration_count}, application_stages={gate_stages}, "
        f"max_backtrack_rounds={MAX_BACKTRACK_ROUNDS}, threshold>{BASELINE_PASS_THRESHOLD:.2%}, "
        f"指标=GPT=DP准确率, require_gpt_dp_match={REQUIRE_GPT_DP_MATCH}, "
        f"require_eppath_feasible={REQUIRE_EPATH_FEASIBLE}, "
        f"eppath_api={'on' if EPATH_FEASIBILITY_API else 'off(local_parser)'}"
    )
    print(
        "[校准策略] 前5个文件用于生成固定方法校准样例；这些样例可以包含DP/DFS样例结果。"
        "20/100/全量应用阶段不会把当前待评估文件的DP/DFS答案直接注入prompt，只注入校准样例、方法反馈和偏大/偏小方向。"
    )

    current_round = 0
    current_stage = 0
    last_stage_results: List[Dict[str, Any]] = []

    try:
        record_prompt_snapshot("initial", "after_calibration_examples_before_gate_loop")
        for round_idx in range(1, MAX_BACKTRACK_ROUNDS + 1):
            current_round = round_idx
            print(f"\n==== 自动回溯轮次 {round_idx}/{MAX_BACKTRACK_ROUNDS} ====")
            record_prompt_snapshot(f"round_{round_idx}_start", "round_start")

            round_failed = False

            if calibration_files:
                current_stage = calibration_count
                latest_stage_results[:] = []
                calib_tag = f"calibration_{calibration_count}"
                print(f"\n---- 方法校准阶段: 前 {calibration_count} 个文件 ----")
                calibration_results = process_files(calibration_files)
                calibration_rows = []
                for r in calibration_results:
                    rr = dict(r)
                    rr["run_round"] = round_idx
                    rr["run_stage"] = calibration_count
                    rr["run_stage_tag"] = calib_tag
                    calibration_rows.append(rr)
                all_stage_results.extend(calibration_rows)
                last_stage_results = calibration_results
                results = calibration_results

                _write_outputs(
                    calibration_rows,
                    f"round_{round_idx}_{calib_tag}_snapshot",
                    f"{calib_tag} 方法校准阶段完成快照；该阶段不作为进入20/100/全量的阻断gate。",
                    write_main_summary=False,
                )
                _print_stage_summary(f"round={round_idx},{calib_tag}", calibration_results)
                calib_acc = _stage_accuracy(calibration_results)
                BASELINE_ACCURACY_HISTORY.setdefault(calibration_count, []).append(calib_acc)
                stage_accuracy_records.append({
                    "round": round_idx,
                    "stage": calibration_count,
                    "accuracy": calib_acc,
                    "sample_count": len(calibration_results),
                    "tag": calib_tag,
                    "stage_role": "calibration",
                })
                print(f"[calibration] round={round_idx}, {calib_tag}, GPT=DP准确率={calib_acc:.2%}（仅用于方法校准，不阻断后续阶段）")

                for fx in [r for r in calibration_results if not r.get("gpt_eq_dp_mems", False)]:
                    _record_file_feedback(fx)

                calib_summary = _build_calibration_method_summary(calibration_results)
                if calib_summary:
                    calib_summary = _sanitize_feedback_for_prompt(calib_summary)
                    CALIBRATION_FEEDBACK_HISTORY.append(calib_summary)
                    PROMPT_FEEDBACK_HISTORY.append(calib_summary)
                    record_prompt_snapshot(f"round_{round_idx}_{calib_tag}_method_feedback", calib_summary)
                    print(f"[校准反馈] {calib_summary}")

            for stage in gate_stages:
                current_stage = stage
                latest_stage_results[:] = []
                subset = c_files[:stage]
                tag_prefix = "all" if stage == len(c_files) else f"stage_{stage}"

                print(f"\n---- 应用阶段执行: 前 {stage} 个文件 ----")
                stage_results = process_files(subset)
                stage_rows = []
                for r in stage_results:
                    rr = dict(r)
                    rr["run_round"] = round_idx
                    rr["run_stage"] = stage
                    rr["run_stage_tag"] = tag_prefix
                    rr["stage_role"] = "application"
                    stage_rows.append(rr)
                all_stage_results.extend(stage_rows)
                last_stage_results = stage_results
                results = stage_results

                _write_outputs(
                    stage_rows,
                    f"round_{round_idx}_{tag_prefix}_stage_snapshot",
                    f"{tag_prefix} 应用阶段执行完成快照。",
                    write_main_summary=False,
                )

                _print_stage_summary(f"round={round_idx},{tag_prefix}", stage_results)
                stage_acc = _stage_accuracy(stage_results)
                BASELINE_ACCURACY_HISTORY.setdefault(stage, []).append(stage_acc)
                stage_accuracy_records.append({
                    "round": round_idx,
                    "stage": stage,
                    "accuracy": stage_acc,
                    "sample_count": len(stage_results),
                    "tag": tag_prefix,
                    "stage_role": "application",
                })
                print(f"[application] round={round_idx}, {tag_prefix}, GPT=DP准确率={stage_acc:.2%}")

                if stage_acc > BASELINE_PASS_THRESHOLD:
                    record_prompt_snapshot(
                        f"round_{round_idx}_{tag_prefix}_pass",
                        f"{tag_prefix} pass, GPT=DP accuracy={stage_acc:.2%}",
                    )
                    if stage == len(c_files):
                        _write_outputs(
                            all_stage_results,
                            f"round_{round_idx}_{tag_prefix}_pass",
                            f"{tag_prefix} 通过，GPT=DP准确率={stage_acc:.2%} > {BASELINE_PASS_THRESHOLD:.2%}",
                        )
                    else:
                        _write_outputs(
                            stage_rows,
                            f"round_{round_idx}_{tag_prefix}_pass",
                            f"{tag_prefix} 通过（中间应用阶段checkpoint）。",
                            write_main_summary=False,
                        )
                    print(f"[gate通过] {tag_prefix} 准确率={stage_acc:.2%}，保存结果和prompt后进入下一应用阶段。")
                    continue

                mismatch_examples: List[str] = []
                for r in stage_results:
                    if r.get("success_dp", False) and r.get("success_gpt", False) and not r.get("gpt_eq_dp_mems", False):
                        direction = _direction_feedback(r.get("gpt_mems", ""), r.get("dp_mems", ""), "当前应用阶段外部目标结果")
                        if direction:
                            mismatch_examples.append(f"{r.get('basename','?')}: {direction}")
                        else:
                            mismatch_examples.append(f"{r.get('basename','?')}: 未通过外部一致性检查")
                    if len(mismatch_examples) >= 5:
                        break

                failed_entries = [r for r in stage_results if not r.get("gpt_eq_dp_mems", False)]
                _write_outputs(
                    stage_rows,
                    f"round_{round_idx}_{tag_prefix}_prefail",
                    f"{tag_prefix} 未通过前快照（尚未注入失败反馈）。",
                    write_main_summary=False,
                )
                for fx in failed_entries:
                    _record_file_feedback(fx)

                fb = (
                    f"{tag_prefix}未达标: 应用阶段外部一致性检查未通过阈值。"
                    "下一轮会先重新运行5个文件的校准阶段，再应用到20/100/全量。"
                    "反馈只允许包含方法级修正、偏大/偏小方向和固定校准样例；"
                    "不允许注入当前待评估文件的DP/DFS目标数值或路径。"
                )
                if mismatch_examples:
                    fb += " 重点错例方向: " + " | ".join(mismatch_examples)
                fb = _sanitize_feedback_for_prompt(fb)
                PROMPT_FEEDBACK_HISTORY.append(fb)
                record_prompt_snapshot(f"round_{round_idx}_{tag_prefix}_fail", fb)
                _write_outputs(
                    stage_rows,
                    f"round_{round_idx}_{tag_prefix}_postfail",
                    f"{tag_prefix} 未通过后快照（已注入方向反馈）；下一轮将先从5个校准样例重新总结方法，再进入应用阶段。",
                    write_main_summary=False,
                )
                print(f"[gate未通过] {fb}")
                round_failed = True
                break

            if not round_failed:
                print("[完成] 5例校准、20、100、全量应用阶段均已执行并通过gate。")
                record_prompt_snapshot(f"round_{round_idx}_completed", "calibration_and_all_application_gate_stages_success")
                _write_outputs(all_stage_results, f"round_{round_idx}_completed", "校准阶段与全部应用阶段完成后的最终汇总结果。")
                break

            if round_idx >= MAX_BACKTRACK_ROUNDS:
                print("[停止] 已达到最大回溯轮次，保留最近一次阶段结果。")
                record_prompt_snapshot(f"round_{round_idx}_stopped", "max_backtrack_reached")
                _write_outputs(all_stage_results, f"round_{round_idx}_stopped", "达到最大回溯轮次后的最终可用结果（含校准与应用阶段）。")
            else:
                print("[回溯] 已保存当前应用阶段结果和prompt，下一轮先重新做5例校准，再继续应用阶段。")

    except KeyboardInterrupt:
        print("\n[用户中断] 捕获到 KeyboardInterrupt，正在保存已完成的阶段/文件结果。")
        interrupted_rows = latest_stage_results if latest_stage_results else (last_stage_results if last_stage_results else results)
        results = interrupted_rows
        record_prompt_snapshot(
            f"interrupted_round_{current_round}_stage_{current_stage}",
            "keyboard_interrupt",
        )
        _write_outputs(
            interrupted_rows,
            f"interrupted_round_{current_round}_stage_{current_stage}",
            "用户中断，保存已完成文件的中断结果。",
        )
    except Exception as e:
        print(f"\n[异常中断] {type(e).__name__}: {e}")
        interrupted_rows = latest_stage_results if latest_stage_results else (last_stage_results if last_stage_results else results)
        results = interrupted_rows
        record_prompt_snapshot(
            f"exception_round_{current_round}_stage_{current_stage}",
            f"{type(e).__name__}: {e}",
        )
        _write_outputs(
            interrupted_rows,
            f"exception_round_{current_round}_stage_{current_stage}",
            "异常中断，保存已完成文件的中断结果。",
        )
        raise

    if results:
        print("\n==== 最终结果已保存 ====")
        print(f"  RESULT_DIR: {RESULT_DIR}")
        print(f"  汇总表: {SUMMARY_XLSX}")
        print(f"  最终提示词: {FINAL_PROMPT_TXT}")
        print(f"  阶段备份目录: {CHECKPOINT_DIR}")
    else:
        print("\n==== 未产生可保存的结果 ====")
        _write_outputs([], "empty_result", "未产生可保存的结果。")


if __name__ == "__main__":
    main()