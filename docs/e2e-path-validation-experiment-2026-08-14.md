# Eppather 端到端路径验证实验记录（2026-08-14）

## 1. 记录信息

| 项目 | 值 |
|---|---|
| 实验编号 | `EPP-E2E-20260814-v1` |
| 仓库 | `Z769018860/eppather` |
| 分支 | `main` |
| 被测版本 | `e67dcdc1026606ef7751f6aca426da93940c549e` |
| 被测版本提交时间 | 2026-08-14 06:48:09 UTC / 2026-08-14 15:48:09 JST |
| 实验日期 | 2026-08-14（JST） |
| 本记录生成时间 | 2026-08-14 15:50:30 JST（UTC+09:00） |
| 测试清单版本 | `tools/e2e_batch_manifest.json`，SHA-256 `f09226bc5e83301ed9395cc640303aaad217cd0c2a38b0f4a310b9c76ee986ec` |
| 单程序验证器版本 | SHA-256 `8d1acdc5ac37be7b6b3722701646bfa52109dda9fb882444e2b1dca3a64e9ac6` |
| 批量验证器版本 | SHA-256 `ee33935fb7a35b206edefc9cd38d04d7a2dab3c7be9b1d4002069a14c20dd55b` |

这里的“被测版本”是创建本实验记录之前 `main` 分支的最新提交。创建本文件会产生一个新的文档提交，但不会改变上述实验所使用的代码和测试工具版本。

## 2. 实验目标与测试链

本实验验证以下完整链路：

1. 输入规范化后的 C/LeetCode 风格函数；
2. 使用 Eppather DFS2 生成有界路径、SMT 约束和测试输入；
3. 从 Z3 模型中恢复合法的 32 位有符号 C `int` 输入；
4. 将输入重新送入插桩后的原始 C 函数；
5. 在具体执行中应用与 Eppather 相同的循环展开上限；
6. 按顺序比较运行时分支真值与 Eppather 路径中的 `@(...)` 决策；
7. 将真实路径不匹配、执行错误和原程序未定义行为分别统计。

实验参数：

| 参数 | 值 |
|---|---:|
| 程序数量 | 20 |
| `max_loop` | 3 |
| 并行任务数 | 2 |
| 单次 Eppather/回放超时 | 120 秒 |
| 批量单程序超时 | 300 秒 |
| 具体编译优化级别 | `-O0` |
| 未定义行为检测 | `-fsanitize=undefined -fno-sanitize-recover=undefined` |

复现实验命令：

```bash
python3 tools/e2e_batch_validation.py \
  --cnip ./cnip \
  --max-loop 3 \
  --jobs 2 \
  --output-dir e2e-batch-reports
```

## 3. 执行环境

| 组件 | 版本 |
|---|---|
| 操作系统环境 | Ubuntu 24.04 系列容器环境 |
| C++ 编译器 | GCC/G++ 13.3.0 (`Ubuntu 13.3.0-6ubuntu2~24.04`) |
| C 编译器 | GCC 13.3.0 (`Ubuntu 13.3.0-6ubuntu2~24.04`) |
| Python | 3.12.13 |
| Eppather 循环约束 | 每次词法进入循环时独立应用 `max_loop=3` |
| 回放范围 | 只记录目标函数最外层调用；递归子调用正常执行但不污染函数内路径序列 |

## 4. 最终结果

| 指标 | 数量 | 比例 |
|---|---:|---:|
| 总路径/测试输入 | 224 | 100% |
| 路径完全吻合 | 212 | 94.64% |
| 路径不匹配 | 0 | 0% |
| 执行错误或崩溃 | 0 | 0% |
| 原 C 程序未定义行为 | 12 | 5.36% |

在所有具有 ISO C 定义语义、可进行有效具体回放的 212 条路径中，Eppather 路径与原程序运行路径的吻合率为 **212/212（100%）**。

`undefined` 不计为 Eppather 路径错误。这些输入在原程序中触发了 UBSan，例如对 `INT_MIN` 取负或有符号整数溢出，因此不存在可移植、唯一的 ISO C 具体执行真值。

## 5. 逐程序结果

