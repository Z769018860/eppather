
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

### 论文实验：三项目基准说明（cJSON / Lua / tinyexpr）

仓库提供 `run_three_projects_experiment.py`，用于对三个真实 C 项目做统一流程实验，并将产物写入 `experiment_results/<project>/`。

#### 原始仓库、选取文件与项目特征

- **cJSON**（`DaveGamble/cJSON`）  
  选取 `testcase/cJSON/cJSON.c`。单文件内包含解析、打印、错误处理等大量分支，路径密度高，适合验证路径枚举与超时退避策略。
- **Lua**（`lua/lua`）  
  选取 `testcase/lua/lapi.c`，并显式不使用 `onelua.c`（聚合过大、CFG 信噪比较差）。该文件宏、别名类型与 API 装饰较多，适合验证预处理兼容性。
- **tinyexpr**（`codeplea/tinyexpr`）  
  选取 `testcase/tinyexpr/tinyexpr_cfgsafe.c`（兼容版输入），核心表达式求值逻辑较紧凑，适合作为摘要与 CFG 对照组。

#### 预处理与兼容策略（按脚本实际行为）

脚本对 `cJSON/lua` 先执行：

```bash
gcc -E -P -std=c11 <cpp_flags> <src> > <project>.i
```

随后生成 `<project>.compat.i`，主要做以下兼容处理：

- 注入兼容前导（如 `__attribute__`、`__extension__`、`__inline__` 的兜底定义，以及 `size_t/ptrdiff_t/uintptr_t` 基础 typedef）；
- 过滤解析噪声：`__attribute__/__declspec`、复杂 `typedef`、高噪声 `extern` 函数声明、匿名 `struct/union` 起始声明、`#pragma/#line` 等；
- 将“简单 typedef 别名”转为宏定义，降低解析负担；
- 项目特化改写：
  - **Lua**：替换 `ptrdiff_t/size_t/Instruction/StkId/Pfunc` 等别名，并去除 `LUA_API/LUAI_*` 装饰；
  - **tinyexpr**：将 `te_fun0/1/2/7` 别名改写为显式函数指针类型；
  - **cJSON**：规整 `CJSON_PUBLIC()/CJSON_CDECL`，将 `cJSON_bool` 归一为 `int`，并固定 `CJSON_NESTING_LIMIT`。

> 注：`tinyexpr_cfgsafe.c` 在脚本中按“直读源文件”处理，不额外跑 `gcc -E`，但仍走统一分析输出流程。

#### 运行预算与超时兼容

- 默认预算（`--maxloop 1`）：
  - cJSON：`--maxpaths 30`，`timeout=180s`
  - Lua/tinyexpr：`--maxpaths 120`，`timeout=180s`
- cJSON 超时后自动退避：
  - `maxpaths=15, timeout=180s`
  - `maxpaths=8, timeout=120s`
- 若仍超时，脚本会从 `cJSON.compat.i` 自动提取候选函数，并通过环境变量 `EPPATHER_ENTRY=<func>` 做入口重试。

所有退避与重试轨迹会写入输出文件（包含 `[FALLBACK RETRY]`、`[ENTRY RETRY]` 标记），便于论文复核。

#### 一次实验会产出什么（函数摘要 / CFG / MEMS）

对每个项目，脚本都会调用 `cnip` 三次：

- `-s`：生成函数摘要与统计（`summary.txt`）；
- `-g`：生成最坏路径（DP）结果（`worst_path_dp.txt`）；
- `-c`：生成 CFG 文本与 `cfg_func_*.dot` 图文件（`cfg.txt` + DOT）。

并在 `experiment_results/report.json` 汇总关键字段，例如：

- `function_count / summary_case_count / call_edge_count`
- `worst_mems / weighted_avg_mems`
- `cfg_graph_count`
- `cfg_quality_sample`（每个 DOT 的节点数/边数样本）
- 各步骤返回码 `rcodes`

#### 复现实验命令

```bash
python3 run_three_projects_experiment.py
```

运行后可重点查看：

- `experiment_results/report.json`（跨项目总览）
- `experiment_results/<project>/summary.txt`（函数摘要与 MEMS 汇总）
- `experiment_results/<project>/worst_path_dp.txt`（最坏路径）
- `experiment_results/<project>/cfg_func_*.dot`（CFG 图）

#### cJSON 编译执行与本仓库当前结果（2026-05-15）

已在仓库内完成编译与实验脚本执行：

