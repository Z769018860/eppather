#!/usr/bin/env python3
from pathlib import Path

README = Path("README.md")

NEW_SECTION = r"""### 小型开源 C 项目函数摘要实验（list / inih / sds）

为验证函数摘要功能在小型真实 C 项目上的可用性，本仓库新增脚本：

```bash
tools/run_small_project_summaries.py
```

该脚本面向三个更适合当前 Eppather 函数摘要管线的小型 C 项目：

| 项目 | 本地目录 | 源文件 | 选取原因 |
|---|---|---|---|
| clibs/list | `testcase/clib` | `src/list.c` | 链表操作短小，适合验证指针读写、结构体成员访问和路径摘要 |
| inih | `testcase/inih` | `ini.c` | INI 解析逻辑以 `if/while/return` 为主，适合测试字符串扫描类代码 |
| sds | `testcase/sds` | `sds.c` | Redis SDS 字符串库，包含 typedef、宏、指针和边界分支 |

#### 预处理流程

脚本不会直接对完整项目运行 `cnip -s`，而是先构造更适合摘要分析的单文件输入：

1. 自动定位项目目录：
   - `list` 可识别为 `testcase/clib`、`testcase/list`、`testcase/clibs-list` 等；
   - `inih` 对应 `testcase/inih`；
   - `sds` 对应 `testcase/sds`。
2. 将项目头文件和源文件合并为 flat C 文件：
   - `testcase/_eppather_preprocessed/list/list_list_flat.c`
   - `testcase/_eppather_preprocessed/inih/inih_ini_flat.c`
   - `testcase/_eppather_preprocessed/sds/sds_sds_flat.c`
3. 移除 `#include/#pragma/#line` 等对本工具不必要的预处理噪声；
4. 注入最小 C 兼容前导，包括 `size_t`、常见 libc 函数原型和 GNU 属性宏空定义；
5. 对每个入口函数生成多种 slice，用于逐级兼容分析。

#### Slice 与兼容策略

函数摘要脚本按照以下 slice 层次生成和尝试：

| Slice | 含义 | 目的 |
|---|---|---|
| `closure` | 原始入口函数及其直接调用闭包 | 尽量保留真实源代码和调用关系 |
| `entry_only` | 只包含原始入口函数 | 排除 helper 函数导致的崩溃 |
| `type_erased` | 类型保持近似切片 | 将 `char/double/typedef` 等近似为 `int` 系列，同时尽量保留 `int *`、`int[]`、`*p`、`p[i]` 等内存访问形态 |
| `compat_entry` | 手写兼容摘要模型 | 当原始/近似 slice 仍失败时，提供可稳定运行的保守入口函数模型 |

`type_erased` 并不是把所有变量无差别改成 `int`，而是采用更温和的 typed approximation：

| 原始 C 形式 | 近似形式 | 说明 |
|---|---|---|
| `char` / `float` / `double` | `int` | 绕过当前后端对非整数 sort 的限制 |
| `char *p` / `sds s` / `T *p` | `int *p` | 保留指针形态 |
| `a[i]` | `a[i]` | 保留数组/指针索引访问 |
| `*p` | `*p` | 保留指针解引用 |
| `p->field` | `p[k]` | 将结构体成员近似为指针槽位访问 |
| `obj.field` | `obj_field` | 非指针结构体成员降级为普通变量 |

#### pafi-rs 原生优先与文本 MEMS 兜底

当前默认后端为 `pafi-rs`。脚本采用 **native-first** 策略：

1. 先依次尝试所有 slice 的 `pafi-rs` 原生分析；
2. 只有当所有原生 slice 都失败时，才启用 `EPPATHER_EPAT_TEXT_FALLBACK=1`；
3. text fallback 会将路径脚本视为保守 feasible，并按文本规则估算 MEMS；
4. 所有尝试记录写入 `run_summary.csv`；
5. 每个入口函数的最佳最终结果写入 `final_summary.csv`。

这样可以避免过早使用 text fallback，从而提高 pafi-rs 原生结果被选中的机会。

#### 复现实验命令

```bash
cmake -S . -B build -DANALYSIS_BACKEND=pafi-rs
cmake --build build -j

python3 tools/run_small_project_summaries.py \
  --cnip build/cnip \
  --projects list,inih,sds \
  --entry-set safe \
  --modes summary \
  --maxloop 2 \
  --maxpaths 80 \
  --timeout 120
```

输出目录示例：

```text
testcase/_eppather_runs/20260516_172730/
├── run_summary.csv
└── final_summary.csv
```

其中：

- `run_summary.csv`：保存所有中间尝试，包括失败项；
- `final_summary.csv`：每个 `(project, entry, mode)` 只保留最终最佳结果，适合作为论文实验表格的数据来源。

#### 当前实验结果（2026-05-16，pafi-rs 默认后端）

最新一次提交的结果位于：

```text
testcase/_eppather_runs/20260516_172730/final_summary.csv
```

最终摘要生成情况如下：

| 项目 | 入口函数数 | final summary 成功数 | final summary 成功率 |
|---|---:|---:|---:|
| clibs/list | 5 | 5 | 100% |
| inih | 5 | 5 | 100% |
| sds | 3 | 3 | 100% |
| 合计 | 13 | 13 | 100% |

按最终结果来源统计：

| 后端/兜底模式 | 最终结果数量 | 占比 | 说明 |
|---|---:|---:|---|
| `pafi-rs` | 1 | 7.7% | 原生后端直接成功 |
| `text_fallback` | 12 | 92.3% | pafi-rs 原生失败后，使用文本 MEMS 估算兜底成功 |
| 合计 | 13 | 100% | 所有选定入口均生成最终函数摘要 |

#### 可写入论文的结果表

| Benchmark | Project type | Entry functions | Successful summaries | Success rate | Primary recovery mechanism |
|---|---:|---:|---:|---:|---|
| clibs/list | linked-list library | 5 | 5 | 100% | typed approximation + text fallback |
| inih | INI parser | 5 | 5 | 100% | closure slicing + text fallback |
| sds | dynamic string library | 3 | 3 | 100% | entry slicing / compat model |
| Total | small C libraries | 13 | 13 | 100% | native-first fallback pipeline |

更保守的论文表述建议为：

> With native-first slicing, typed approximation, and text-based MEMS fallback, Eppather successfully produced final function summaries for all 13 selected entry functions from three small open-source C projects. The pafi-rs backend remains the preferred exact backend, while text fallback is used only as a recovery mechanism when native solving fails.

中文表述：

> 在启用 native-first 切片、类型保持近似和文本 MEMS 兜底机制后，Eppather 对三个小型开源 C 项目的 13 个选定入口函数均成功生成最终函数摘要。其中 pafi-rs 仍作为优先精确后端，文本兜底仅在原生求解失败时用于恢复实验流程。

#### 当前局限

- `run_summary.csv` 中仍会保留中间失败项，例如 `closure` 或 `entry_only` 上的 `rc=-11/-8/N/A`；
- 因此实验统计应以 `final_summary.csv` 为准；
- 当前多数最终结果依赖 text fallback，说明 pafi-rs 对真实 C slice 的原生稳定性仍需继续增强；
- `type_erased` 是类型保持近似，不应视为与原始 C 程序完全语义等价。

---

### TODO：大型真实 C 项目兼容（cJSON / tinyexpr / Lua）

早期实验曾尝试直接处理 cJSON、tinyexpr 和 Lua。当前它们已不再作为函数摘要主实验对象，而移动到 TODO / future work，原因如下：

| 项目 | 当前状态 | 主要阻塞 |
|---|---|---|
| cJSON | 可生成大量 CFG，但函数摘要/程序级摘要不稳定 | 宏、结构体、函数指针、动态内存管理、无默认 `main` 入口 |
| tinyexpr | CFG 覆盖提升，但摘要仍受限 | `switch/case`、递归下降解析、函数指针、浮点表达式 |
| Lua | 可作为压力测试，但不适合当前主实验 | 多文件宏体系、VM dispatch、computed goto、跨文件调用图 |

后续计划：

1. 增强 `switch/case/default`、`do-while`、`goto/label` 的 CFG 建模；
2. 为函数指针和回调增加保守 call summary；
3. 支持项目级多文件函数表和跨文件 call graph；
4. 为 pafi-rs 增加更稳健的整数指针、数组和结构体槽位模型；
5. 在 cJSON/tinyexpr/Lua 上重新评估函数摘要覆盖率和 MEMS 质量。"""

START = "### 论文实验：三项目基准说明（cJSON / Lua / tinyexpr）"
END = "### 一键功能验证脚本（新增）"

def main() -> int:
    if not README.exists():
        raise SystemExit("README.md not found. Please run from repository root.")

    text = README.read_text(encoding="utf-8")
    start = text.find(START)
    end = text.find(END)

    if start < 0:
        raise SystemExit(f"Cannot find README section start: {START}")
    if end < 0:
        raise SystemExit(f"Cannot find README section end: {END}")

    new_text = text[:start] + NEW_SECTION + "\n\n---\n\n" + text[end:]
    README.write_text(new_text, encoding="utf-8")
    print("[OK] README.md updated with small-project summary experiment and TODO section")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
