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
OUTPUT_TRUE_FOLDER = os.path.join(SCRIPT_DIR, "output_true3")
SUMMARY_CSV = os.path.join(SCRIPT_DIR, "result_summary_true3.csv")
SUMMARY_XLSX = os.path.join(SCRIPT_DIR, "result_summary_true3.xlsx")
TRUE_ONLY_CSV = os.path.join(SCRIPT_DIR, "result_true_only3.csv")
TRUE_ONLY_XLSX = os.path.join(SCRIPT_DIR, "result_true_only3.xlsx")
GPT_FAIL_CSV = os.path.join(SCRIPT_DIR, "result_gpt_fail3.csv")
GPT_FAIL_XLSX = os.path.join(SCRIPT_DIR, "result_gpt_fail3.xlsx")
PROMPT_HISTORY_JSON = os.path.join(SCRIPT_DIR, "prompt_backtrack_history_true3.json")
FINAL_PROMPT_TXT = os.path.join(SCRIPT_DIR, "prompt_final_true3.txt")

INPUT_GLOB = (os.getenv("AUTO_MEM_INPUT_GLOB") or "*.c").strip()
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
API_KEY = (os.getenv("IFOPEN_API_KEY") or os.getenv("OPENAI_API_KEY") or "").strip()
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

    candidates.extend(["gpt-4o-mini", "gpt-4o", "gpt-4.1-mini", "gpt-4.1"])

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


if not API_KEY:
    raise RuntimeError("Missing API key. Please set IFOPEN_API_KEY (preferred) or OPENAI_API_KEY in your environment.")

print("==== API CONFIG ====")
print(f"  BASE_URL : {BASE_URL}")
print(f"  MODEL    : {MODEL_NAME}")
print(f"  MODEL_CANDIDATES : {MODEL_CANDIDATES}")
print(f"  API_KEY  : {_mask_key(API_KEY)}")
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


