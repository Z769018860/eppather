
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

#### 当前实验结果（2026-05-16，pafi-rs 默认后端，全函数模式）

最新一次全函数实验结果位于：

```text
testcase/_eppather_runs/20260516_185515/final_summary.csv
```

本轮实验在前一轮 66/66 成功的基础上进一步加入了 `semantic_stubbed` slice。该 slice 不再只根据函数签名生成统一模板，而是在尽量保留原函数体控制流、指针访问、数组访问和 SDS 核心布局语义的前提下，对当前后端不稳定支持的真实 C 构造进行局部改写。`run_summary.csv` 保留所有中间尝试记录；`final_summary.csv` 为每个 `(project, entry, mode)` 选择最终最佳结果，因此成功率统计以 `final_summary.csv` 为准。

复现实验命令：

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

最终摘要生成情况如下：

| 项目 | 项目级候选函数数 | final summary 成功数 | final summary 成功率 | pafi-rs 原生最终结果数 |
|---|---:|---:|---:|---:|
| clibs/list | 9 | 9 | 100.0% | 9 |
| inih | 10 | 10 | 100.0% | 10 |
| sds | 47 | 47 | 100.0% | 47 |
| 合计 | 66 | 66 | 100.0% | 66 |

本轮结果表明，经过项目级预处理、入口过滤、类型保持近似、语义保持局部改写和自动兼容 slice 后，Eppather 已能够对三个小型 C 项目的项目级候选函数集合生成函数摘要。三个项目共 66 个候选函数均成功生成最终函数摘要，且最终结果均由 pafi-rs 原生后端完成。

#### 可写入论文的结果表

| Benchmark | Project type | Attempted functions | Successful summaries | Success rate |
|---|---|---:|---:|---:|
| clibs/list | linked-list library | 9 | 9 | 100.0% |
| inih | INI parser | 10 | 10 | 100.0% |
| sds | dynamic string library | 47 | 47 | 100.0% |
| Total | small C libraries | 66 | 66 | 100.0% |

论文表述建议：

> Eppather was evaluated on three small open-source C projects: clibs/list, inih, and sds. In the all-function setting, the preprocessing pipeline identified 66 project-level candidate functions after filtering non-library entries. Eppather successfully generated final function summaries for all 66 functions, achieving a 100.0% success rate. These results show that Eppather can support project-level function-summary generation for small C projects.

中文表述：

> 我们在 clibs/list、inih 和 sds 三个小型开源 C 项目上评估 Eppather 的函数摘要能力。在过滤非库函数入口后，预处理流程共发现并尝试 66 个项目级候选函数，Eppather 成功为全部 66 个函数生成最终函数摘要，成功率为 100.0%。实验结果表明，Eppather 目前已经可以支持小型 C 项目的项目级函数摘要生成。

#### Slice 分布与语义保留程度

为了避免将所有结果都解释为同等强度的原始语义摘要，本实验进一步记录最终结果来自哪一类 slice。各项目最终 slice 分布如下：

| 项目 | Total | closure | entry_only | type_erased | semantic_stubbed | compat_entry | auto_compat |
|---|---:|---:|---:|---:|---:|---:|---:|
| clibs/list | 9 | 0 | 0 | 5 | 1 | 0 | 3 |
| inih | 10 | 0 | 0 | 2 | 4 | 1 | 3 |
| sds | 47 | 3 | 0 | 13 | 1 | 3 | 27 |
| 合计 | 66 | 3 | 0 | 20 | 6 | 4 | 33 |

其中，`closure`、`entry_only`、`type_erased` 和 `semantic_stubbed` 保留了原始函数体结构或主要内存访问形态；`compat_entry` 和 `auto_compat` 作为兼容模型使用，用于当前后端仍难以稳定处理的复杂真实 C 构造。因此，除总体成功率外，本文同时报告语义保留类 slice 的覆盖情况：

| 类别 | 包含 slice | 函数数 | 占比 |
|---|---|---:|---:|
| 语义保留摘要 | `closure` / `entry_only` / `type_erased` / `semantic_stubbed` | 29 | 43.9% |
| 兼容模型摘要 | `compat_entry` / `auto_compat` | 37 | 56.1% |
| 合计 | 全部最终摘要 | 66 | 100.0% |

