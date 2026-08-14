# list / inih / sds 函数摘要迭代实验与路径验证

## 1. 实验配置

- 执行时间：2026-08-14 17:38（Asia/Tokyo）
- 仓库：`Z769018860/eppather`
- 实验基线：`5e498e4`（包含 DP/DFS 正确性修复后的主分支）
- 分析后端：pafi-rs
- 模式：项目级函数摘要 `-s`，并对最终 slice 追加 DFS2 `-q` 与 DP `-g` 交叉验证
- 循环约束：`--maxloop 2`
- 路径约束：`--maxpaths 80`
- 摘要单次超时：120 秒
- DFS2/DP 交叉验证单次超时：60 秒
- 本轮目录：`testcase/_eppather_runs/20260814_173835/`

项目规模采用仓库既有实验口径：

| 项目 | 版本 | LOC | 函数数 | 主要特征 |
|---|---|---:|---:|---|
| clibs/list | 0.4.1 | 269 | 9 | 链表、结构体指针、节点增删 |
| inih | r62 | 441 | 10 | 字符串扫描、回调、INI 解析 |
| SDS | SDSLib 2.0 | 1,504 | 47 | 动态字符串、指针算术、变长布局 |

复现摘要实验：

```bash
python3 tools/run_small_project_summaries.py \
  --cnip ./cnip \
  --projects list,inih,sds \
  --entry-set all \
  --modes summary \
  --maxloop 2 \
  --maxpaths 80 \
  --timeout 120
```

## 2. 迭代更新过程

| 轮次 | 时间戳 | 更新内容 | 统计范围 | 成功数 | 成功率 |
|---|---|---|---:|---:|---:|
| R0 | 20260516_172730 | safe 入口；closure、entry-only、type-erased 与少量手写兼容摘要 | 13 | 13 | 100.0% |
| R1 | 20260516_180425 | 扩展为全函数集合，暴露非项目入口及 SDS 复杂语法问题 | 70 | 54 | 77.1% |
| R2 | 20260516_181840 | 过滤 4 个非项目入口，并为 SDS 增加 auto-compat | 66 | 61 | 92.4% |
| R3 | 20260516_183533 | 修复生成函数头，将 auto-compat 扩展到三个项目 | 66 | 66 | 100.0% |
| R4 | 20260516_185515 | 增加 semantic-stubbed，优先保留原函数控制流和槽位访问 | 66 | 66 | 100.0% |
| R5 | 20260814_173835 | 使用当前修复版后端重新执行全函数，并增加 DFS2/DP 交叉验证 | 66 | 66 | 100.0% |

R5 与 R4 相比，最终使用 `closure` 的函数由 3 个增加至 23 个，同时有 7 个函数使用
`entry_only`，说明最终结果中直接保留原函数体的比例明显增加。auto-compat 从 33 个下降到
21 个，但这仍意味着最终成功率不能直接解释为完整源码语义支持率。

## 3. R5 摘要生成结果

### 3.1 总体结果

| 项目 | 入口数 | 最终成功 | 成功率 | 总尝试数 | 最终 MEMS 范围 | 最终平均 MEMS | 最终结果累计时间 |
|---|---:|---:|---:|---:|---:|---:|---:|
| list | 9 | 9 | 100.0% | 38 | 0–5 | 1.000 | 0.588 s |
| inih | 10 | 10 | 100.0% | 44 | 0–2 | 1.200 | 1.279 s |
| sds | 47 | 47 | 100.0% | 116 | 0–2 | 0.277 | 20.635 s |
| 合计 | 66 | 66 | 100.0% | 198 | 0–5 | 0.515 | 22.502 s |

这里的“最终结果累计时间”只统计每个入口最终被选中 slice 的执行时间，不包含此前失败尝试。

### 3.2 最终 slice 分布

| 项目 | closure | entry-only | type-erased | semantic-stubbed | compat-entry | auto-compat |
|---|---:|---:|---:|---:|---:|---:|
| list | 0 | 0 | 3 | 1 | 2 | 3 |
| inih | 0 | 0 | 2 | 2 | 1 | 5 |
| sds | 23 | 7 | 3 | 0 | 1 | 13 |
| 合计 | 23 | 7 | 8 | 3 | 4 | 21 |

按保真等级划分：

- 直接源码层（closure + entry-only）：30/66，45.5%；
- 语义近似层（type-erased + semantic-stubbed）：11/66，16.7%；
- 兼容模型层（compat-entry + auto-compat）：25/66，37.9%。

### 3.3 中间失败情况

| 项目 | 中间失败数 | SIGSEGV (-11) | SIGFPE (-8) | 普通失败 (rc=1) | rc=0 但摘要不完整 | 超时 |
|---|---:|---:|---:|---:|---:|---:|
| list | 29 | 24 | 0 | 0 | 5 | 0 |
| inih | 34 | 24 | 0 | 7 | 3 | 0 |
| sds | 69 | 41 | 5 | 7 | 16 | 0 |

这些是迭代过程中较高保真 slice 的失败次数，不是最终入口失败数。脚本会按
`closure → entry-only → type-erased → semantic-stubbed → compat-entry/auto-compat`
继续降级，直到得到可用结果。

## 4. 分项目详细结果

### 4.1 clibs/list

