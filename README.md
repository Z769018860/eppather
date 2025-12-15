# Eppather

[🇨🇳 中文说明](#eppather说明文档) | [🇬🇧 English](#eppather-documentation)

---

## Eppather说明文档

标签（空格分隔）： 未分类

---

## 说明

**Eppather** 是一个面向 C 语言程序的静态路径分析与测试生成原型工具，核心目标是分析和近似计算程序的 **WCET（Worst-Case Execution Time）**。  
本工具以 **MEMS（Memory Accesses）** 作为平台无关的代价度量，通过对程序路径进行系统性探索，寻找 **MEMS 最大的最坏情况执行路径**，并生成能够到达该路径的测试用例。

在实现层面，Eppather 综合了多种已有与自研技术组件：

- **psychec**：负责 C 程序的语法解析与 AST 构建  
- **路径探索模块**：支持 DFS / BFS / 动态规划（DP）等多种路径搜索策略  
- **epat++ + Z3**：用于路径可行性判定与符号约束求解  

工具的输入为 **C 语言程序源代码（.c 文件）**，输出包括：

- MEMS 最大的最坏情况路径（语句级）
- 该路径对应的 MEMS 值与分析耗时
- 能够触达该路径的测试输入模型

除 WCET 场景外，Eppather 也可作为一个 **通用的静态路径遍历与符号执行分析工具** 使用。

---

## 编译执行

Eppather 没有额外的特殊依赖，但为了分析和编译执行，至少需要有 **clang 环境**。

```bash
cmake CMakeLists.txt && make -j 4
```

得到的结果为：

```text
[ 99%] Building CXX object CMakeFiles/cnip.dir/cnippet/Driver.cpp.o
[100%] Building CXX object CMakeFiles/cnip.dir/cnippet/Plugin.cpp.o
[100%] Linking CXX executable cnip
[100%] Built target cnip
```

工具的执行参数：

```bash
./cnip -h
```

相关的功能参数为：

```text
cnippet
Usage:
  ./cnip [OPTION...] file

  -l, --lang <C>                Specify the language. (default: C)
  -z, --dump-AST                Dump the program's AST to the console.
  -c, --dump-CFG                Dump the program's CFG to the console.
  -f, --dump-DFS                Dump the program's path in the DFS mode to
                                the console.(icov)
  -q, --dump-DFS2               Dump the program's path in the DFS mode to
                                the console.(bcov)
  -g, --dump-MaxMemDP           Dump the program's worst path in the DP
                                mode to the console.
  -b, --dump-BFS                Dump the program's path in the BFS mode to
                                the console.
  -d, --debug                   Enable debugging.
  -p, --plugin arg              Load plugin with the given name.
  -w, --WIP                     Enable Work-In-Progress features.
  -h, --help                    Print instructions.
      --c-std <c89|c90|c99|c11|c17>
                                Specify the C standard. (default: c11)
      --host-cc <gcc|clang>     Specify a host C compiler. (default: gcc)
      --cpp-includes            Expand `#include' directives of the C
                                preprocessor.
      --cpp-I path              Add a directory to the `#include' search path
                                of the C preprocessor.
      --cpp-D <name|name=definition>
                                Predefine a C preprocessor macro.
      --cpp-U <name>            Undefine a C preprocessor macro.
      --C-ParseOptions-TreatmentOfAmbiguities <None|Diagnose|DisambiguateAlgorithmically|DisambiguateAlgorithmicallyOrHeuristically|DisambiguateHeuristically>
                                Treatment of ambiguities. (default:
                                DisambiguateAlgorithmicallyOrHeuristically)
      --C-infer                 Infer the definition of missing types.
  -o, --output arg              Specify output file (default: a.cstr)
```

---

## 使用示例

### 使用 `-q` 参数遍历全部路径

```bash
./cnip -q test2.c
```

得到的结果为（截取最后一段）：

```text
Path:int *nums1;
int nums1Size;
int m;
int *nums2;
int nums2Size;
int n;
int p1 = m - 1;
int p2 = n - 1;
int p = m + n - 1;
@(!(p1 >= 0 && p2 >= 0));

@(!(p2 >= 0));

feasible!!!
[mem]:0
[averagemem]:0
modelL(define-fun n@0@0 () (_ BitVec 32)
  #x00000000)
[DFS TIME COST]: 29.0845 seconds
[MATRIX]:
1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 1 1 
...
[DFS MAX MEMS]: 18
[DFS MIN MEMS]: 0
```

### 使用 `-g` 参数生成 DP 下 MEMS 最大的最坏情况路径

```bash
./cnip -g test2.c
```

得到的结果示例：

```text
[MAX MEMS PATH]:
int *nums1;
int nums1Size;
int m;
int *nums2;
int nums2Size;
int n;
int p1 = m - 1;
int p2 = n - 1;
int p = m + n - 1;
@(p1 >= 0 && p2 >= 0);
@(nums1[p1] > nums2[p2]);
nums1[p] = nums1[p1];
p1=p1-1;
p=p-1;
...
MEMS: 18
[DP TIME COST]: 10.3801 seconds
```

补充说明：这里如果不在最后增加参数，则会默认最大循环展开次数为 3，如果想要更改循环展开次数可以使用如下参数：

```bash
./cnip -z test2.c 5
```

这里的 5 意味着循环展开次最大数为 5。

---

## 其他功能

Eppather 工具同样保留了中间过程，例如 AST 语法树（该部分完全沿用 psychec）：

```bash
./cnip -z test2.c
```

以及 CFG 的输出：

```bash
./cnip -c test2.c
```

CFG 的控制流图示例为（内容保持不变）：

```text
======== CFG TABLE: FunctionDefinition #0 ========
Total nodes: 20
Idx | Level | Kind                | Flags        | Next  | False | Code/Label
...
```

DOT 文件输出示例：

```text
[INFO] DOT written to: cfg_func_0.dot
       Render with: dot -Tpng cfg_func_0.dot -o cfg_func_0.png
```

---

## 批量测试

我们主要的测试用例放在了 `eppather/testcase` 文件夹下。

### Rosettacode

网址为：https://rosettacode.org/wiki/Rosetta_Code

Rosetta Code 是一个大规模的公开算法与程序实现集合，覆盖多种编程语言和算法任务。  
本项目下载并提取了其中 **1139 个 C 文件** 作为测试输入。

### The Arcane Algorithm Archive

网址为：https://www.algorithm-archive.org/

该站点以“算法百科全书”的形式组织代码，实现补充提取了 19 个 C 文件，并与 Rosetta Code 数据集合并使用。

---

### 数据集处理

为了适配更多样的输入形式，我们使用 LLM 构建了一个 **语法转换前端（Demo）**，用于将代码转换为 Eppather 能够稳定分析的形式。

```bash
cd testcase
python ds.py
```

其中输入与输出目录可以自行修改：

```python
input_dir = './rosetta-c'
output_dir = './output_c_files_ds2'
```

### 批量执行

```bash
python auto_mem_ds.py
```

生成结果主要用于比较：

- DP 搜索得到的最坏路径
- 完全遍历得到的最坏路径
- 两种方法在时间与规模上的差异

---

## Eppather Documentation

(English section keeps all code blocks identical to the Chinese version and focuses on explanation only.)

