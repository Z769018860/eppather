#!/usr/bin/env python3
from __future__ import annotations
import argparse,csv,json,statistics
from pathlib import Path

def main():
    ap=argparse.ArgumentParser(); ap.add_argument('--input',type=Path,required=True); ap.add_argument('--output',type=Path,required=True); a=ap.parse_args()
    rows=[]
    for p in a.input.glob('**/coverage-*.json'): rows.extend(json.loads(p.read_text()))
    by={r['problem_id']:r for r in rows}; rows=[by[k] for k in sorted(by)]
    ok=[r for r in rows if r['status']=='ok']; applicable=[r for r in ok if r.get('validated_candidates',0)>0]
    def avg(key): return statistics.mean(r[key] for r in applicable) if applicable else 0
    summary={'problems_total':len(rows),'status_ok':len(ok),'validated_applicable':len(applicable),
      'not_applicable':sum(r['status']=='not_applicable' for r in rows),'errors':sum(r['status']=='error' for r in rows),
      'generated_tests_total':sum(r.get('minimum_tests',0) for r in applicable),
      'official_tests_total':sum(r.get('official_tests',0) for r in applicable),
      'eppather_predicted_coverage_mean':avg('eppather_predicted_coverage'),'eppather_actual_coverage_mean':avg('eppather_coverage'),'official_coverage_mean':avg('official_coverage'),
      'coverage_correct':sum(bool(r.get('coverage_prediction_correct')) for r in applicable),
      'replay_matches':sum(r.get('path_replay_matches',0) for r in applicable),
      'candidate_paths':sum(r.get('candidate_paths',0) for r in applicable)}
    a.output.mkdir(parents=True,exist_ok=True); (a.output/'summary.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2))
    fields=['problem_id','status','branches','candidate_paths','validated_candidates','minimum_tests','eppather_predicted_edges','eppather_predicted_coverage','eppather_covered_edges','eppather_coverage','official_tests','official_covered_edges','official_coverage','coverage_prediction_correct','path_replay_matches','detail']
    with (a.output/'results.csv').open('w',newline='',encoding='utf-8') as f:
        w=csv.DictWriter(f,fieldnames=fields,extrasaction='ignore'); w.writeheader(); w.writerows(rows)
    md=['# AOJ 100题 Eppather 最小测试集与覆盖率实验','', '## 汇总','', '|指标|结果|','|---|---:|']
    for k,v in summary.items(): md.append(f'|{k}|{v:.4f}|' if isinstance(v,float) else f'|{k}|{v}|')
    md += ['', '## 逐题结果','', '|题目|状态|Eppather候选|最小集|Eppather覆盖率|官方测试数|官方覆盖率|覆盖映射正确|','|---|---|---:|---:|---:|---:|---:|---|']
    for r in rows: md.append(f"|{r['problem_id']}|{r['status']}|{r.get('candidate_paths','')}|{r.get('minimum_tests','')}|{r.get('eppather_coverage','')}|{r.get('official_tests','')}|{r.get('official_coverage','')}|{r.get('coverage_prediction_correct','')}|")
    md += ['', '## 口径', '', '- 分支覆盖率分母为代表实现中静态条件数的两倍（真/假边）。', '- 最小集在 Eppather 生成且通过转换模型—原程序覆盖映射验证的候选输入上，用0-1整数规划精确求解。', '- 官方覆盖率使用同一代表实现和同一分支编号测量。', '- `not_applicable` 不计入均值；原因保留在 CSV。', '- 生成输入重新喂给原始 AOJ 程序；只有转换模型与原程序的实际覆盖边集合一致才计为正确。']
    (a.output/'report.md').write_text('\n'.join(md)+'\n',encoding='utf-8'); print(json.dumps(summary,ensure_ascii=False,indent=2))
if __name__=='__main__': main()
