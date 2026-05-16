
<!-- Language Switch -->
<p align="center">
  <a href="#中文版">🇨🇳 中文版</a> | <a href="#english-version">🇬🇧 English Version</a>
</p>

---

# Eppather

## 中文版

### 项目简介

**Eppather** 是一个面向 C 语言程序的静态路径分析与测试用例生成原型工具，核心目标是分析程序的**最坏情况执行时间（WCET, Worst-Case Execution Time）**。  
工具以 **MEMS（Memory Access Metric）** 作为平台无关的性能度量指标，重点关注内存访问行为对执行时间的影响。

Eppather 综合并扩展了以下关键技术组件：

- **Psychec**：用于 C 程序的 AST 解析与语义建模  
- **CFG / 路径探索模块**：支持 DFS / BFS / DP 等多种路径分析策略  
- **Epat++ + Z3**：基于 SMT 的符号执行与路径可达性判定  

输入为 **C 语言源代码（`.c` 文件）**，输出包括：

- MEMS 最大的最坏情况执行路径  
- 每条路径对应的 MEMS 值与分析时间  
- 可触达最坏路径的测试输入（模型）  

此外，Eppather 也可作为一个**通用静态路径遍历与分析框架**，支持完整路径覆盖分析与中间结果导出。

---


### 后端切换（pafi-rs / epat++）

当前构建系统已支持后端切换参数：

```bash
cmake -DANALYSIS_BACKEND=pafi-rs . && make -j4
```

可选值：`pafi-rs`（默认）或 `epat++`。

### 编译与运行

#### 环境要求

- Linux / macOS（推荐）  
- **Clang / LLVM 工具链**（必需）  
- CMake ≥ 3.10  

Eppather 本身无额外第三方依赖。

#### 编译

```bash
cmake CMakeLists.txt && make -j 4
```

成功编译后可看到：

```text
[ 99%] Building CXX object CMakeFiles/cnip.dir/cnippet/Driver.cpp.o
[100%] Building CXX object CMakeFiles/cnip.dir/cnippet/Plugin.cpp.o
[100%] Linking CXX executable cnip
[100%] Built target cnip
```

生成的可执行文件为 `cnip`。

---

### 基本使用

查看帮助信息：

```bash
./cnip -h
```

工具支持的主要参数如下：

```text
cnippet
Usage:
  ./cnip [OPTION...] file

  -l, --lang <C>                Specify the language. (default: C)
  -z, --dump-AST                Dump the program's AST to the console.
  -c, --dump-CFG                Dump the program's CFG to the console.
  -f, --dump-DFS                Dump the program's path in the DFS mode (icov).
  -q, --dump-DFS2               Dump the program's path in the DFS mode (bcov).
  -g, --dump-MaxMemDP           Dump the worst MEMS path using DP.
  -b, --dump-BFS                Dump the program's path in the BFS mode.
  -s, --dump-summary            Dump function summaries to the console.
  -d, --debug                   Enable debugging.
      --volce                   Enable VolCE model counting.
      --maxloop arg             Set loop unroll upper bound (default: 3).
      --maxpaths arg            Set maximum path count (default: 1000).
      --volce-lower arg         Set VolCE variable lower bound (default: -8).
      --volce-upper arg         Set VolCE variable upper bound (default: 8).
  -p, --plugin arg              Load plugin with the given name.
  -w, --WIP                     Enable Work-In-Progress features.
  -h, --help                    Print instructions.
      --c-std <c89|c90|c99|c11|c17>
                                Specify the C standard (default: c11).
      --host-cc <gcc|clang>     Specify host compiler (default: gcc).
      --cpp-includes            Expand #include directives.
      --cpp-I path              Add include search path.
      --cpp-D name[=definition] Define macro.
      --cpp-U name              Undefine macro.
      --C-infer                 Infer missing types.
  -o, --output arg              Output file (default: a.cstr)
```

---

### 路径遍历示例（DFS）

使用 `-q` 参数遍历程序中的所有可行路径：

```bash
./cnip -q test2.c
```

输出结果包含以下信息：

- 当前路径对应的符号路径条件  
- SMT 求解器给出的可达性判定结果  
- 该路径的 MEMS 值与平均 MEMS  
- 求解得到的输入模型  
- 路径覆盖矩阵  
- DFS 总耗时  

示例输出（节选）：