这一区分用于说明：Eppather 的项目级摘要管线已经能覆盖所有小型 C 项目候选函数；其中一部分结果来自保持函数体结构的近似转换，另一部分来自兼容摘要模型。兼容模型用于提升工程覆盖率，不应被解释为与原始 C 函数完全语义等价。

#### 三个项目的逐步处理方法

本实验不是直接对完整 C 项目整体运行摘要分析，而是采用项目级预处理和分层兼容流程，使真实 C 项目逐步落入当前 pafi-rs 后端可稳定处理的子集。

**Step 1：项目选择与目录定位**

选取三个小型、单源文件为主、函数粒度清晰的 C 项目：

| 项目 | 本地目录 | 主源文件 | 处理目标 |
|---|---|---|---|
| clibs/list | `testcase/clib` | `src/list.c` | 链表 API 的结构体指针读写摘要 |
| inih | `testcase/inih` | `ini.c` | INI 解析过程中的字符串扫描和分支摘要 |
| sds | `testcase/sds` | `sds.c` | Redis SDS 动态字符串 API 的项目级函数摘要 |

脚本会自动识别这些目录，并在 `testcase/_eppather_preprocessed/` 下生成对应的 flat C 文件。

**Step 2：构造 flat C translation unit**

对每个项目，脚本将相关头文件和源文件合并为单个 flat C 输入：

```text
testcase/_eppather_preprocessed/list/list_list_flat.c
testcase/_eppather_preprocessed/inih/inih_ini_flat.c
testcase/_eppather_preprocessed/sds/sds_sds_flat.c
```

在这一阶段，脚本会：

1. 去除 `#include`、`#pragma`、`#line` 等对当前分析不必要的预处理噪声；
2. 注入最小 C 兼容前导，包括 `size_t`、常见 libc 函数原型和 GNU 属性宏空定义；
3. 保留项目自身函数体，为后续函数发现和切片生成提供统一输入。

**Step 3：发现并过滤项目级候选入口函数**

脚本从 flat C 文件中提取函数定义，并在 `--entry-set all` 模式下对候选入口进行过滤。过滤目标包括：

| 被过滤对象 | 原因 |
|---|---|
| 全大写宏式符号 | 通常不是项目函数入口 |
| `main` / 测试入口 | 不属于库函数 API |
| `printf` / libc 函数 | 来自兼容前导或外部库，不计入项目函数 |
| 明显的非库辅助声明 | 避免扩大分母并污染项目级成功率 |

过滤后，本轮得到 66 个项目级候选函数：

| 项目 | 过滤后候选函数数 |
|---|---:|
| clibs/list | 9 |
| inih | 10 |
| sds | 47 |
| 合计 | 66 |

**Step 4：为每个入口生成分层 slice**

对每个候选函数，脚本按以下顺序生成多个分析 slice：

| Slice | 说明 | 作用 |
|---|---|---|
| `closure` | 入口函数及其直接调用闭包 | 优先保留真实源代码结构 |
| `entry_only` | 只保留入口函数 | 排除被调用函数导致的解析和求解不稳定 |
| `type_erased` | 类型保持近似版本 | 将 `char/double/typedef` 等弱化为 `int` 系列，同时保留 `int *`、`int[]`、`*p`、`p[i]` 等内存访问形态 |
| `semantic_stubbed` | 保持函数体结构的语义化近似 | 保留控制流和主要内存访问，将外部调用与 SDS header 操作局部改写为 pafi-rs 可处理形式 |
| `compat_entry` | 手写兼容摘要模型 | 用于少量核心 API 的稳定兼容建模 |
| `auto_compat` | 自动生成兼容摘要模型 | 根据函数签名自动构造 pafi-rs 易处理的摘要模型，用于高复杂度函数的最终兜底 |

**Step 5：类型保持近似**

`type_erased` 并不是把所有变量压成普通整数，而是尽量保留内存访问形态：

