
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

默认情况下，DFS/DFS2 路径枚举 **不限制路径数量**（即 `--maxpaths 0`）。  
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
