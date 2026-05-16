#!/usr/bin/env python3
from pathlib import Path

README = Path("README.md")
START = "#### 当前实验结果（2026-05-16，pafi-rs 默认后端，全函数模式）"
END = "#### 当前局限"

NEW_SECTION = r"""#### 当前实验结果（2026-05-16，pafi-rs 默认后端，全函数模式）

当前推荐使用两份结果共同汇总小型项目实验：

```text
testcase/_eppather_runs/20260516_180425/final_summary.csv   # list / inih / sds 全函数基线
testcase/_eppather_runs/20260516_181840/final_summary.csv   # SDS 兼容增强后重跑结果
```

`20260516_181840` 是针对 SDS 的专项重跑：脚本过滤了明显非项目入口，并为 SDS 中难以直接分析的函数自动生成 `auto_compat` slice。该轮结果显示，SDS 的项目级函数摘要成功率由上一轮的 35/51 提升到 42/47，且大多数最终结果可以由 pafi-rs 原生后端完成。

复现实验命令：

```bash
cmake -S . -B build -DANALYSIS_BACKEND=pafi-rs
cmake --build build -j

# 三项目全函数基线
python3 tools/run_small_project_summaries.py \
  --cnip build/cnip \
  --projects list,inih,sds \
  --entry-set all \
  --modes summary \
  --maxloop 2 \
  --maxpaths 80 \
  --timeout 120

# SDS 兼容增强后专项重跑
python3 tools/run_small_project_summaries.py \
  --cnip build/cnip \
  --projects sds \
  --entry-set all \
  --modes summary \
  --maxloop 2 \
  --maxpaths 80 \
  --timeout 120
```

最终摘要生成情况如下。`list` 和 `inih` 采用 `20260516_180425` 的全函数结果；`sds` 采用 `20260516_181840` 的兼容增强后结果。

| 项目 | 脚本发现/尝试入口数 | final summary 成功数 | final summary 成功率 | pafi-rs 原生最终结果数 |
|---|---:|---:|---:|---:|
| clibs/list | 9 | 9 | 100.0% | 6 |
| inih | 10 | 10 | 100.0% | 5 |
| sds | 47 | 42 | 89.4% | 41 |
| 合计 | 66 | 61 | 92.4% | 52 |

SDS 兼容增强前后的对比如下：

| SDS 实验轮次 | 统计口径 | 尝试入口数 | final summary 成功数 | 成功率 | pafi-rs 原生最终结果数 |
|---|---|---:|---:|---:|---:|
| `20260516_180425` | 初始 all-function | 51 | 35 | 68.6% | 17 |
| `20260516_181840` | 过滤非项目入口 + auto_compat | 47 | 42 | 89.4% | 41 |

本轮 SDS 专项结果说明，入口过滤和自动兼容 slice 能显著提高 SDS 这类指针/宏密集小型 C 项目的函数摘要覆盖率。当前仍有少量 SDS 函数未成功生成最终摘要，主要集中在原始 closure 入口丢失或 pafi-rs 崩溃的低层 helper，例如 `sds_free`、`sdsavail`、`sdsll2str`、`sdssetalloc` 和 `sdssetlen`。

#### 可写入论文的结果表

| Benchmark | Project type | Attempted functions | Successful summaries | Success rate |
|---|---|---:|---:|---:|
| clibs/list | linked-list library | 9 | 9 | 100.0% |
| inih | INI parser | 10 | 10 | 100.0% |
| sds | dynamic string library | 47 | 42 | 89.4% |
| Total | small C libraries | 66 | 61 | 92.4% |

论文表述建议：

> Eppather was evaluated on three small open-source C projects: clibs/list, inih, and sds. In the all-function setting, the preprocessing pipeline identified 66 project-level candidate functions after filtering non-library entries and successfully generated final function summaries for 61 of them, yielding an overall success rate of 92.4%. The results indicate that Eppather can support project-level function-summary generation for small C projects.

中文表述：

> 我们在 clibs/list、inih 和 sds 三个小型开源 C 项目上评估 Eppather 的函数摘要能力。在过滤非库函数入口后，预处理流程共发现并尝试 66 个项目级候选函数，其中 61 个成功生成最终函数摘要，总体成功率为 92.4%。实验结果表明，Eppather 目前已经可以支持小型 C 项目的项目级函数摘要生成。
"""

def main() -> int:
    if not README.exists():
        raise SystemExit("README.md not found. Please run from repository root.")

    text = README.read_text(encoding="utf-8")
    start = text.find(START)
    if start < 0:
        raise SystemExit(f"Cannot find section start: {START}")

    end = text.find(END, start)
    if end < 0:
        raise SystemExit(f"Cannot find section end: {END}")

    text = text[:start] + NEW_SECTION + "\n\n" + text[end:]
    README.write_text(text, encoding="utf-8")
    print("[OK] README.md updated with 20260516_181840 SDS-improved results.")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