def build_system_prompt() -> str:
    base = (
        "You are a static-analysis assistant for C code.\n"
        "Target: generate one FEASIBLE worst-case path with MAX MEMS that matches cnip DP outputs as strictly as possible.\n\n"
        "Primary objective priority:\n"
        "1) Match DP MAX MEMS counting style.\n"
        "2) Match DP path expression style and branch order.\n"
        "3) Keep output strict JSON.\n\n"
        "You MUST follow a step-by-step method:\n"
        "Step 1) Build symbolic constraints for branches, loops, and calls under the given caps.\n"
        "Step 2) Enumerate feasible candidate paths (bounded) and reject contradictory constraints.\n"
        "Step 3) If NO feasible path exists, set mems=-1 and test_input_path_expr='[NO FEASIBLE PATH]'.\n"
        "Step 4) Otherwise compute MEMS for each feasible candidate by DP counting rules below.\n"
        "Step 5) Choose the feasible candidate with maximum MEMS (DP target principle).\n"
        "Step 6) Self-verify: recompute MEMS from emitted path line-by-line and ensure exact consistency.\n"
        "Step 7) Output JSON only.\n\n"
        "MUST align with cnip assumptions:\n"
        f"- Loop unrolling cap = {MAX_LOOP}. Never exceed this cap for each loop in a single path.\n"
        f"- Function inline expansion cap = {MAX_INLINE} levels.\n"
        "- For recursion/mutual recursion: use fixpoint-style approximation idea; do NOT do unbounded expansion.\n"
        "- Respect path feasibility (no contradictory branch predicates).\n\n"
        "MEMS definition (strict):\n"
        "- MEMS = variable-memory accesses along the chosen path.\n"
        "- Read as rvalue => +1; write lvalue => +1.\n"
        "- Include locals/params/globals, array subscripts, struct fields, pointer dereference expressions.\n"
        "- Assignment L=E counts reads in E plus one write to L.\n"
        "- ++/-- and compound assignments count both read and write.\n"
        "- Conditions contribute reads; use short-circuit semantics for && and ||.\n"
        "- Function-call arguments still contribute expression reads.\n"
        "- Ignore non-memory tokens (types, keywords, punctuation, pure constants).\n"
        "- Ignore declaration statements without actual read/write side effects.\n"
        "- For 'return x;' count read of x; for 'return 0;' add nothing.\n"
        "- Do not add external ABI overhead not present in static analyzer.\n\n"
        "Calibration hints (very important):\n"
        "- For simple 'a+b' style programs, do NOT over-count temporaries or implicit steps.\n"
        "- If DP-like count is small, prefer smaller count consistent with explicit variable accesses only.\n"
        "- Never invent hidden temporaries/register moves; only count explicit source-level memory reads/writes.\n"
        "- For expression trees, count variable occurrences that are actually evaluated on the chosen feasible path only.\n\n"
        "Strict feasibility rules:\n"
        "- If any chosen branch predicate contradicts earlier predicates, this path is INVALID and must be discarded.\n"
        "- Do not report a path with mems>=0 unless every emitted predicate/statement can execute in one concrete run.\n"
        "- If all bounded candidates are contradictory, return mems=-1 with [NO FEASIBLE PATH].\n\n"
        "DP-first tie-break policy:\n"
        "- When multiple feasible paths are close, prefer the path whose counting style is most conservative and DP-consistent.\n"
        "- Prefer explicit variable access accounting over speculative hidden operations.\n\n"
        "Hard constraints to reduce mismatch with DP/DFS results:\n"
        "- Treat DP output style as oracle target for worst-case path selection.\n"
        "- Prefer exact symbolic predicates from source conditions (keep operators and constants unchanged).\n"
        "- If unsure about branch feasibility, choose the conservative feasible branch with explicit guard in path.\n"
        "- For loops, explicitly emit each taken iteration guard and a final not-taken guard.\n"
        "- Branch order in path must follow source execution order exactly.\n"
        "- Include all MEMS-contributing statements on the chosen path; do not skip hidden reads in conditions/index/pointer expressions.\n"
        "- Avoid undercounting from short-circuit logic; count only actually evaluated side under path predicates.\n"
        "- Keep path statements close to source-level assignments/conditions only; avoid invented statements.\n"
        "- Final mems must be consistent with the emitted path; do a self-check before output.\n\n"
        "Output STRICT JSON only:\n"
        "{\n"
        '  "mems": <integer; use -1 if and only if no feasible path>,\n'
        '  "test_input_path_expr": "<exact path expr format>",\n'
        '  "reason": "<one-line rationale tied to loop/recursion/feasibility assumptions>"\n'
        "}\n\n"
        "Path format MUST be:\n"
        "[TEST INPUT PATH EXPR]:\n"
        "@(cond);\n"
        "stmt;\n"
        "...\n"
        "Every non-empty line after title must end with ';'.\n"
        "Special case for infeasible program: mems=-1 and test_input_path_expr='[NO FEASIBLE PATH]'."
    )
    if PROMPT_FEEDBACK_HISTORY:
        base += (
            "\n\nRecent failure feedback from previous runs (must fix in current reasoning):\n"
            + "\n".join(f"- {x}" for x in PROMPT_FEEDBACK_HISTORY[-6:])
        )
    return base


def build_user_prompt(code: str, guidance: str = "") -> str:
    prompt = (
        "Given this C file content, estimate a feasible MAX-MEMS path under the same assumptions as cnip. "
        f"Use loop cap={MAX_LOOP}, inline depth cap={MAX_INLINE}, recursion via fixpoint-style approximation. "
        "Prioritize strict alignment with cnip DFS/DP path style and MEMS counting. "
        "If multiple candidates exist, return the one most likely to match cnip output exactly.\n\n"
        "请按“先约束、再枚举、再计数、再验证”的分步过程完成，并输出最坏情况路径和对应 mems。\n\n"
        "-----BEGIN C CODE-----\n"
        f"{code}\n"
        "-----END C CODE-----"
    )
    if guidance:
        prompt += f"\n\nDP/DFS对齐提示(高优先级):\n{guidance}"
    return prompt


