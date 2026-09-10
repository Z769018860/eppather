# ProbMEMS 实验进展与下一阶段数据缺口（2026-09-10）

## 本轮新增实验：自适应 maxloop 重复性

对 40 个基准用例重复运行 3 次，共 120 次分析。配置保持为 maxpaths=100、maxloop ceiling=12、自适应半径=4、单次候选超时=30 秒。

- 40/40 用例编译成功。
- 39/40 用例每轮均完整成功，即 117/120 个 PASS。
- 34 个含内存访问且完整执行的用例全部得到非零 MEMS。
- 5 个纯标量用例稳定为真零。
- gt20_function_call.c 三轮均失败，是稳定的多函数生命周期/清理崩溃，并非 maxloop 猜测波动。
- 40/40 用例的运行状态、所选 maxloop、解空间计数、加权平均 MEMS、MaxMEMS 均跨三轮一致。
- 三轮按用例汇总耗时分别落在 20–35 秒范围；逐用例中位耗时之和为 24 秒。
- 较慢用例仍是 gt24（8–10 秒）和 gt40（固定 11 秒），应作为性能剖析对象。

数据：
- [稳定性汇总 CSV](probmems-reproducibility-summary-2026-09-10.csv)
- [GitHub Actions run 34516923288](https://github.com/Z769018860/eppather/actions/runs/34516923288)
- 完整 120 行原始 CSV 保存在该运行的 probmems-reproducibility-aggregate artifact 中。

## 当前证据边界

现有结果足以说明：微型基准上的计算是确定的；while 上界修复有效；自适应猜测没有引入结果波动；零值可区分为无内存访问的真零与分析失败。

现有结果尚不足以支撑完整论文结论，因为项目级样本较少、真实函数覆盖不完整、缺少独立正确性 oracle、缺少正式基线和统计检验，也没有系统记录峰值内存。

## 下一步实验与当前缺失数据

| 优先级 | 实验 | 建议设计 | 必须采集的数据 | 当前缺失 |
|---|---|---|---|---|
| P0 | 修复并验证多函数输入 | 修复 Issue #77；增加 10 个含 2–5 个函数、调用链、递归排除说明的用例；每例重复 3 次 | 函数级/程序级聚合语义、退出码、崩溃栈、路径数、解数、EMEMS、MaxMEMS | gt20 完整结果；跨函数聚合定义；多函数回归数据 |
| P0 | 小规模精确 oracle | 选择 20–30 个小程序，穷举全部输入并人工/插桩统计每个输入的内存访问；与 VolCE 权重结果逐项比较 | 每输入真实 MEMS、输入数、路径解数、加权和、绝对/相对误差 | 独立 ground truth；误差率和一致率 |
| P0 | 真实项目扩展 | cJSON、Lua、tinyexpr、inih、sds、list 外再加入 8–12 个 C 项目；每项目选 10–30 个有数组/指针且能独立分析的函数 | 项目版本、LOC、函数数、支持/失败/超时数、EMEMS、MaxMEMS、路径数、解数、耗时、峰值 RSS | 足够的项目/函数样本；失败原因分布；峰值内存 |
| P0 | 基线比较 | 对相同函数比较 MaxMEMS、非加权路径平均、随机/均匀输入采样、本文精确加权平均 | 各方法估计值、与 oracle 误差、时间、内存；EMEMS/MaxMEMS 比值 | 正式基线结果与效应量 |
| P1 | maxloop 消融 | 固定上界 {1,2,3,4,5,8,10,12} 对比自适应策略；区分 complete、timeout、path-cap-censored | 成功率、结果偏差、总耗时、重试数、最小稳定上界 | 自适应相对固定策略的统计收益 |
| P1 | 输入域敏感性 | 至少使用 [-1,1]、[-3,3]、[-10,10]；对数组下标另设合法域；按项目分层 | 解空间增长、EMEMS变化、超时率、域稳定点 | 输入域对结论的影响；cJSON 宽域可行数据 |
| P1 | maxpaths 敏感性 | 对发生截断者使用 {100,300,1000,3000}，必要时抽样；明确删失规则 | path_limit_hit、覆盖路径数、EMEMS/MaxMEMS 收敛、耗时/RSS | cJSON 等 path-cap-censored 配置的未删失结果 |
| P1 | 性能与可扩展性 | 按路径数、解空间规模、循环嵌套深度、指针/数组类别分桶 | wall time、CPU time、峰值 RSS、超时、路径/秒、解/秒 | 峰值 RSS、CPU 时间、规模曲线 |
| P2 | 稳定性增强 | 正式论文数据每配置独立重复 10 次；固定 runner 镜像和依赖版本 | 中位数、IQR、95% CI、异常值、机器规格 | 10 次重复、置信区间、环境版本锁定 |
| P2 | 威胁与覆盖率 | 建立支持/不支持语法清单，并对抽样项目统计可分析函数比例 | 总函数、筛选数、成功数、排除原因 | 工具适用范围和选择偏差数据 |

## 推荐执行顺序

1. 先修复 Issue #77，并固定“函数级还是程序级”的统计语义；否则真实项目实验可能把部分结果误当成完整结果。
2. 同时建立小规模穷举 oracle。这是证明加权平均值正确性的核心数据，优先级高于继续堆叠项目数量。
3. 扩展真实项目到至少 10–15 个、100–200 个目标函数，统一记录失败分类、wall time 与 peak RSS。
4. 在同一数据集上完成四种基线和 maxloop/maxpaths/输入域三类消融。
5. 最后做 10 次重复、统计检验和论文图表；避免在实验配置仍变化时提前计算显著性。

## 建议论文主表最少字段

subject, project_commit, function, LOC, memory_feature, input_domain, maxloop_policy,
selected_maxloop, maxpaths, completion_status, failure_class, path_count,
solution_space_count, weighted_sum, EMEMS, MaxMEMS, EMEMS_over_MaxMEMS,
wall_time_s, cpu_time_s, peak_rss_mb, repetition, censored

任何 timeout、core dump、缺指标或 path-limit hit 都不得当作普通数值参与均值；应单独报告为失败或删失数据。