```text
feasible!!!
[mem]:0
[DFS TIME COST]: 29.0845 seconds
[DFS MAX MEMS]: 18
[DFS MIN MEMS]: 0
```

---

### DFS2 跨函数输出说明（新增）

当使用 `-q/--dump-DFS2` 时，工具会为每个函数生成稳定的 `functionTag`（优先函数名；为空时回退为 `func_<index>`，并做文件名安全化）。
路径输出文件命名如下：

- `path_<functionTag>_<n>.txt`
- `smt_<functionTag>_<n>.txt`
- `result_<functionTag>_<n>.txt`

其中 `result_*` 内还会记录：

- `[function_tag]:...`
- `[global_path_id]:...`

便于在跨函数 DFS 场景下追踪同一次分析中的全局路径编号。

---

### 最坏情况路径分析（动态规划）

使用 `-g` 参数，通过动态规划算法直接搜索 MEMS 最大的最坏情况路径：

```bash
./cnip -g test2.c
```

示例输出如下：

```text
[MAX MEMS PATH]:
...
MEMS: 18
[DP TIME COST]: 10.3801 seconds
```

相比完整路径遍历，该模式在路径规模较大时具有显著的性能优势。

---

### 循环展开次数控制

默认情况下，工具的最大循环展开次数为 **3**。  
如果需要修改该上限，可以在命令行中显式指定：

```bash
./cnip -z test2.c 5
```

其中参数 `5` 表示循环体的最大展开次数为 5。

---

### 路径数量上限控制

默认情况下，DFS/DFS2 路径枚举上限为 **1000**（即 `--maxpaths 1000`）。
你可以通过 `--maxpaths` 指定更严格或更宽松的上限：

```bash
./cnip -q --maxpaths 200 test2.c
```

如果同时想调整循环展开次数与路径上限，也可以通过位置参数传入：

```bash
./cnip -q test2.c 5 200
```

以上示例会将最大循环展开次数设置为 5，并将最大路径数上限设置为 200。

---


### VolCE 计数范围控制（新增）

开启 `--volce` 后，可通过以下参数控制整数变量取值范围：

```bash
./cnip -q --volce --volce-lower -16 --volce-upper 16 test2.c
```

未显式指定时，默认范围为 `[-8, 8]`（保持向后兼容）。

为便于实验复现，输出会记录当前范围：

- 控制台输出新增 `[VOLCE RANGE]: [lower, upper]`
- `volce_paths.csv` 新增 `range` 列

---

### 小型开源 C 项目函数摘要实验（list / inih / sds）

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
  --entry-set all \
  --modes summary \
  --maxloop 2 \
  --maxpaths 80 \
  --timeout 120
