# ProbMEMS / EMEMS SANER 2027 实验路线

本文档把加权平均 MEMS 独立论文的研究问题转化为可复现的实验阶段。所有正式论文结果必须区分完整期望值、条件期望值和分析失败，不能把超时、循环截断或计数失败记为零概率。

## 1. 研究目标与指标

对有效输入空间 \(\Omega\)、可行路径 \(\pi_i\)、路径解数量 \(n_i\) 和路径 MEMS \(m_i\)，定义：

- 路径概率：\(p_i=n_i/|\Omega|\)；
- 路径期望贡献：\(c_i=p_i m_i\)；
- Expected MEMS：\(EMEMS=\sum_i p_i m_i\)；
- 概率质量覆盖率：\(MassCoverage=\sum_{i\in counted}n_i/|\Omega|\)；
- 最坏/平均差距：\(Gap=MaxMEMS/EMEMS\)。

必须额外报告方差、P50/P90/P95/P99、超过阈值的概率，以及未探索概率质量。当前工具尚未输出这些字段，因此它们属于 Phase 1 的实现任务。

## 2. 实验顺序

### Phase 0：可信度闸门与零值诊断（立即执行）

目标：确认已有大量 weighted sum 为 0 的原因，并判断 maxloop 是否过小。

运行配置：

- 项目：cJSON、tinyexpr、Lua、clibs/list、inih、sds；
- 输入域：[-1,1]、[-3,3]；
- maxloop：1、2、3、5；
- maxpaths：40（保持与已有结果一致，单独标记是否触顶）；
- 单次超时：180 秒。

输出字段：

- subject、source、input_kind；
- lower、upper、maxloop、maxpaths；
- compile_status、run_status、elapsed_seconds；
- path_count、solution_space_count；
- weighted_mems_sum、weighted_average_mems、dfs_max_mems；
- path_limit_hit；
- zero_diagnostic；
- average_to_max_ratio。

判定规则：

- weighted sum = 0 且 MaxMEMS > 0：标记 ZERO_WEIGHT_REQUIRES_DIAGNOSIS；
- path_count >= maxpaths：标记 path_limit_hit=YES，结果不得称为完整 EMEMS；
- 退出码 124：标记 TIMEOUT，不得写为零；
- 缺少 VolCE 输出：标记 MISSING_METRIC；
- 编译失败与运行失败分别记录。

验收标准：

1. 六个对象全部生成每个配置的行；
2. 任何失败均保留日志；
3. 可以比较 maxloop 增加后零权重是否消失；
4. 可以比较扩大输入域后零解路径是否获得正解；
5. cJSON 等触及 maxpaths 的结果明确标记为条件结果。

自动化入口：`.github/workflows/probmems-sensitivity.yml`。
本地入口：`tools/run_probmems_sensitivity.sh`。

### Phase 1：路径状态、总输入空间与概率质量

这是正式准确性实验前必须完成的工具增强。

每条路径新增状态：

- COUNTED_POSITIVE；
- COUNTED_ZERO；
- UNSAT；
- OUT_OF_DOMAIN；
- LOOP_TRUNCATED；
- PATH_LIMIT_REACHED；
- COUNT_TIMEOUT；
- COUNT_UNSUPPORTED；
- COUNT_ERROR。

函数级新增：

- valid_input_space_count；
- counted_solution_count；
- residual_solution_count；
- mass_coverage；
- conditional_emems；
- emems_lower_bound；
- emems_upper_bound；
- variance；
- p50/p90/p95/p99；
- maximum_path_probability。

关键一致性检查：

1. 确定性、终止且完整探索时，各路径约束必须互斥；
2. 完整探索时 \(\sum_i n_i=|\Omega|\)；
3. \(\sum_i p_i=1\)，允许数值误差不超过 1e-9；
4. 无法证明完整时只报告 conditional EMEMS 和区间；
5. 超时和不支持不得参与零值求和。

期望值区间：

若已计数路径覆盖 \(N_E\) 个输入，残余输入数 \(R=N-N_E\)，残余路径代价位于 \([L_R,U_R]\)，则：

- lower = (weighted_sum + R * L_R) / N；
- upper = (weighted_sum + R * U_R) / N。

验收标准：为每类状态提供至少一个单元测试，并把状态写入 CSV/JSON。

### Phase 2：可穷举真值实验（RQ1、RQ2）

构建 100–150 个有限域 C 函数：

- 普通与嵌套分支不少于 20；
- 短路条件不少于 15；
- 循环不少于 30；
- 数组不少于 30；
- 指针不少于 30；
- 数组+指针混合不少于 20；
- 函数调用不少于 15；
- 含不可行路径的函数不少于 15。

对每个有效输入穷举执行，记录动态路径 ID 和按相同语义插桩的 MEMS，得到每条路径精确 \(n_i\)、\(p_i\) 与 EMEMS。

基线：

1. Exhaustive ground truth；
2. ProbMEMS + VolCE；
3. Path-uniform mean；
4. Independent branch probability 0.5；
5. time-matched Monte Carlo。

指标：

- 路径概率 MAE；
- Total Variation Distance；
- false-zero count；
- EMEMS MAE/MAPE；
- Pearson、Spearman 和 R²；
- 95% bootstrap confidence interval。

验收标准：

