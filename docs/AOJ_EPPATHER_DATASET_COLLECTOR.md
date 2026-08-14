# AOJ C 数据集采集与 Eppather 兼容性筛选

版本：1.0（2026-08-14）

## 站点选择

使用 Aizu Online Judge（AOJ）。AOJ 提供公开题目、公开提交源码查询和官方系统测试数据接口，比只公开样例而隐藏系统测试的竞赛平台更适合路径回放实验。

采集器只读取公开提交（`policy != private`），并在元数据中保存题目、提交 ID、用户 ID 和原始页面 URL。公开可见不代表代码没有版权；数据用于研究前仍需遵守 AOJ 条款并保留归属，不应重新发布完整镜像。

## 快速运行

```bash
python3 tools/collect_aoj_eppather_dataset.py \
  --problem-limit 100 \
  --solutions-per-problem 10 \
  --max-system-tests 20 \
  --verify
```

下载全部官方测试时把 `--max-system-tests` 设为 `0`。首次运行可能很久，这是刻意的：默认每个 HTTP 请求间隔 1 秒并指数退避，避免对 AOJ 服务造成压力。缓存位于输出目录的 `.cache`，中断后可直接重跑。

## 筛选规则

- 题目：从 ITP1、ALDS1、DSL、DPL、GRL 系列探测，按 array、matrix、sequence、pointer、list、sort、search 等词加权。
- 答案：依次查询 C、C11、C99，去除私有提交和规范化后重复源码，每题保留 10 份。
- Eppather：允许可剥离的 `main` 和标准输入输出外壳；拒绝 struct/union/enum、typedef、宏、VLA、动态内存、goto/switch/do、浮点、可变参数、函数指针、C++ 语法以及未知外部调用。
- 验证：`--verify` 使用 C11 编译每份源码，并逐个执行已下载的官方测试；单例默认 3 秒超时，结果写入各题 `metadata.json`。

筛选是保守的语法预检，不是完整 C 解析器。通过筛选表示“适合进一步剥离 I/O 外壳后输入 Eppather”，不表示未经预处理的完整竞赛程序可直接输入分析器。

## 输出结构

```text
testcase/aoj_eppather_dataset/
  manifest.json
  .cache/
  problems/ITP1_6_A/
    description.json
    metadata.json
    solutions/<judge-id>.c
    tests/001.in
    tests/001.out
```

成功返回码为 0；若候选池内满足“题目相关、10 份兼容公开答案”条件的题目不足 100 个，仍保存已有结果，但返回码为 2，便于 CI 识别数据不足。

## 可复现实验建议

1. 固定 `manifest.json` 和采集日期，避免公开提交集合变化造成样本漂移。
2. 先运行默认 20 个系统测试进行批量冒烟验证，再对最终样本使用 `--max-system-tests 0` 全量回放。
3. 将每份源码的 `verification.passed == verification.total` 作为进入 Eppather 路径实验的硬条件。
4. 不把生成的数据集提交到 Git；只提交采集器、规则和实验清单。