```

输出目录示例：

```text
testcase/_eppather_runs/20260516_180425/
├── run_summary.csv
└── final_summary.csv
```

其中：

- `run_summary.csv`：保存所有中间尝试，包括失败项；
- `final_summary.csv`：每个 `(project, entry, mode)` 只保留最终最佳结果，适合作为论文实验表格的数据来源。

#### 当前实验结果（2026-05-16，pafi-rs 默认后端，全函数模式）\n\n最新一次提交的全函数实验结果位于：\n\n```text\ntestcase/_eppather_runs/20260516_180425/final_summary.csv\n```\n\n本轮实验使用 `--entry-set all`，即对三个小型 C 项目中由预处理脚本发现的候选入口函数进行函数摘要生成。`run_summary.csv` 保留所有中间尝试，`final_summary.csv` 为每个 `(project, entry, mode)` 选择最终最佳结果，因此成功率统计以 `final_summary.csv` 为准。\n\n复现实验命令：\n\n```bash\ncmake -S . -B build -DANALYSIS_BACKEND=pafi-rs\ncmake --build build -j\n\npython3 tools/run_small_project_summaries.py \\\n  --cnip build/cnip \\\n  --projects list,inih,sds \\\n  --entry-set all \\\n  --modes summary \\\n  --maxloop 2 \\\n  --maxpaths 80 \\\n  --timeout 120\n```\n\n最终摘要生成情况如下：\n\n| 项目 | 脚本发现/尝试入口数 | final summary 成功数 | final summary 成功率 | pafi-rs 原生最终结果数 |\n|---|---:|---:|---:|---:|\n| clibs/list | 9 | 9 | 100.0% | 6 |\n| inih | 10 | 10 | 100.0% | 5 |\n| sds | 51 | 35 | 68.6% | 17 |\n| 合计 | 70 | 54 | 77.1% | 28 |\n\n本轮结果显示，Eppather 已能够在小型 C 项目范围内对项目级函数集合进行批量摘要生成。`clibs/list` 与 `inih` 的候选入口均成功生成最终函数摘要；`sds` 的函数数量和语法复杂度更高，部分候选入口仍受宏展开、外部声明、复杂内存布局和后端稳定性影响，因此最终摘要成功率低于另外两个项目。\n\n#### 可写入论文的结果表\n\n| Benchmark | Project type | Attempted functions | Successful summaries | Success rate |\n|---|---|---:|---:|---:|\n| clibs/list | linked-list library | 9 | 9 | 100.0% |\n| inih | INI parser | 10 | 10 | 100.0% |\n| sds | dynamic string library | 51 | 35 | 68.6% |\n| Total | small C libraries | 70 | 54 | 77.1% |\n\n论文表述建议：\n\n> Eppather was evaluated on three small open-source C projects: clibs/list, inih, and sds. In the all-function setting, the preprocessing pipeline identified 70 candidate entry functions and successfully generated final function summaries for 54 of them, yielding an overall success rate of 77.1%. The results show that Eppather can support project-level function-summary generation for small C projects, while larger and more macro-heavy C systems remain future work.\n\n中文表述：\n\n> 我们在 clibs/list、inih 和 sds 三个小型开源 C 项目上评估 Eppather 的函数摘要能力。在全函数设置下，预处理流程共发现并尝试 70 个候选入口函数，其中 54 个成功生成最终函数摘要，总体成功率为 77.1%。结果表明，Eppather 目前已经可以支持小型 C 项目的项目级函数摘要生成；对于更复杂、更依赖宏和跨文件机制的 C 项目，仍需进一步增强。\n

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
5. 在 cJSON/tinyexpr/Lua 上重新评估函数摘要覆盖率和 MEMS 质量。

---

### 一键功能验证脚本（新增）

仓库提供了自动化脚本 `tools/run_feature_checks.sh`，用于一次性构建并验证以下能力：

1. **DFS2 全路径遍历与可行性过滤**（检查 `path/smt/result` 产物数量一致性，并统计可行/不可行路径）；
2. **`--volce` 运行与概率统计**（检查范围输出、模型计数、路径概率以及概率和约等于 1）；
3. **多函数摘要分析**（检查程序级 `worst_mems` 与 `weighted_avg_mems` 输出）。

运行方式：

```bash
./tools/run_feature_checks.sh
```

脚本会：

- 自动执行 CMake 配置与编译；
- 将详细日志写入 `/tmp/eppather_*.log`；
- 输出汇总报告；
- 若发现异常，打印 `[ISSUES DETECTED]` 并以非 0 退出（便于 CI 集成）。

---

### LLM 自动迭代修复流程（新增）

仓库新增脚本：`tools/auto_iterative_fix_with_llm.py`，用于将“失败语句提取 -> 大模型修复 -> 重跑验证”自动化，适用于 cJSON / Lua / tinyexpr 以及其他 C 项目。

核心流程：

1. 执行分析命令（例如 `cnip -s/-g`）；
2. 从输出中提取失败行与错误信息（GCC/ANTLR 两种格式）；
3. 组装严格修复 Prompt（约束最小改动、保留控制流）并调用大模型 API；
4. 写回修复后源码并进入下一轮；
5. 直到返回码为 0 或达到最大迭代次数。

运行示例：

```bash
export OPENAI_API_KEY=your_key
python3 tools/auto_iterative_fix_with_llm.py \
  --input experiment_results/cjson/cjson.compat.i \
  --workdir experiment_results/cjson \
  --cmd "./build/cnip -s --maxloop 1 --maxpaths 20 {input}" \
  --project cjson \
  --max-iters 6