def record_prompt_snapshot(tag: str, note: str = "") -> None:
    try:
        snap = {
            "tag": tag,
            "note": note,
            "feedback_count": len(PROMPT_FEEDBACK_HISTORY),
            "feedback_tail": PROMPT_FEEDBACK_HISTORY[-6:],
            "prompt": build_system_prompt(),
        }
        PROMPT_SNAPSHOTS.append(snap)
    except Exception as e:
        PROMPT_SNAPSHOTS.append({
            "tag": tag,
            "note": f"{note} | snapshot_error={e}",
            "feedback_count": len(PROMPT_FEEDBACK_HISTORY),
            "feedback_tail": PROMPT_FEEDBACK_HISTORY[-6:],
            "prompt": "",
        })


def _format_file_guidance(entry: Dict[str, Any], filename: str) -> str:
    hints: List[str] = []
    base = os.path.basename(filename)
    if base in FILE_FEEDBACK_HISTORY and FILE_FEEDBACK_HISTORY[base]:
        hints.extend(FILE_FEEDBACK_HISTORY[base][-3:])
    if PROMPT_FEEDBACK_HISTORY:
        hints.append("全局近期失败摘要: " + " || ".join(PROMPT_FEEDBACK_HISTORY[-2:]))

    if entry.get("success_dp", False):
        hints.append(
            f"参考信号: cnip DP 已成功，dp_mems={entry.get('dp_mems','?')}。请优先收敛到与 DP 一致的计数口径。"
        )
    if entry.get("success_dfs", False):
        hints.append(
            f"参考信号: cnip DFS 已成功，dfs_max_mems={entry.get('dfs_max_mems','?')}。"
            "若与 DP 冲突，以 DP 计数口径优先，但路径必须可行。"
        )
    if entry.get("success_dp", False) and entry.get("success_dfs", False):
        hints.append("若 DP 与 DFS 不一致：优先与 DP mems 对齐，同时借助 DFS 可行路径约束避免不可行分支。")
    return "\n".join(hints).strip()


def _record_file_feedback(entry: Dict[str, Any]) -> None:
    base = entry.get("basename", "")
    if not base:
        return
    fb: List[str] = []
    if entry.get("success_dp", False) and (not entry.get("gpt_eq_dp_mems", False)):
        fb.append(
            f"{base}: 上轮 GPT={entry.get('gpt_mems','?')} 与 DP={entry.get('dp_mems','?')} 不一致。"
            "下轮必须只统计显式变量读写，重新逐行核对。"
        )
    if entry.get("success_dfs", False) and (not entry.get("gpt_eq_dfs_mems", False)):
        fb.append(f"{base}: 上轮 GPT 与 DFS 最大 mems 不一致。请复查分支可行性和循环展开上限。")
    if not entry.get("success_gpt", False):
        fb.append(f"{base}: 上轮 GPT 输出解析失败，必须返回严格 JSON。")
    if entry.get("success_gpt", False) and str(entry.get("gpt_mems", "")).strip() != "-1" and entry.get("eppath_feasible", "unknown") != "true":
        fb.append(
            f"{base}: 上轮路径被 eppather 判定为 {entry.get('eppath_feasible','unknown')}({entry.get('eppath_feasible_reason','')})。"
            "下轮必须避免冲突谓词，确保单路径可执行。"
        )
    if fb:
        FILE_FEEDBACK_HISTORY.setdefault(base, []).extend(fb[-2:])


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
    def _valid_dp_int(v: Any) -> bool:
        if isinstance(v, int):
            return v >= -1
        if isinstance(v, str) and re.fullmatch(r"-?\d+", v):
            return int(v) >= -1
        return False

    reasons: List[str] = []
    examples: List[str] = []
    for e in failed_entries[:10]:
        name = e.get("basename", "")
        if not e.get("success_gpt", False):
            reasons.append(f"{name}: GPT失败({e.get('gpt_error', 'unknown')})，需要更严格输出 JSON + 可行路径。")
        if not e.get("success_dfs", False):
            reasons.append(f"{name}: DFS失败({e.get('dfs_error', 'unknown')})，请避免不可行分支。")
        if not e.get("success_dp", False):
            reasons.append(f"{name}: DP失败({e.get('dp_error', 'unknown')})，请检查路径格式与语义一致性。")
        if e.get("success_gpt", False) and str(e.get("gpt_mems", "")).strip() != "-1" and e.get("eppath_feasible", "unknown") != "true":
            reasons.append(
                f"{name}: eppather判定路径不可行/不确定({e.get('eppath_feasible','unknown')}:{e.get('eppath_feasible_reason','')})，"
                "请修正分支谓词矛盾并确保路径可执行。"
            )
        if (
            e.get("success_dp", False)
            and str(e.get("dp_mems", "")).strip() == "-1"
            and e.get("success_dfs", False)
            and isinstance(e.get("dfs_max_mems", ""), str)
            and re.fullmatch(r"-?\d+", e.get("dfs_max_mems", ""))
            and int(e.get("dfs_max_mems", "0")) >= 0
        ):
            reasons.append(
                f"{name}: DP给出-1(不可行)但DFS给出可行mems={e.get('dfs_max_mems','?')}，请优先怀疑DP结果异常并复核代码/工具输出。"
            )
        if (
            e.get("success_gpt", False)
            and e.get("success_dp", False)
            and _valid_dp_int(e.get("dp_mems", ""))
            and (not e.get("gpt_eq_dp_mems", False))
        ):
            reasons.append(
                f"{name}: GPT与DP不一致(gpt={e.get('gpt_mems','?')}, dp={e.get('dp_mems','?')}, diff={e.get('gpt_dp_mems_diff','?')})，"
                "请严格按DP口径重算分支条件与循环展开。"
            )
            if len(examples) < 2:
                examples.append(
                    f"示例{len(examples)+1}: {name} 中 GPT={e.get('gpt_mems','?')} 但 DP={e.get('dp_mems','?')}，"
                    "下轮应减少隐含临时量计数，只保留显式变量读写。"
                )
    if not reasons:
        reasons.append("批量执行出现失败，请提高路径可行性和 MEMS 计数一致性。")
    feedback = " | ".join(reasons[:5])
    if examples:
        feedback += " | " + " | ".join(examples)
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