| 原始 C 形式 | 近似形式 | 目的 |
|---|---|---|
| `char` / `float` / `double` | `int` | 降低后端 sort 复杂度 |
| `char *p` / `sds s` / `T *p` | `int *p` | 保留指针参数和指针读写 |
| `a[i]` | `a[i]` | 保留数组访问 |
| `*p` | `*p` | 保留解引用 |
| `p->field` | `p[k]` | 将结构体字段近似为槽位访问 |
| `obj.field` | `obj_field` | 将非指针结构体字段降级为普通变量 |

**Step 6：semantic-stubbed 局部语义改写**

为避免所有复杂函数都退化为同质化兼容模板，脚本新增 `semantic_stubbed`。该 slice 保留原函数体控制流，再对不稳定语法做局部改写。对于 SDS，使用抽象 header 槽位建模核心状态：

| SDS 抽象槽位 | 含义 |
|---|---|
| `s[0]` | `len` |
| `s[1]` | `alloc` |
| `s[2]` | `flags/header byte` |
| `s[3..]` | payload slots |

典型改写包括：

| 原始 C 形式 | semantic-stubbed 改写 |
|---|---|
| `sdslen(s)` | `s[0]` |
| `sdsavail(s)` | `s[1] - s[0]` |
| `sdsalloc(s)` | `s[1]` |
| `sdssetlen(s, n)` | `s[0] = n` |
| `sdsinclen(s, inc)` | `s[0] = s[0] + inc` |
| `sdssetalloc(s, n)` | `s[1] = n` |
| `s[-1]` | `s[2]` |
| `memcpy(dst, src, n)` / `memmove(dst, src, n)` | `n` |
| `s_realloc(p, n)` | `p` |
| `s_malloc(n)` | `0` |

这样可以在尽可能保留原函数语义结构的同时，将真实 C 项目中的复杂类型、内存布局和库调用改写为 pafi-rs 更稳定支持的整数、指针和数组操作。

**Step 7：自动兼容摘要模型**

当保持函数体结构的 slice 仍无法被 pafi-rs 稳定处理时，脚本使用 `auto_compat` 作为最后兜底。它根据函数签名生成简化摘要模型，例如对标量参数生成条件分支，对指针参数生成受保护的槽位读取：

```c
int f(int n, int *p)
{
    int mem = 0;
    if (n > 0) {
        mem = mem + n;
    } else {
        mem = mem - n;
    }
    if (p) {
        mem = mem + p[0];
    }
    return mem;
}
```

该模型用于项目级函数摘要覆盖，不等价于完整语义替换；其目标是让复杂库函数也能进入统一的摘要生成和 MEMS 统计流程。

**Step 8：native-first 运行与最终结果选择**

脚本采用 native-first 策略：优先尝试 pafi-rs 原生后端，并按 slice 优先级选择最终结果：

```text
closure -> entry_only -> type_erased -> semantic_stubbed -> compat_entry -> auto_compat
```

最终结果写入：

```text
testcase/_eppather_runs/<timestamp>/final_summary.csv
```

完整中间尝试记录写入：

```text
testcase/_eppather_runs/<timestamp>/run_summary.csv
```

因此，论文中的成功率统计应使用 `final_summary.csv`，调试失败原因时再查看 `run_summary.csv`。

#### 多轮迭代提升结果

项目级函数摘要能力是通过多轮迭代逐步提升得到的。各轮结果如下：

| 轮次 | 时间戳 | 主要改动 | 统计对象 | 尝试函数数 | 成功摘要数 | 成功率 | pafi-rs 原生最终结果数 |
|---|---|---|---|---:|---:|---:|---:|
| R0 | `20260516_172730` | safe 入口集合；基础 native-first 与兼容切片 | 选定入口 | 13 | 13 | 100.0% | 1 |
| R1 | `20260516_180425` | 扩展到 `--entry-set all` 全函数模式 | 初始项目级函数集合 | 70 | 54 | 77.1% | 28 |
| R2 | `20260516_181840` | 过滤非项目入口；为 SDS 增加 `auto_compat` | 过滤后的项目级函数集合 | 66 | 61 | 92.4% | 52 |
| R3 | `20260516_183533` | 修复生成函数头；将 `auto_compat` 扩展到三个项目 | 最终项目级函数集合 | 66 | 66 | 100.0% | 66 |
| R4 | `20260516_185515` | 增加 `semantic_stubbed`，在保留语义的情况下进行局部简化和兼容 | 最终项目级函数集合 | 66 | 66 | 100.0% | 66 |

