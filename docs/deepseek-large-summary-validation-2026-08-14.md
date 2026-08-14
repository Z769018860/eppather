# DeepSeek 大型项目函数摘要修复与验证记录

- 日期：2026-08-14（Asia/Tokyo）
- 修复前基线：`5fc597e`
- API：DeepSeek 官方兼容接口
- 模型：`deepseek-v4-pro`
- API 单请求超时：900 秒
- 本地分析约束：`--maxloop 1 --maxpaths 40`，每模式 120 秒
- 对象：cJSON、tinyexpr、Lua 的代表函数摘要

## 修复内容

1. DP 的缓存状态加入路径前缀，防止不同约束分支复用同一后缀并产生伪可行最坏路径。
2. DP 默认只在完整叶子路径上执行可行性判定；不完整前缀求解保留为
   `EPPATHER_PREFIX_FEASIBILITY=1` 实验选项。
3. DP 选出路径后使用完整路径计数器复核报告 MEMS，使 `-g` 与 `-q` 使用一致口径。
4. DFS 循环递归返回时恢复循环计数，避免共享状态污染后续分支。
5. 将 LLM 摘要约束为已初始化的小型固定数组、十进制整数和显式循环边界。
6. cJSON 摘要将循环体内的块级声明提升至函数作用域，消除 DP 段错误。
7. 新增 `tools/validate_llm_summaries.sh` 批量编译、运行并核对 DFS2/DP MEMS。

## 最终结果

| 摘要 | C 编译 | DFS2 | DP | DFS2 最大 MEMS | DP MEMS | 一致性 |
|---|---:|---:|---:|---:|---:|---:|
| cJSON ParseWithLengthOpts | 通过 | 通过 | 通过 | 15 | 15 | 通过 |
| Lua luaZ_read | 通过 | 通过 | 通过 | 21 | 21 | 通过 |
| tinyexpr te_interp | 通过 | 通过 | 通过 | 20 | 20 | 通过 |

批量脚本退出状态为 0，三项均未发生崩溃或超时。

## 已确认的根因

- 原 Lua DP 结果 17 对应一条矛盾路径：先约束 `n > z[0]`，再令
  `m=z[0]`、`n=n-m`，最后要求 `n==0`。缓存键缺少路径约束导致该路径被误判可行。
- 原 cJSON 摘要包含未初始化的 `input[100]`、两段大循环和循环体块级局部声明。
  前两项造成状态空间膨胀，块级声明触发 DP 后端段错误。
- 对规范化摘要进行同口径复测后，DFS2 与 DP 的最大 MEMS 已全部一致。

## 复现命令

```bash
CNIP=./cnip MAXLOOP=1 MAXPATHS=40 RUN_TIMEOUT=120 \
  bash tools/validate_llm_summaries.sh
```

详细日志默认保存于 `/tmp/eppather-llm-summary-validation/`，不提交 API Key 或源码上传凭据。