| # | 源文件 / 函数 | 吻合 | 不匹配 | 未定义 | 错误 | 总计 |
|---:|---|---:|---:|---:|---:|---:|
| 1 | `almost-prime.c::kprime` | 96 | 0 | 0 | 0 | 96 |
| 2 | `arithmetic-integer.c::func` | 1 | 0 | 0 | 0 | 1 |
| 3 | `factorial-1.c::factorial` | 4 | 0 | 0 | 0 | 4 |
| 4 | `factorial-2.c::factorialSafe` | 5 | 0 | 0 | 0 | 5 |
| 5 | `fibonacci-sequence-1.c::fibb` | 2 | 0 | 0 | 0 | 2 |
| 6 | `integer-comparison.c::compare` | 3 | 0 | 0 | 0 | 3 |
| 7 | `leap-year.c::is_leap_year` | 4 | 0 | 0 | 0 | 4 |
| 8 | `sum-digits-of-an-integer.c::SumDigits` | 4 | 0 | 0 | 0 | 4 |
| 9 | `greatest-common-divisor-1.c::gcd_iter` | 20 | 0 | 6 | 0 | 26 |
| 10 | `truncatable-primes-2.c::func` | 1 | 0 | 0 | 0 | 1 |
| 11 | `compile-time-calculation-1.c::fac` | 4 | 0 | 0 | 0 | 4 |
| 12 | `detect-division-by-zero.c::try_division` | 1 | 0 | 0 | 0 | 1 |
| 13 | `ethiopian-multiplication.c::ethiopian` | 7 | 0 | 0 | 0 | 7 |
| 14 | `euclidean_example.c::euclid` | 41 | 0 | 1 | 0 | 42 |
| 15 | `exponentiation-operator-1.c::ipow` | 7 | 0 | 1 | 0 | 8 |
| 16 | `harshad-or-niven-series.c::digsum` | 4 | 0 | 0 | 0 | 4 |
| 17 | `least-common-multiple.c::lcm` | 1 | 0 | 3 | 0 | 4 |
| 18 | `modular-exponentiation.c::modular_exponentiation` | 1 | 0 | 0 | 0 | 1 |
| 19 | `sequence-of-non-squares.c::nonsqr` | 3 | 0 | 1 | 0 | 4 |
| 20 | `sum-multiples-of-3-and-5-1.c::sum35` | 3 | 0 | 0 | 0 | 3 |
| **合计** | **20 个程序** | **212** | **0** | **12** | **0** | **224** |

## 6. 本轮发现并修复的问题

### 6.1 CFG 嵌套 `if/else` 错误落入

当 then 分支中还包含嵌套 `if` 时，内部 join 曾被错误连接到外层 else 的首语句，导致一次路径同时执行 then 和 else。修复后，在进入外层 else 之前先关闭 then 内部的条件帧，并将其连接到外层 if join。

### 6.2 `if` 分支内循环错误落入另一分支

then 分支内的循环在进入 else 时没有先完成收束，其 false/join 边会错误指向 else。修复后，完全位于 then 内的循环在切换到 else 前连接到外层 if join。

### 6.3 嵌套循环出口跳过外层回边

内外循环同时收束时，内层 join 曾直接连接到两个循环之外，跳过外层 update 和条件检查。修复后控制流为：

```text
内层 false/join -> 外层 bodyEnd/update -> 外层条件
```

该修复使 `almost-prime` 从存在大量路径差异提升为 **96/96 全部吻合**。

### 6.4 循环回放计数跨动态入口污染

旧回放器对同一词法循环使用全程累计计数，内层循环再次被外层循环调用时不会重置。现在每次进入词法循环都会重置对应计数器，使具体执行与 Eppather 的有界展开状态一致。

### 6.5 递归调用轨迹污染

旧回放会把 Fibonacci 等函数的递归子调用分支混入当前函数内路径。现在只记录最外层入口调用，保持与 Eppather 当前函数内路径产物一致。

### 6.6 崩溃和未定义行为处理

- 未约束且作为除数的参数默认补全为 `1`，避免人为制造除零崩溃；
- 回放使用 UBSan；
- `INT_MIN` 取负、有符号溢出等被记录为 `undefined`；
- `undefined`、`mismatch`、`error` 分开统计，不再把源程序语义问题误报为路径生成问题。

## 7. 相关代码版本

| 提交 | 内容 |
|---|---|
| `76f1cc7` | 循环路径和 DFS2 崩溃修复 |
| `fa5633b` | 有界具体回放 |
| `cc5b601` | 初始自动化测试 |
| `408f207` | 初始链路文档 |
| `2e39be3` | CFG if/loop 嵌套连接修复 |
| `a3177b6` | 递归与缺失除数模型的安全回放 |
| `6ae9858` | 安全模型补全和递归插桩测试 |
| `caed6b1` | 安全有界回放文档 |
| `86f56c9` | 嵌套 if/else 和 loop CFG 控制流修复 |
| `269ecc9` | 词法循环约束和未定义行为分类 |
| `4a2a49d` | 嵌套循环回放回归测试 |
| `5daed5f` | 批量路径验证使用说明 |
| `a681a3b` | 并行批量验证器 |
| `e67dcdc` | 20 程序批量测试清单；本报告被测基线 |

## 8. 结果解释与后续建议

当前结果证明，在这 20 个规范化 C 程序的 212 条有定义执行路径上，生成测试输入重新执行原代码后，运行路径与 Eppather 静态路径完全一致。

后续建议将 `undefined` 输入分为两种实验口径：

1. **严格 C 语义口径**：保持当前做法，将其独立报告；
2. **有效测试生成口径**：在 SMT 模型中增加已知 C 未定义行为约束，重新求取同一路径的替代模型，以尽可能减少 `undefined` 测试输入。

批量实验的机器可读结果由 `e2e_batch_validation.py` 生成。建议发布论文实验数据时同时保存 `summary.json`、逐函数 JSON、仓库提交 SHA 和本文件列出的三个工具 SHA-256，以保证结果可追溯和可复现。