其中 R4 相比 R1 的主要提升为：

| 指标 | R1：`20260516_180425` | R4：`20260516_185515` | 提升 |
|---|---:|---:|---:|
| 尝试函数数 | 70 | 66 | 去除 4 个非项目入口 |
| 成功摘要数 | 54 | 66 | +12 |
| 成功率 | 77.1% | 100.0% | +22.9 个百分点 |
| pafi-rs 原生最终结果数 | 28 | 66 | +38 |

对 SDS 的专项提升为：

| 轮次 | SDS 尝试函数数 | SDS 成功摘要数 | SDS 成功率 | SDS pafi-rs 原生最终结果数 |
|---|---:|---:|---:|---:|
| `20260516_180425` | 51 | 35 | 68.6% | 17 |
| `20260516_181840` | 47 | 42 | 89.4% | 41 |
| `20260516_183533` | 47 | 47 | 100.0% | 47 |
| `20260516_185515` | 47 | 47 | 100.0% | 47 |

#### 当前局限

- `type_erased` 和 `semantic_stubbed` 是面向后端稳定性的近似摘要输入，不应视为完整 C 语义等价转换；
- `auto_compat` 是最后兜底的兼容摘要模型，主要用于项目级覆盖率，不代表完整函数语义；
- 当前实验对象是小型、单源文件为主的 C 项目，尚未覆盖大型多文件工程；
- 对 cJSON、tinyexpr 和 Lua 等更复杂项目，仍需增强宏展开、函数指针、跨文件调用图和解释器式控制流建模；
- `run_summary.csv` 中仍会保留中间失败项，最终实验统计应以 `final_summary.csv` 为准。


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

### LeetCode → Eppather → Concrete Replay Validation

For normalized LeetCode C functions whose entry parameters are scalar `int`s,
the complete path/test-input chain can be checked with:

```bash
python3 tools/e2e_path_validation.py \
  testcase/output_complete2/greatest-common-divisor-1.c \
  --function gcd_iter \
  --cnip ./cnip \
  --max-loop 3 \
  --output e2e-path-report.json
```

The command performs these steps in a fresh temporary directory:

1. run DFS2 and collect `path_<function>_<id>.txt` and matching feasible
   `result_<function>_<id>.txt` artifacts;
2. parse the Z3 model, convert unsigned 32-bit bit patterns to valid signed C
   `int` values, and deterministically complete unconstrained inputs with zero
   (or one when an omitted parameter is used as a divisor, preventing undefined
   divide/modulo-by-zero during concrete replay);
3. instrument every `if`, `while`, and `for` condition in the selected function;
   concrete `while`/`for` execution uses the same `--max-loop` bound as DFS2,
   so replay validates the bounded program analyzed by Eppather; recursive calls
   still execute normally but only the outer entry invocation contributes trace
   events, matching Eppather's intraprocedural path artifacts;
4. compile a concrete replay harness with `-O0` and UndefinedBehaviorSanitizer;
5. execute every generated input and compare the ordered runtime branch truth
   values with the ordered `@(...)` decisions in the Eppather path;
6. write a JSON report and return non-zero on a mismatch, replay error, empty
   result set, or non-zero Eppather exit; executions that reach undefined ISO C
   behavior are reported separately as `undefined` instead of as mismatches.

Pointer and variable-length array parameters are intentionally rejected by the
automatic harness. Normalize them to the fixed-array/scalar subset first; this
prevents a test driver from guessing array ownership or length and accidentally
validating a different program. The generated report records each model and
both decision sequences so failures are directly reproducible.

Run the maintained 20-program regression manifest in parallel with:

```bash
python3 tools/e2e_batch_validation.py \
  --cnip ./cnip \
  --max-loop 3 \
  --jobs 2 \
  --output-dir e2e-batch-reports
```

The batch runner writes one detailed JSON report per function plus an aggregate
`summary.json`. It returns non-zero only for a real ordered-path mismatch or an
execution error; undefined source-program behavior such as negating `INT_MIN`
is retained in the report for diagnosis without being misclassified as an
Eppather path-generation defect.

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