def call_gpt_for_mems(code: str, max_retries: int = 2, timeout_sec: int = 90, guidance: str = "") -> Tuple[Optional[int], str, str]:
    url = f"{BASE_URL.rstrip('/')}/chat/completions"
    headers = {
        "Authorization": f"Bearer {API_KEY}",
        "Content-Type": "application/json",
    }
    headers.update(_load_extra_headers())

    last_text = ""
    for model_name in MODEL_CANDIDATES:
        print(f"      [GPT] trying model: {model_name}")
        for attempt in range(max_retries + 1):
            payload = {
                "model": model_name,
                "messages": [
                    {"role": "system", "content": build_system_prompt()},
                    {"role": "user", "content": build_user_prompt(code, guidance=guidance)},
                ],
                "temperature": 0.0,
            }

            try:
                resp = requests.post(url, headers=headers, data=json.dumps(payload), timeout=timeout_sec)
                if resp.status_code != 200:
                    err_info = _extract_api_error(resp.text)
                    msg = err_info.get("message", "")
                    typ = err_info.get("type", "")
                    code_ = err_info.get("code", "")
                    line = f"model={model_name} [HTTP {resp.status_code}] type={typ} code={code_} msg={msg}"
                    line = _sanitize_secrets(line)
                    print(f"      [GPT] HTTP error: {short_err(line, 380)}")

                    if _is_model_access_error(resp.status_code, msg, code_):
                        break

                    last_text = line
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
    c_files = glob.glob(os.path.join(INPUT_FOLDER, INPUT_GLOB))
    c_files.sort()
    if MAX_FILES > 0:
        c_files = c_files[:MAX_FILES]
    print(f"  {INPUT_FOLDER}: 找到 {len(c_files)} 个 .c 文件 (glob={INPUT_GLOB}, max_files={MAX_FILES})")

    print(f"== 共 {len(c_files)} 个 C 文件将被处理 ==\n")
    if not c_files:
        print("[终止] 未在指定文件夹下发现任何 .c 文件。")
        return

    os.makedirs(OUTPUT_TRUE_FOLDER, exist_ok=True)
    analyzer_cache: Dict[str, Dict[str, Any]] = {}

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
                print("  [3/3] 调用 GPT 分析（使用全局+文件级回溯提示以逼近 DP/DFS）")
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

            if success_gpt and success_dp and (not entry["gpt_eq_dp_mems"]):
                retry_guidance = (
                    f"{file_guidance}\n"
                    f"本文件强制校准: 你上一版 gpt_mems={gpt_mems_val}, 目标 dp_mems={dp_mems_val}。\n"
                    "请重新执行“约束→枚举→计数→自检”，并避免隐含临时量过计数。"
                )
                print("  [3/3-重试] GPT 与 DP 不一致，触发一次文件级强校准重试")
                t1 = time.time()
                rg_mems, rg_path, rg_raw = call_gpt_for_mems(code_text, guidance=retry_guidance)
                entry["gpt_time"] = f"{(float(entry['gpt_time']) + (time.time() - t1)):.4f}"
                if rg_mems is not None and (rg_path or rg_mems == -1):
                    entry.update({"gpt_mems": str(rg_mems), "gpt_path": rg_path, "gpt_error": ""})
                    gpt_mems_val = to_int(entry.get("gpt_mems", ""))
                    entry["gpt_eq_dp_mems"] = bool(
                        success_dp and gpt_mems_val is not None and dp_mems_val is not None and gpt_mems_val == dp_mems_val
                    )
                    entry["gpt_eq_dfs_mems"] = bool(
                        success_dfs and gpt_mems_val is not None and dfs_mems_val is not None and gpt_mems_val == dfs_mems_val
                    )
                    print(f"  [重试结果] gpt_mems={entry['gpt_mems']} | 与DP一致={entry['gpt_eq_dp_mems']}")
                else:
                    entry["gpt_error"] = short_err(_sanitize_secrets(rg_raw), 300) or entry.get("gpt_error", "retry_parse_fail")
                    print("  [重试结果] 解析失败，保留首轮 GPT 结果")
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
        return local_results

    results: List[Dict[str, Any]] = []
    stages = _parse_batch_stages(len(c_files))
    checkpoint_5 = min(BASELINE_STAGE1, len(c_files)) if c_files else 0
    checkpoint_20 = min(BASELINE_STAGE2, len(c_files)) if c_files else 0
    baseline_checkpoints = []
    for x in [checkpoint_5, checkpoint_20]:
        if x > 0 and x not in baseline_checkpoints:
            baseline_checkpoints.append(x)
    max_baseline_checkpoint = max(baseline_checkpoints) if baseline_checkpoints else 0
    baseline_passed: Dict[int, bool] = {cp: False for cp in baseline_checkpoints}
    print(
        f"[批量策略] stages={stages}, max_backtrack_rounds={MAX_BACKTRACK_ROUNDS}, "
        f"require_gpt_dp_match={REQUIRE_GPT_DP_MATCH}, require_eppath_feasible={REQUIRE_EPATH_FEASIBLE}, "
        f"eppath_api={'on' if EPATH_FEASIBILITY_API else 'off(local_parser)'}"
    )
    print(
        f"[baseline门槛] checkpoints={baseline_checkpoints}, threshold>{BASELINE_PASS_THRESHOLD:.2%} "
        "(指标=GPT=DP准确率)"
    )

    try:
        round_idx = 0
        record_prompt_snapshot("initial", "before_backtrack_loop")
        while round_idx < MAX_BACKTRACK_ROUNDS:
            round_idx += 1
            print(f"\n==== 自动回溯轮次 {round_idx}/{MAX_BACKTRACK_ROUNDS} ====")
            record_prompt_snapshot(f"round_{round_idx}_start", "round_start")
            round_failed = False
            baseline_passed = {cp: False for cp in baseline_checkpoints}
            for stage in stages:
                subset = c_files[:stage]
                print(f"\n---- 阶段执行: 前 {stage} 个样例 ----")
                stage_results = process_files(subset)
                _print_stage_summary(f"round={round_idx},stage={stage}", stage_results)
                stage_acc = _stage_accuracy(stage_results)
                print(f"[baseline] stage={stage} GPT=DP准确率={stage_acc:.2%}")
                if stage in baseline_checkpoints:
                    BASELINE_ACCURACY_HISTORY.setdefault(stage, []).append(stage_acc)
                    baseline_passed[stage] = stage_acc > BASELINE_PASS_THRESHOLD
                    if not baseline_passed[stage]:
                        fb = (
                            f"baseline未达标: stage={stage}, GPT=DP准确率={stage_acc:.2%} "
                            f"<= {BASELINE_PASS_THRESHOLD:.2%}。请优先修正MEMS计数口径与路径可行性。"
                        )
                        PROMPT_FEEDBACK_HISTORY.append(fb)
                        record_prompt_snapshot(f"round_{round_idx}_stage_{stage}_baseline_fail", fb)
                        print(f"[自动回溯] {fb}")
                        round_failed = True
                        break
                strict_guard_enabled = (
                    (max_baseline_checkpoint <= 0)
                    or (stage > max_baseline_checkpoint and baseline_passed.get(max_baseline_checkpoint, False))
                )
                if strict_guard_enabled:
                    failed = []
                    for x in stage_results:
                        base_ok = x["success_gpt"] and x["success_dfs"] and x["success_dp"]
                        if not base_ok:
                            failed.append(x)
                            continue
                        dp_mems_s = x.get("dp_mems", "")
                        dp_mems_valid = isinstance(dp_mems_s, int) and dp_mems_s >= -1
                        if isinstance(dp_mems_s, str) and re.fullmatch(r"-?\d+", dp_mems_s):
                            dp_mems_valid = int(dp_mems_s) >= -1
                        if REQUIRE_GPT_DP_MATCH and dp_mems_valid and (not x.get("gpt_eq_dp_mems", False)):
                            failed.append(x)
                            continue
                        if REQUIRE_EPATH_FEASIBLE and x.get("success_gpt", False) and str(x.get("gpt_mems", "")).strip() != "-1":
                            if x.get("eppath_feasible", "unknown") != "true":
                                failed.append(x)
                    if failed:
                        for fx in failed:
                            _record_file_feedback(fx)
                        fb = _add_feedback_from_failures(failed)
                        record_prompt_snapshot(f"round_{round_idx}_stage_{stage}_feedback", fb)
                        print(f"[自动回溯] 阶段 {stage} 失败 {len(failed)} 个。错误摘要: {fb}")
                        round_failed = True
                        break
                else:
                    print(
                        f"[baseline推进] 阶段 {stage} 仅按基线准确率门槛推进，"
                        "暂不启用逐样本严格失败拦截。"
                    )
                results = stage_results
                print(f"[阶段成功] 前 {stage} 个样例全部执行成功。")

            if not round_failed and 5 in [r["stage"] for r in stage_accuracy_records if r["round"] == round_idx] and 20 in [r["stage"] for r in stage_accuracy_records if r["round"] == round_idx]:
                round_stage_map = {
                    r["stage"]: r for r in stage_accuracy_records if r["round"] == round_idx
                }
                acc5 = float(round_stage_map[5]["accuracy"])
                acc20 = float(round_stage_map[20]["accuracy"])
                if acc5 > 0.5 and acc20 > 0.5:
                    print(
                        f"[gate通过] 5样例准确率={acc5:.2%}, 20样例准确率={acc20:.2%}，"
                        "触发全量样例批量执行。"
                    )
                    full_stage = len(c_files)
                    full_results = process_files(c_files)
                    _print_stage_summary(f"round={round_idx},stage=ALL({full_stage})", full_results)
                    full_acc, full_valid_n = _compute_gpt_baseline_accuracy(full_results)
                    stage_accuracy_records.append(
                        {
                            "round": round_idx,
                            "stage": full_stage,
                            "accuracy": full_acc,
                            "valid_count": full_valid_n,
                        }
                    )
                    print(
                        f"[baseline] 全量 stage={full_stage} GPT=DP baseline 准确率: "
                        f"{full_acc:.2%} (有效样本={full_valid_n})"
                    )
                    results = full_results
                    gate_passed = True
                else:
                    print(
                        f"[gate未通过] 5样例准确率={acc5:.2%}, 20样例准确率={acc20:.2%}。"
                        "继续按原阶段策略执行。"
                    )

            if not round_failed and (not gate_passed):
                for stage in stages:
                    if stage in gated_stage_order:
                        continue
                    subset = c_files[:stage]
                    print(f"\n---- 阶段执行: 前 {stage} 个样例 ----")
                    stage_results = process_files(subset)
                    _print_stage_summary(f"round={round_idx},stage={stage}", stage_results)
                    stage_acc, valid_n = _compute_gpt_baseline_accuracy(stage_results)
                    stage_accuracy_records.append(
                        {
                            "round": round_idx,
                            "stage": stage,
                            "accuracy": stage_acc,
                            "valid_count": valid_n,
                        }
                    )
                    print(
                        f"[baseline] stage={stage} 使用 GPT=DP 作为 baseline 准确率: "
                        f"{stage_acc:.2%} (有效样本={valid_n})"
                    )
                    failed = []
                    for x in stage_results:
                        base_ok = x["success_gpt"] and x["success_dfs"] and x["success_dp"]
                        if not base_ok:
                            failed.append(x)
                            continue
                        dp_mems_s = x.get("dp_mems", "")
                        dp_mems_valid = isinstance(dp_mems_s, int) and dp_mems_s >= -1
                        if isinstance(dp_mems_s, str) and re.fullmatch(r"-?\d+", dp_mems_s):
                            dp_mems_valid = int(dp_mems_s) >= -1
                        if REQUIRE_GPT_DP_MATCH and dp_mems_valid and (not x.get("gpt_eq_dp_mems", False)):
                            failed.append(x)
                            continue
                        if REQUIRE_EPATH_FEASIBLE and x.get("success_gpt", False) and str(x.get("gpt_mems", "")).strip() != "-1":
                            if x.get("eppath_feasible", "unknown") != "true":
                                failed.append(x)
                    if failed:
                        for fx in failed:
                            _record_file_feedback(fx)
                        fb = _add_feedback_from_failures(failed)
                        print(f"[自动回溯] 阶段 {stage} 失败 {len(failed)} 个。错误摘要: {fb}")
                        round_failed = True
                        break
                    results = stage_results
                    print(f"[阶段成功] 前 {stage} 个样例全部执行成功。")

            if not round_failed:
                print("[完成] 所有批量阶段均执行成功。")
                record_prompt_snapshot(f"round_{round_idx}_completed", "all_stages_success")
                break
            if round_idx >= MAX_BACKTRACK_ROUNDS:
                print(f"[停止] 已达到最大回溯轮次，保留最近一轮失败结果。")
                results = stage_results
                record_prompt_snapshot(f"round_{round_idx}_stopped", "max_backtrack_reached")
            else:
                print("[回溯] 已更新 prompt 反馈，重新从 5 个样例开始执行。")
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
    ]

    df = pd.DataFrame(results, columns=cols)
    df.to_csv(SUMMARY_CSV, index=False, encoding="utf-8")
    df.to_excel(SUMMARY_XLSX, index=False)

    df_true = df[df["is_true"] == True].copy()
    df_true.to_csv(TRUE_ONLY_CSV, index=False, encoding="utf-8")
    df_true.to_excel(TRUE_ONLY_XLSX, index=False)

    df_gpt_fail = df[df["success_gpt"] == False].copy()
    df_gpt_fail.to_csv(GPT_FAIL_CSV, index=False, encoding="utf-8")
    df_gpt_fail.to_excel(GPT_FAIL_XLSX, index=False)

    total = len(df)
    true_count = int(df["is_true"].sum()) if total else 0
    dp_ok = int(df["success_dp"].sum()) if total else 0
    dfs_ok = int(df["success_dfs"].sum()) if total else 0
    gpt_ok = int(df["success_gpt"].sum()) if total else 0
    eppath_ok = int((df["eppath_feasible"] == "true").sum()) if total and "eppath_feasible" in df.columns else 0
    gpt_dp_diffs: List[float] = []
    if total and "gpt_dp_mems_diff" in df.columns:
        for v in df["gpt_dp_mems_diff"].tolist():
            if isinstance(v, int):
                gpt_dp_diffs.append(float(v))
            elif isinstance(v, float):
                gpt_dp_diffs.append(v)
            elif isinstance(v, str) and re.fullmatch(r"-?\d+(\.\d+)?", v.strip()):
                gpt_dp_diffs.append(float(v.strip()))
    gpt_dp_var = _safe_variance(gpt_dp_diffs)
    baseline_acc_samples: List[float] = []
    for cp in sorted(BASELINE_ACCURACY_HISTORY.keys()):
        baseline_acc_samples.extend(BASELINE_ACCURACY_HISTORY.get(cp, []))
    baseline_acc_var = _safe_variance(baseline_acc_samples)

    final_prompt = build_system_prompt()
    with open(FINAL_PROMPT_TXT, "w", encoding="utf-8") as f:
        f.write(final_prompt)
        f.write("\n")

    with open(PROMPT_HISTORY_JSON, "w", encoding="utf-8") as f:
        json.dump(PROMPT_SNAPSHOTS, f, ensure_ascii=False, indent=2)

    print(f"  [表格] 汇总CSV: {SUMMARY_CSV}")
    print(f"  [表格] 汇总XLSX: {SUMMARY_XLSX}")
    print(f"  [表格] TRUE子集CSV: {TRUE_ONLY_CSV}")
    print(f"  [表格] TRUE子集XLSX: {TRUE_ONLY_XLSX}")
    print(f"  [表格] GPT失败子集CSV: {GPT_FAIL_CSV}")
    print(f"  [表格] GPT失败子集XLSX: {GPT_FAIL_XLSX}")
    print(f"  [提示词] 回溯历史JSON: {PROMPT_HISTORY_JSON}")
    print(f"  [提示词] 最终提示词TXT: {FINAL_PROMPT_TXT}")
    print("\n==== 最终系统提示词（回溯后） ====")
    print(final_prompt)

    print("\n==== 统计结果 ====")
    if total:
        print(f"  总文件数: {total}")
        print(f"  GPT成功:  {gpt_ok}/{total} ({gpt_ok/total:.2%})")
        print(f"  GPT失败:  {total - gpt_ok}/{total} ({(total - gpt_ok)/total:.2%})")
        print(f"  DFS成功:  {dfs_ok}/{total} ({dfs_ok/total:.2%})")
        print(f"  DP成功:   {dp_ok}/{total} ({dp_ok/total:.2%})")
        print(f"  GPT=DP:   {int(df['gpt_eq_dp_mems'].sum())}/{total} ({df['gpt_eq_dp_mems'].mean():.2%})")
        print(f"  GPT=DFS:  {int(df['gpt_eq_dfs_mems'].sum())}/{total} ({df['gpt_eq_dfs_mems'].mean():.2%})")
        print(f"  DP=DFS:   {int(df['dp_eq_dfs_mems'].sum())}/{total} ({df['dp_eq_dfs_mems'].mean():.2%})")
        print(f"  eppather判定可行: {eppath_ok}/{total} ({eppath_ok/total:.2%})")
        print(f"  稳定性方差(gpt_dp_mems_diff): {gpt_dp_var:.6f}")
        print(f"  baseline准确率方差(stage-level): {baseline_acc_var:.6f}")
        for cp in sorted(BASELINE_ACCURACY_HISTORY.keys()):
            vals = BASELINE_ACCURACY_HISTORY.get(cp, [])
            var = _safe_variance(vals)
            last = vals[-1] if vals else 0.0
            print(
                f"  稳定性方差(stage={cp}, GPT=DP准确率): {var:.6f} "
                f"(latest={last:.2%}, rounds={len(vals)})"
            )
        print(f"  TRUE(三方一致并已保存到{OUTPUT_TRUE_FOLDER}): {true_count}/{total} ({true_count/total:.2%})")
        print("\n==== 稳定性方差 ====")
        print(f"  baseline准确率方差(stage-level): {baseline_acc_var:.6f}")
        print(f"  GPT-DP mems差值方差(file-level): {gpt_dp_diff_var:.6f}")
        print(f"  GPT-DFS mems差值方差(file-level): {gpt_dfs_diff_var:.6f}")
    else:
        print("  总文件数: 0")


if __name__ == "__main__":
    main()
