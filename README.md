# Eppather

[🇨🇳 中文](#eppather-说明文档) | [🇬🇧 English](#eppather-documentation)

---

# Eppather 说明文档

## 简介

**Eppather** 是一个面向 C 语言程序的静态最坏路径分析与测试生成原型工具，主要用于 **WCET（Worst-Case Execution Time）分析**。  
工具以 **MEMS（Memory Accesses）** 作为核心度量指标，通过静态分析程序的控制流与路径约束，自动寻找 **MEMS 最大的最坏情况执行路径**，并生成能够触达该路径的测试输入。

Eppather 结合了以下关键组件：

- **Psychec**：用于 C 程序的 AST 构建与语法分析  
- **CFG 构建与路径探索模块**：支持 DFS / BFS / DP 等多种路径搜索策略  
- **epat++ + Z3**：进行路径可行性判定与符号约束求解  

### 输入与输出

- **输入**：C 语言源代码（`.c` 文件）  
- **输出**：
  - MEMS 最大的最坏情况路径
  - 路径对应的 MEMS 值与分析耗时
  - 能够到达该路径的测试用例（模型）

除 WCET 场景外，Eppather 也可作为一个 **通用的静态路径遍历与符号执行分析框架** 使用。

---

## 编译与运行

### 环境依赖

- 操作系统：Linux / macOS（推荐）
- 编译环境：`clang`（必须）
- 构建系统：`cmake`

### 编译

```bash
cmake CMakeLists.txt
make -j 4
```

成功编译后将生成可执行文件 `cnip`：

```text
[100%] Linking CXX executable cnip
[100%] Built target cnip
```

---

## 基本用法

### 查看帮助

```bash
./cnip -h
```

### 常用参数说明

- `-z`：输出 AST（来自 psychec）
- `-c`：输出 CFG（文本 + DOT）
- `-f`：DFS 路径遍历（icov）
- `-q`：DFS 路径遍历（bcov，全路径）
- `-b`：BFS 路径遍历
- `-g`：基于动态规划（DP）的最坏 MEMS 路径搜索
- `--c-std`：指定 C 语言标准（c89/c99/c11/...）
- `--cpp-I / --cpp-D`：预处理器参数
- `-o`：输出文件名

---

## 使用示例

### 1. DFS 全路径遍历

```bash
./cnip -q test2.c
```

输出包括：

- 路径条件（符号形式）
- 可行性判断（Z3）
- MEMS 值统计
- DFS 总耗时
- 路径覆盖矩阵

### 2. DP 最坏路径搜索（推荐）

```bash
./cnip -g test2.c
```

输出示例：

- MEMS 最大的路径（语句级）
- 对应 MEMS 值
- DP 算法耗时

该模式在大规模路径空间下显著优于完全遍历。

---

## 循环展开控制

默认情况下，Eppather 的 **最大循环展开次数为 3**。  
可通过在命令末尾增加参数进行修改：

```bash
./cnip -z test2.c 5
```

表示最大循环展开次数为 5。

该机制用于在 **可分析性与精度之间进行权衡**。

---

## 中间结果输出

### AST 输出

```bash
./cnip -z test2.c
```

### CFG 输出

```bash
./cnip -c test2.c
```

- 生成 CFG 表格（文本）
- 生成 DOT 文件（`cfg_func_*.dot`）
- 可使用 Graphviz 渲染：

```bash
dot -Tpng cfg_func_0.dot -o cfg_func_0.png
```

---

## 批量测试与 Benchmark

### 测试目录

```text
eppather/testcase/
```

### 使用的 Benchmark

#### 1. Rosetta Code

- 官网：https://rosettacode.org/wiki/Rosetta_Code
- 特点：
  - 大规模、多算法、多语言
  - 持续更新
  - 类似 LeetCode 的公开算法与答案集合

本项目提取了 **1139 个 C 文件** 用于分析。

#### 2. The Arcane Algorithm Archive

- 官网：https://www.algorithm-archive.org/
- 以“算法百科全书”形式组织
- 补充获得 19 个 C 实现

---

## 数据集预处理（LLM 转换前端）

为支持更加多样的输入形式，Eppather 提供了一个 **基于 LLM 的代码转换前端（Demo）**，用于：

- 规范化 C 代码结构
- 消除不被分析支持的语法差异
- 扩展工具的适用范围

### 使用方法

```bash
cd testcase
python ds.py
```

可在脚本中修改：

```python
input_dir = './rosetta-c'
output_dir = './output_c_files_ds2'
```

---

## 批量执行分析

```bash
python auto_mem_ds.py
```

输出：

- 每个程序的 DP 最坏 MEMS 路径
- DFS / DP 结果一致性对比
- 执行时间统计
- CSV 汇总结果

该实验主要用于验证：

- DP 搜索结果的正确性
- 相比完全遍历的性能优势

---

## English Version

# Eppather Documentation

## Overview

**Eppather** is a static analysis and test generation prototype for C programs, targeting **Worst-Case Execution Time (WCET)** analysis using the **MEMS (Memory Accesses)** metric.

It statically explores program paths, identifies the path with the **maximum MEMS**, and generates test inputs that can trigger this worst-case behavior.

### Key Components

- Psychec-based AST construction
- CFG-based path exploration (DFS / BFS / DP)
- Symbolic execution with epat++ and Z3

### Input / Output

- **Input**: C source code (`.c`)
- **Output**:
  - Worst-case execution path
  - MEMS value and analysis time
  - Feasible test inputs

---

## Build

```bash
cmake CMakeLists.txt
make -j 4
```

---

## Usage

### Show help

```bash
./cnip -h
```

### Find worst-case MEMS path (DP)

```bash
./cnip -g test.c
```

### Full path exploration (DFS)

```bash
./cnip -q test.c
```

---

## Loop Unrolling

Default max unrolling depth: **3**

```bash
./cnip -z test.c 5
```

---

## Batch Evaluation

Benchmarks used:

- **Rosetta Code** (1139 C programs)
- **Arcane Algorithm Archive**

LLM-based preprocessing is provided to normalize inputs.

---

## License & Status

- Research prototype
- For academic and experimental use
