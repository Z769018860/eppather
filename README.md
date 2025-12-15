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
- 需要 **Clang** 相关环境  

#### 2. 编译方式

```bash
cmake CMakeLists.txt && make -j 4
```

---

## English

### Overview

**Eppather** is a prototype static analysis and test generation tool for **C programs**, aiming to identify **worst-case execution paths** using **MEMS (Memory Accesses)** as a platform-independent cost metric, targeting **WCET (Worst-Case Execution Time) analysis**.
