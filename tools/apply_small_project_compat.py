#!/usr/bin/env python3
from pathlib import Path

README = Path("README.md")

NEW_SECTION = r'#### 当前实验结果（2026-05-16，pafi-rs 默认后端，全函数模式）\n\n最新一次提交的全函数实验结果位于：\n\n```text\ntestcase/_eppather_runs/20260516_180425/final_summary.csv\n```\n\n本轮实验使用 `--entry-set all`，即对三个小型 C 项目中由预处理脚本发现的候选入口函数进行函数摘要生成。`run_summary.csv` 保留所有中间尝试，`final_summary.csv` 为每个 `(project, entry, mode)` 选择最终最佳结果，因此成功率统计以 `final_summary.csv` 为准。\n\n复现实验命令：\n\n```bash\ncmake -S . -B build -DANALYSIS_BACKEND=pafi-rs\ncmake --build build -j\n\npython3 tools/run_small_project_summaries.py \\\n  --cnip build/cnip \\\n  --projects list,inih,sds \\\n  --entry-set all \\\n  --modes summary \\\n  --maxloop 2 \\\n  --maxpaths 80 \\\n  --timeout 120\n```\n\n最终摘要生成情况如下：\n\n| 项目 | 脚本发现/尝试入口数 | final summary 成功数 | final summary 成功率 | pafi-rs 原生最终结果数 |\n|---|---:|---:|---:|---:|\n| clibs/list | 9 | 9 | 100.0% | 6 |\n| inih | 10 | 10 | 100.0% | 5 |\n| sds | 51 | 35 | 68.6% | 17 |\n| 合计 | 70 | 54 | 77.1% | 28 |\n\n本轮结果显示，Eppather 已能够在小型 C 项目范围内对项目级函数集合进行批量摘要生成。`clibs/list` 与 `inih` 的候选入口均成功生成最终函数摘要；`sds` 的函数数量和语法复杂度更高，部分候选入口仍受宏展开、外部声明、复杂内存布局和后端稳定性影响，因此最终摘要成功率低于另外两个项目。\n\n#### 可写入论文的结果表\n\n| Benchmark | Project type | Attempted functions | Successful summaries | Success rate |\n|---|---|---:|---:|---:|\n| clibs/list | linked-list library | 9 | 9 | 100.0% |\n| inih | INI parser | 10 | 10 | 100.0% |\n| sds | dynamic string library | 51 | 35 | 68.6% |\n| Total | small C libraries | 70 | 54 | 77.1% |\n\n论文表述建议：\n\n> Eppather was evaluated on three small open-source C projects: clibs/list, inih, and sds. In the all-function setting, the preprocessing pipeline identified 70 candidate entry functions and successfully generated final function summaries for 54 of them, yielding an overall success rate of 77.1%. The results show that Eppather can support project-level function-summary generation for small C projects, while larger and more macro-heavy C systems remain future work.\n\n中文表述：\n\n> 我们在 clibs/list、inih 和 sds 三个小型开源 C 项目上评估 Eppather 的函数摘要能力。在全函数设置下，预处理流程共发现并尝试 70 个候选入口函数，其中 54 个成功生成最终函数摘要，总体成功率为 77.1%。结果表明，Eppather 目前已经可以支持小型 C 项目的项目级函数摘要生成；对于更复杂、更依赖宏和跨文件机制的 C 项目，仍需进一步增强。\n'

START = "#### 当前实验结果（2026-05-16，pafi-rs 默认后端）"
END = "#### 当前局限"

def main() -> int:
    if not README.exists():
        raise SystemExit("README.md not found. Please run this script from the repository root.")

    text = README.read_text(encoding="utf-8")
    start = text.find(START)
    if start < 0:
        raise SystemExit(f"Cannot find section start: {START}")

    end = text.find(END, start)
    if end < 0:
        raise SystemExit(f"Cannot find section end: {END}")

    text = text[:start] + NEW_SECTION + "\n\n" + text[end:]

    text = text.replace(
        "--entry-set safe \\\n  --modes summary",
        "--entry-set all \\\n  --modes summary"
    )
    text = text.replace(
        "testcase/_eppather_runs/20260516_172730/",
        "testcase/_eppather_runs/20260516_180425/"
    )
    text = text.replace(
        "testcase/_eppather_runs/20260516_172730/final_summary.csv",
        "testcase/_eppather_runs/20260516_180425/final_summary.csv"
    )

    README.write_text(text, encoding="utf-8")
    print("[OK] README.md updated with 20260516_180425 all-function summary results.")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