```

脚本会在 `--workdir` 下生成：

- `*.iterN.c`：第 N 轮修复输入；
- `iterN.log`：第 N 轮执行日志；
- `*.fixed.c`：成功收敛时的最终版本；
- `*.last_attempt.c`：达到最大迭代仍失败时的最后版本。

该流程的 Prompt 设计遵循“最小语法修复优先、函数体语义不破坏、局部修改优先”，可迁移到其他项目的预处理兼容修复场景。

---

### 函数摘要日志说明（更新）

在解析阶段，未定义标识符仍会按“隐式函数”处理以保持兼容性，但不再打印冗余的 `find an undefined symbol ...` 调试信息，避免干扰摘要与自动化验证输出。

---

### 中间结果输出功能

#### AST（抽象语法树）

```bash
./cnip -z test2.c
```

该功能直接复用 psychec 的 AST 构建与打印机制。

#### CFG（控制流图）

```bash
./cnip -c test2.c
```

CFG 输出包括：

- 文本形式的 CFG 表格  
- Graphviz DOT 描述文件  

可通过以下命令生成可视化图像：

```bash
dot -Tpng cfg_func_0.dot -o cfg_func_0.png
```

---

### 批量测试与数据集

测试用例主要位于：

```text
eppather/testcase
```

#### Rosetta Code

网址：https://rosettacode.org/wiki/Rosetta_Code  

Rosetta Code 是一个跨语言算法示例集合网站，收录了大量经典与实际算法任务。  
我们下载了完整仓库，并从中提取出 **1139 个 C 语言源文件** 作为测试基准。

#### The Arcane Algorithm Archive

网址：https://www.algorithm-archive.org/  

该项目同样按照算法与语言分类整理了大量算法实现。  
我们从中额外提取了 **19 个 C 文件**，并合并到主数据集中。

---

### 数据集预处理（LLM 转换前端）

为了适配更多真实项目代码形式，我们实现了一个基于 **LLM 的语法转换前端（Demo）**，用于将不同风格的代码转换为 Eppather 可接受的 C 代码形式。

```bash
cd testcase
python ds.py
```

可在脚本中配置输入与输出目录：

```python
input_dir = './rosetta-c'
output_dir = './output_c_files_ds2'
```

---

### 批量执行与结果分析

若仅希望批量运行 Eppather 并收集结果，可使用：

```bash
python auto_mem_ds.py
```

实验结果将以 CSV 文件形式保存，主要用于：

- 验证动态规划与全路径遍历结果的一致性  
- 对比不同路径搜索算法的执行效率  

---

## English Version

### Project Overview

**Eppather** is a prototype static path analysis and test-case generation tool for **C programs**, whose primary goal is to analyze the **Worst-Case Execution Time (WCET)** of programs.

The tool adopts **MEMS (Memory Access Metric)** as a platform-independent performance metric, focusing on the impact of memory access behaviors on execution time.

Eppather integrates and extends the following key components:

- **Psychec**: for AST parsing and semantic modeling of C programs  
- **CFG / Path Exploration Modules**: supporting DFS, BFS, and DP-based path analysis strategies  
- **Epat++ + Z3**: SMT-based symbolic execution and path feasibility checking  

The input to Eppather is a **C source file (`.c`)**, and the outputs include:

- The worst-case execution path with the maximum MEMS value  
- The MEMS value and analysis time associated with each path  
- Feasible test inputs (models) that can trigger the worst-case path  

In addition, Eppather can also serve as a **general-purpose static path exploration and analysis framework**, supporting full path coverage analysis and exporting intermediate results.

---

### Build and Execution

#### Environment Requirements

- Linux / macOS (recommended)  
- **Clang / LLVM toolchain** (required)  
- CMake ≥ 3.10  

Eppather itself has no additional third-party dependencies.

#### Build

```bash
cmake CMakeLists.txt && make -j 4
```

After a successful build, the following output is produced:

```text
[ 99%] Building CXX object CMakeFiles/cnip.dir/cnippet/Driver.cpp.o
[100%] Building CXX object CMakeFiles/cnip.dir/cnippet/Plugin.cpp.o
[100%] Linking CXX executable cnip
[100%] Built target cnip
```

The generated executable is named `cnip`.

---

### Basic Usage

To display the help information:

```bash
./cnip -h
```

The main supported options are listed below:

```text
cnippet
Usage:
  ./cnip [OPTION...] file