- 所有报告准确率的函数必须具有完整真值；
- 静态与动态 MEMS 采用同一读写语义；
- 每个失败对象保留在数据集中并报告原因，不能静默删除。

### Phase 3：输入分布实验（RQ3）

每个函数至少比较：

1. bounded uniform；
2. boundary-heavy；
3. small-value-biased；
4. positive/asymmetric；
5. profile-derived bucketed distribution。

分桶概率计算：

\[
p_i=\sum_j w_j\frac{Count(PC_i\land B_j)}{Count(B_j)}.
\]

报告不同分布下：

- EMEMS；
- P95/P99；
- MaxMEMS/EMEMS；
- 最大 MEMS 路径概率；
- 函数排名变化；
- 对动态留出集的误差。

验收标准：训练 workload profile 与验证输入严格分离。

### Phase 4：循环、路径和时间预算收敛（RQ4）

独立控制变量：

- maxloop：1、2、3、5、8、10；
- maxpaths：20、40、100、250、500、1000；
- time budget：30、60、120、300 秒；
- 输入域：[-1,1]、[-3,3]、[-8,8]。

报告：

- loop-tail probability；
- mass coverage；
- conditional EMEMS；
- lower/upper interval；
- normalized interval width；
- 是否包含穷举真值；
- 运行时间和超时率。

实验原则：每次只改变一类预算；maxloop、maxpaths、输入域不能在同一组中同时改变，否则无法归因。

### Phase 5：等价实现排序（RQ5a）

使用现有 C 算法题数据，每题选择 3–10 个通过实现。对相同题目固定输入域和 workload，比较：

- MaxMEMS；
- path-uniform mean；
- branch-0.5 mean；
- ProbMEMS EMEMS；
- dynamic instrumented mean。

指标：

- Spearman rho；
- Kendall tau；
- pairwise ranking accuracy；
- top-1 selection accuracy；
- selection regret。

该实验用于证明 EMEMS 是否比 MaxMEMS 更适合预测“典型输入下哪个实现更节省内存访问”。

### Phase 6：测试排序（RQ5b）

候选方法：

- Random；
- Coverage-greedy；
- Probability-only；
- MEMS-only；
- expected contribution（p_i * m_i）；
- tail-aware；
- dynamic oracle。

预算：1、2、5、10、20、50 个测试，或测试集的 1%、5%、10%、20%、50%。

指标：

- Probability Mass Coverage；
- Expected MEMS Contribution Coverage；
- Top-k heavy path coverage；
- 最大已发现 MEMS；
- 首次发现 P99/MaxMEMS 路径的测试数与时间；
- budget-effectiveness AUC。

随机方法使用至少 30 个固定并公开的种子。统计比较使用 Wilcoxon signed-rank、Holm correction、Cliff's delta 和 95% bootstrap CI。

### Phase 7：真实项目与可扩展性（RQ6）

项目至少覆盖：

- cJSON；
- tinyexpr；
- Lua；
- clibs/list；
- inih；
- sds；
- 另外 2–4 个轻量 C 项目。

目标：8–10 个项目、至少 120 个真实函数。每个项目选择 10–30 个函数，不得仅使用一个摘要代表整个项目。

分开报告：

- original function；
- automatic compatibility slice；
- manually normalized summary。

规模指标：

- LOC、CFG nodes、branches、loops；
- symbolic inputs、arrays、pointers；
- feasible paths、counted paths；
- SMT time、VolCE time、total time；
- peak memory、timeout rate、mass coverage。

## 3. 论文表格与图

最低要求：

1. 数据集与复杂度统计表；
2. 路径概率准确率表；
3. 静态 EMEMS vs 动态真值散点图；
4. MaxMEMS/EMEMS 比值 ECDF 或箱线图；
5. 不同 workload 下的 EMEMS 排名变化；
6. maxloop/maxpaths 的质量覆盖率和区间收敛图；
7. 测试预算效果曲线；
8. 运行时间、超时率与消融表。

## 4. 当前已有结果的使用限制

已有六项目 CSV 是 feasibility study：

- cJSON 枚举 40 条路径，等于 maxpaths=40，可能截断；
- 当前项目实验使用 maxloop=1；
- cJSON、tinyexpr、Lua 是规范化函数摘要；
- clibs/list、inih、sds 是代表函数切片；
- 输入域为 [-1,1]；
- 结果不能解释为整个项目的平均性能；
- 不同输入维度的 solution count 不能直接横向排名。

当前可引用的初步 EMEMS：

- cJSON：9.66667，MaxMEMS 15；
- tinyexpr：18，MaxMEMS 20；
- Lua：16.6154，MaxMEMS 21；
- clibs/list：0.666667，MaxMEMS 1；
- inih：1.33333，MaxMEMS 2；
- sds：1.33333，MaxMEMS 2。

只有在 Phase 1 补充质量覆盖率后，才应把这些数值升级为正式论文结论。

## 5. 推荐的近期执行顺序

1. 运行 Phase 0 sensitivity workflow；
2. 根据日志对每个零权重案例分类；
3. 实现 Phase 1 状态与概率质量字段；
4. 先完成 30 个可穷举函数作为 pilot；
5. 确认误差指标和 CSV schema 后扩到 100–150 个；
6. 再做 workload、等价实现和测试排序；
7. 最后运行大规模真实项目，避免在统计口径未稳定前消耗大量 CI 时间。