| 入口 | 最终 slice | worst MEMS | weighted average MEMS |
|---|---|---:|---:|
| list_at | auto-compat | 1 | 0.5 |
| list_destroy | auto-compat | 1 | 0.5 |
| list_find | auto-compat | 2 | 1.0 |
| list_lpop | compat-entry | 0 | 0 |
| list_lpush | type-erased | 0 | 0 |
| list_new | type-erased | 5 | 5.0 |
| list_remove | semantic-stubbed | 0 | 0 |
| list_rpop | compat-entry | 0 | 0 |
| list_rpush | type-erased | 0 | 0 |

list 的最终覆盖率为 100%，但没有入口直接使用 closure/entry-only，表明结构体指针和节点
所有权仍是原生前端的主要阻塞。5/9 条目的 worst MEMS 为 0，应理解为兼容摘要计数结果，
不能作为真实库函数内存开销的准确估计。

### 4.2 inih

| 入口 | 最终 slice | worst MEMS | weighted average MEMS |
|---|---|---:|---:|
| ini_find_chars_or_comment | type-erased | 0 | 0 |
| ini_lskip | semantic-stubbed | 0 | 0 |
| ini_parse | auto-compat | 2 | 1.0 |
| ini_parse_file | auto-compat | 2 | 1.0 |
| ini_parse_stream | auto-compat | 2 | 1.0 |
| ini_parse_string | auto-compat | 2 | 1.0 |
| ini_parse_string_length | auto-compat | 2 | 1.0 |
| ini_reader_string | compat-entry | 0 | 0 |
| ini_rstrip | semantic-stubbed | 0 | 0 |
| ini_strncpy0 | type-erased | 2 | 2.0 |

inih 的 5 个解析入口依赖 auto-compat；字符串扫描 helper 可以进入 type-erased 或
semantic-stubbed。4/10 条目 worst MEMS 为 0。

### 4.3 SDS

SDS 的 47 个入口全部生成摘要，其中 23 个使用 closure、7 个使用 entry-only、3 个使用
type-erased，直接源码层比例为 30/47（63.8%）。13 个使用 auto-compat，1 个使用
compat-entry。worst MEMS 分布如下：

| worst MEMS | 函数数 | 比例 |
|---:|---:|---:|
| 0 | 37 | 78.7% |
| 1 | 7 | 14.9% |
| 2 | 3 | 6.4% |

耗时最高的最终摘要包括 `sdscatfmt`（6.028 s）、`sdscatrepr`（3.513 s）、
`sdscpylen`（1.996 s）和 `sdsmapchars`（1.034 s）。大量零 MEMS 说明当前 closure
虽能完成路径摘要，但真实指针/库调用的内存访问仍未被充分映射到整数槽位计数。

## 5. DFS2 与 DP 交叉验证

对 66 个最终 slice 使用相同的 `maxloop=2`、`maxpaths=80` 运行 DFS2 和 DP：

| 项目 | DFS2 成功 | DP 成功 | 同一 slice MEMS 一致 | DFS2 崩溃 | DP 崩溃 | DP 超时 |
|---|---:|---:|---:|---:|---:|---:|
| list | 9/9 | 9/9 | 9/9 | 0 | 0 | 0 |
| inih | 10/10 | 8/10 | 8/10 | 0 | 0 | 2 |
| sds | 47/47 | 47/47 | 47/47 | 0 | 0 | 0 |
| 合计 | 66/66 | 64/66 | 64/66（97.0%） | 0 | 0 | 2 |

累计执行时间：list DFS2/DP 为 0.559/1.465 秒，inih 为 1.081/153.873 秒（含两个
60 秒超时），SDS 为 16.539/66.730 秒。

两个异常均位于 inih：

| 入口 | slice | DFS2 | DP | 后续迭代 |
|---|---|---:|---|---|
| ini_find_chars_or_comment | type-erased | MEMS=0 | 60 s 超时 | semantic-stubbed 仍无法正常结束；auto-compat 为 2/2 |
| ini_strncpy0 | type-erased | MEMS=2 | 60 s 超时 | semantic-stubbed 为 0/0；auto-compat 为 2/2 |

因此有两种统计口径：

1. 保持摘要 slice 不变的严格一致率：64/66，97.0%；
2. 允许继续降级到 auto-compat 的可完成率：66/66，100%，但这不代表语义等价准确率。

## 6. 结论与局限

1. 三项目的函数摘要生成覆盖率达到 100%，路径阶段没有出现崩溃。
2. 同一最终 slice 上 DFS2/DP 的可验证一致率为 97.0%，剩余两项为 DP 性能超时而非结果冲突。
3. 直接源码层只占 45.5%，37.9% 的入口仍依赖兼容模型，因此“生成成功率”不能替代
   “摘要语义准确率”。
4. 46/66 个最终摘要的 worst MEMS 为 0，特别是 SDS 的零值比例达到 78.7%；这说明当前
   MEMS 质量仍明显受类型擦除、外部调用和指针槽位建模不足影响。
5. 下一轮应优先提升 list 的结构体指针摘要、inih 的字符串循环 DP 状态合并，以及 SDS
   外部内存操作到显式槽位读写的映射，而不是继续依靠 auto-compat 提高表面成功率。