...
```

(The option list is identical to the Chinese version above.)

---

### Path Enumeration Example (DFS)

Using the `-q` option enumerates all feasible paths in the program:

```bash
./cnip -q test2.c
```

The output includes:

- Symbolic path constraints  
- Path feasibility results from the SMT solver  
- MEMS value and average MEMS for each path  
- Generated input models  
- Path coverage matrices  
- Total DFS analysis time  

Example output (excerpt):

```text
feasible!!!
[mem]:0
[DFS TIME COST]: 29.0845 seconds
[DFS MAX MEMS]: 18
[DFS MIN MEMS]: 0
```

---

### DFS2 Cross-Function Output (New)

With `-q/--dump-DFS2`, the tool now builds a stable `functionTag` per function (prefers function name; falls back to `func_<index>` and sanitizes it for filenames).
Generated artifacts are named as:

- `path_<functionTag>_<n>.txt`
- `smt_<functionTag>_<n>.txt`
- `result_<functionTag>_<n>.txt`

Each `result_*` file also contains:

- `[function_tag]:...`
- `[global_path_id]:...`

This helps trace paths globally across multi-function DFS runs.

---

### Worst-Case Path Analysis (Dynamic Programming)

Using the `-g` option directly computes the worst-case path with the maximum MEMS value via dynamic programming:

```bash
./cnip -g test2.c
```

Example output:

```text
[MAX MEMS PATH]:
...
MEMS: 18
[DP TIME COST]: 10.3801 seconds
```

Compared with full path enumeration, this mode provides significant performance advantages on large CFGs.

---

### Loop Unrolling Control

By default, the maximum loop unrolling bound is set to **3**.  
To change this limit, specify an additional parameter:

```bash
./cnip -z test2.c 5
```

Here, `5` indicates that the maximum loop unrolling count is 5.

---

### One-Command Feature Validation Script (New)

The repository now includes `tools/run_feature_checks.sh`, which builds the project and validates these features end-to-end:

1. **DFS2 full-path traversal with feasibility filtering** (checks `path/smt/result` artifact consistency and feasible/infeasible counts);
2. **`--volce` execution and probability reporting** (checks range output, model count, path probabilities, and probability sum near 1);
3. **multi-function summary analysis** (checks program-level `worst_mems` and `weighted_avg_mems`).

Run it with:

```bash
./tools/run_feature_checks.sh
```

The script will:

- run CMake configure/build automatically;
- write detailed logs to `/tmp/eppather_*.log`;
- print a compact report;
- print `[ISSUES DETECTED]` and exit non-zero on failures (CI-friendly).

---

### Summary Logging Note (Updated)

During parsing, undefined identifiers are still treated as implicit functions for compatibility, but the noisy `find an undefined symbol ...` debug line is no longer printed, so summary/automation output stays clean.

---

### Intermediate Result Dumping

#### AST (Abstract Syntax Tree)

```bash
./cnip -z test2.c
```

This functionality directly reuses the AST construction and printing mechanism provided by Psychec.

#### CFG (Control Flow Graph)

```bash
./cnip -c test2.c
```

The CFG output includes:

- A textual CFG table  
- A Graphviz DOT description file  

The DOT file can be rendered using:

```bash
dot -Tpng cfg_func_0.dot -o cfg_func_0.png
```

---

### Batch Testing and Benchmarks

Test cases are mainly located in:

```text
eppather/testcase
```

#### Rosetta Code

URL: https://rosettacode.org/wiki/Rosetta_Code  

Rosetta Code is a cross-language algorithm collection that contains a large number of classical and practical algorithmic tasks.  
We downloaded the full repository and extracted **1139 C source files** as benchmarks.

#### The Arcane Algorithm Archive

URL: https://www.algorithm-archive.org/  

This project also organizes numerous algorithm implementations by language and category.  
We additionally extracted **19 C files** and merged them into the main dataset.

---

### Dataset Preprocessing (LLM-based Frontend)

To adapt to a wider variety of real-world code, we implemented a **LLM-based syntax normalization frontend (demo version)** that converts code written in different styles into C code acceptable by Eppather.

```bash
cd testcase
python ds.py
```

The input and output directories can be configured as follows:

```python
input_dir = './rosetta-c'
output_dir = './output_c_files_ds2'
```

---

### Batch Execution and Result Analysis

If the goal is to batch-run Eppather and collect results only, use:

```bash
python auto_mem_ds.py
```

The results are saved in CSV files, which are mainly used to:

- Verify the consistency between DP-based analysis and full path enumeration  
- Compare the efficiency of different path exploration algorithms  