```bash
cmake -S . -B build && cmake --build build -j4
python3 run_three_projects_experiment.py
```

从 `experiment_results/cjson/summary.txt` 可得到当前 cJSON 摘要统计：

- `function_count=113`
- `summary_case_count=679`
- `call_edge_count=139`

当前程序级 MEMS 结果为：

- `worst_mems=N/A`
- `weighted_avg_mems=N/A`
- `reason=entry function not found`

说明：cJSON 源文件本身不提供 `main` 入口，因此在默认入口策略下只能稳定得到函数级摘要；如需程序级 MEMS，请在实验时显式设置 `EPPATHER_ENTRY`（并结合兼容过滤进一步收敛解析噪声）。

#### 降噪与兼容增强（run_three_projects_experiment.py）

为降低 cJSON 预处理噪声并提升实验效率，脚本新增/调整了以下策略：

- cJSON 预算下调为 `--maxpaths 18`、`timeout 120s`（保持 `--maxloop 1`），减少长尾耗时；
- 兼容过滤新增：
  - 去除 `__restrict/restrict` 关键字；
  - 在 `enum` 块内过滤注释与预处理残留行；
  - 对 cJSON 进一步过滤 `_IS* = ...` 以及高噪声 `extern void *memcpy(...)` 行；
- cJSON 运行 `-s/-g/-c` 时默认注入 `EPPATHER_ENTRY=cJSON_Parse`，减少无效入口带来的失败重试；
- 汇总报告新增 `_aggregate.summary_success_rate`（函数摘要成功率）与 `summary_success`（单项目布尔）。

此外，在 Eppather 预处理前端（`tools/GnuCompilerFacade.cpp`）中新增了常见 GNU/libc 装饰宏默认兼容定义（如 `__THROW/__wur/__nonnull/__extension__/__restrict`），用于降低真实项目源码进入解析器前的语法噪声。

#### 当前结果表（2026-05-16）

| 项目 | 预计函数摘要数 | 当前函数摘要数（report.function_count） | CFG数量（report.cfg_graph_count） | CFG是否已生成 |
|---|---:|---:|---:|---|
| cjson | 113 | 113 | 113 | ✅ |
| lua | 96 | 96 | 96 | ✅ |
| tinyexpr | 29 | 29 | 29 | ✅ |
| 合计 | 238 | 238 | 238 | ✅ |

| 汇总指标 | 数值 |
|---|---:|
| 总项目数 | 3 |
| 函数摘要成功数 | 0 |
| 函数摘要成功率 | 0.0 |

#### Lua / cJSON 的进一步处理与 DP 策略说明

- 当前三项目实验脚本已统一采用 `-g`（DP 最坏路径）而非 DFS 路径枚举来输出 MEMS 相关结果；
- 但 `lua/cjson` 在当前版本仍存在“可出 CFG、但 `-s/-g` 异常退出（返回码 `-11`）”的问题，说明瓶颈已从路径搜索策略转为**前端解析/语义建模噪声**；
- 因此后续优化重点应放在更强的预处理约简（尤其是 libc 相关声明、宏展开残留、复杂别名链）而非进一步削减 DFS/DP 参数。

#### tinyexpr 函数摘要正确性分析：是否需要更多预处理？

从 `experiment_results/tinyexpr/summary.txt` 可见：

- 函数摘要块已正确生成（`fac/ncr/npr/main` 共 4 个函数）；
- 但每个函数 `#cases=0`，`DIRECT worst_mems=-1`，程序级 `worst_mems=N/A`；
- 输出同时出现 `unsupported type for sort: double`，说明当前 SMT/MEMS 通路对 `double` 相关路径支持不足，导致“摘要框架可运行，但无可用路径案例”。

补充核查（`testcase/tinyexpr/tinyexpr.c`）显示 tinyexpr 核心文件函数数明显 **不止 4 个**，因此此前只得到 4 个函数摘要时，确实说明大量函数未完整进入摘要阶段。

最新实验改为直接处理 `tinyexpr.c`，并在兼容过滤中启用“浮点近似为整数”的策略（`double/float -> long`，`NAN/INFINITY` 常量归一化），以绕过当前求解器对 `double sort` 的限制；该策略显著提升了 CFG 覆盖（可见 `cfg_graph_count` 上升），但 `-s/-g` 仍可能受更深层语义问题影响。

结论：tinyexpr **仍需要进一步语义兼容**，但“浮点近似转整数”是必要步骤之一，且已纳入当前实验管线。

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
