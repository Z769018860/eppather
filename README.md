````markdown
# Eppather

[中文](#中文说明) | [English](#english)

---

## 中文说明

### 一、工具简介

**Eppather** 是一个面向 C 语言程序的**静态路径分析与测试生成原型工具**，用于分析程序的**最坏情况执行路径（Worst-Case Path）**，并以 **MEMS（Memory Accesses）** 作为平台无关的性能度量指标，服务于 **WCET（Worst-Case Execution Time）分析**。

Eppather 结合了以下核心组件：

- **Psychec**：用于 C 程序的 AST 构建与语义解析  
- **路径探索模块**：支持 DFS / BFS / 动态规划（DP）等多种路径搜索策略  
- **epat++ + Z3**：用于路径可达性判定与符号约束求解  

**输入**：C 语言源代码（`.c` 文件）  

**输出**：
- MEMS 最大的最坏情况执行路径  
- 路径对应的 MEMS 数值与分析时间  
- 能够触发该路径的测试输入（SMT 模型）  

此外，Eppather 也支持：
- 全路径遍历  
- AST / CFG 等中间结果输出  
- 基于 SMT 的路径可行性分析  

---

### 二、编译与运行

#### 1. 编译环境

- 无额外特殊依赖  
- 需要 **Clang** 相关环境（用于解析与分析）  

#### 2. 编译方式

```bash
cmake CMakeLists.txt && make -j 4
````

成功编译后将生成可执行文件 `cnip`：

```text
[100%] Linking CXX executable cnip
[100%] Built target cnip
```

---

### 三、命令行参数说明

查看帮助信息：

```bash
./cnip -h
```

主要参数如下：

```text
Usage:
  ./cnip [OPTION...] file

-l, --lang <C>                指定语言（默认：C）
-z, --dump-AST                输出 AST
-c, --dump-CFG                输出 CFG
-f, --dump-DFS                DFS 遍历路径（icov）
-q, --dump-DFS2               DFS 遍历路径（bcov）
-b, --dump-BFS                BFS 遍历路径
-g, --dump-MaxMemDP           使用动态规划搜索 MEMS 最大路径
-d, --debug                   调试模式
-p, --plugin arg              加载插件
-w, --WIP                     启用实验性功能
-h, --help                    帮助信息
-o, --output arg              输出文件（默认：a.cstr）
```

---

### 四、使用示例

#### 1. 全路径遍历（DFS）

```bash
./cnip -q test2.c
```

输出包括：

* 路径条件
* 可行性判定（SMT）
* MEMS 数值
* 路径覆盖矩阵
* 执行时间

示例（截取）：

```text
feasible!!!
[mem]:0
[DFS TIME COST]: 29.0845 seconds
[DFS MAX MEMS]: 18
[DFS MIN MEMS]: 0
```

---

#### 2. 最坏情况路径（动态规划）

```bash
./cnip -g test2.c
```

示例输出：

```text
[MAX MEMS PATH]:
...
MEMS: 18
[DP TIME COST]: 10.3801 seconds
```

该模式用于**高效计算 MEMS 最大的最坏情况执行路径**。

---

#### 3. 循环展开次数说明

若未显式指定，默认循环最大展开次数为 **3**。

可通过如下方式指定：

```bash
./cnip -z test2.c 5
```

表示循环最多展开 **5 次**。

---

### 五、中间结果输出

#### 1. AST 输出

```bash
./cnip -z test2.c
```

该功能完全复用 **Psychec** 的 AST 构建能力。

---

#### 2. CFG 输出

```bash
./cnip -c test2.c
```

将输出：

* CFG 表格形式
* 对应的 DOT 文件

并提示：

```text
Render with: dot -Tpng cfg_func_0.dot -o cfg_func_0.png
```

---

### 六、批量测试与数据集

测试用例位于：

```text
eppather/testcase
```

#### 1. Rosetta Code

* 官网：[https://rosettacode.org/wiki/Rosetta_Code](https://rosettacode.org/wiki/Rosetta_Code)
* 提取 C 语言程序：**1139 个 `.c` 文件**
* 覆盖大量算法与编程模式

---

#### 2. The Arcane Algorithm Archive

* 官网：[https://www.algorithm-archive.org/](https://www.algorithm-archive.org/)
* 补充提取：**19 个 C 程序**

---

### 七、数据集预处理（LLM 前端）

为了支持更多样化的输入形式，Eppather 提供了一个**基于 LLM 的语法转换前端（Demo）**，用于将非标准 C 代码转换为 Eppather 可接受的形式。

执行方式：

```bash
cd testcase
python ds.py
```

可配置输入输出目录：

```python
input_dir = './rosetta-c'
output_dir = './output_c_files_ds2'
```

---

### 八、批量执行

若仅需批量运行分析：

```bash
python auto_mem_ds.py
```

输出结果将写入 CSV 文件，用于：

* 对比 DP 与完全遍历结果的一致性
* 分析不同路径搜索策略的执行效率

---

## English

### Overview

**Eppather** is a prototype static analysis and test generation tool for **C programs**, aiming to identify **worst-case execution paths** using **MEMS (Memory Accesses)** as a platform-independent cost metric, targeting **WCET (Worst-Case Execution Time) analysis**.

Eppather integrates:

* **Psychec** for AST construction and semantic analysis
* Multiple path exploration strategies (DFS / BFS / DP)
* **epat++ + Z3** for symbolic execution and path feasibility checking

**Input**: C source files (`.c`)

**Output**:

* Worst-case execution path with maximum MEMS
* Corresponding MEMS value and analysis time
* Feasible test inputs (SMT models)

---

### Build & Run

```bash
cmake CMakeLists.txt && make -j 4
```

Run:

```bash
./cnip -h
```

---

### Example: Worst-Case Path via DP

```bash
./cnip -g test2.c
```

Output:

```text
MEMS: 18
[DP TIME COST]: 10.38 seconds
```

---

### Benchmarks

* **Rosetta Code** (1139 C programs)
* **The Arcane Algorithm Archive**

These benchmarks are used to evaluate:

* Path optimality
* Search efficiency
* Consistency between DP-based and exhaustive traversal

---

### Project Status

This project is a **research prototype** under active development.

```
```
