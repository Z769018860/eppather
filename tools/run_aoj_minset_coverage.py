#!/usr/bin/env python3
"""Eppather path-derived minimum test sets and concrete AOJ coverage replay."""
from __future__ import annotations
import argparse, csv, json, os, re, subprocess, tempfile
from pathlib import Path

FUNC = re.compile(r"\bint\s+main\s*\([^)]*\)\s*\{")
CALL = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
SCAN = re.compile(r"\bscanf\s*\(\s*\"([^\"]*)\"\s*,(.*?)\)\s*;", re.S)
OUT = re.compile(r"\b(?:printf|puts|putchar)\s*\([^;]*\)\s*;", re.S)
COND = re.compile(r"\b(if|while)\s*\(([^{};]*)\)|\bfor\s*\(([^;]*);([^;]*);([^)]*)\)")
MODEL_ARRAY = re.compile(r"\binput\s*\[\s*(\d+)\s*\]\s*=\s*(-?\d+)\s*;?")
PATH_COND = re.compile(r"@\((.*?)\);", re.S)

def int32(value: str) -> int:
    n=int(value)
    if 0x80000000 <= n <= 0xffffffff: n-=0x100000000
    if not -(1<<31) <= n < (1<<31): raise ValueError('model integer outside int32')
    return n

def block(source: str, match: re.Match[str]) -> tuple[int,int,str]:
    opening=match.end()-1; depth=0
    for pos in range(opening,len(source)):
        if source[pos]=='{': depth+=1
        elif source[pos]=='}':
            depth-=1
            if depth==0: return opening,pos,source[opening+1:pos]
    raise ValueError('unterminated main')

def normalize(source: str) -> tuple[str,int]:
    m=FUNC.search(source)
    if not m: raise ValueError('no plain int main')
    _,_,body=block(source,m)
    if re.search(r"\b(getchar|fgets|gets|sscanf)\s*\(",body): raise ValueError('non-integer input API')
    max_tokens=0
    def scan(mm: re.Match[str]) -> str:
        nonlocal max_tokens
        fmt,args=mm.group(1),mm.group(2)
        specs=re.findall(r"%(?:[-+0-9.*hl]*)([diuoxX])",fmt)
        if '%' in re.sub(r'%%','',fmt) and not specs: raise ValueError('unsupported scanf format')
        targets=[x.strip() for x in args.split(',')]
        if len(specs)!=len(targets): raise ValueError('scanf arity')
        out=[]; base=max_tokens
        for target in targets:
            target=re.sub(r'^&\s*','',target)
            if not re.fullmatch(r'[A-Za-z_]\w*(?:\s*\[[^\]]+\])?',target): raise ValueError('complex scanf target')
            out.append(f'{target} = input[{base + len(out)}];')
        max_tokens += len(targets)
        return ' '.join(out)
    body=SCAN.sub(scan,body); body=OUT.sub('',body)
    body=re.sub(r'\b([A-Za-z_]\w*)\s*\+\+',r'\1 = \1 + 1',body)
    body=re.sub(r'\+\+\s*([A-Za-z_]\w*)\b',r'\1 = \1 + 1',body)
    body=re.sub(r'\b([A-Za-z_]\w*)\s*--',r'\1 = \1 - 1',body)
    body=re.sub(r'--\s*([A-Za-z_]\w*)\b',r'\1 = \1 - 1',body)
    calls=set(CALL.findall(body))-{'if','for','while','sizeof','return','abs'}
    if calls: raise ValueError('helper/external calls: '+','.join(sorted(calls)))
    if re.search(r'\b(static|extern)\b',body): raise ValueError('storage duration')
    dims=[int(x) for x in re.findall(r'\[\s*(\d+)\s*\]',body)]
    if dims and max(dims)>4096: raise ValueError('array bound exceeds 4096')
    return 'int epp_model(int input[64]) {\n'+body+'\n}\n',max_tokens

def instrument_function(source: str, function_pattern: re.Pattern[str], stderr: bool=True) -> tuple[str,int]:
    m=function_pattern.search(source)
    if not m: raise ValueError('entry missing')
    opening,closing,body=block(source,m); count=0
    def repl(mm: re.Match[str]) -> str:
        nonlocal count
        idx=count; count+=1
        if mm.group(1): return f'{mm.group(1)} (EPP_TRACE({idx}, ({mm.group(2)})))'
        condition=mm.group(4).strip() or '1'
        return f'for ({mm.group(3)}; EPP_TRACE({idx}, ({condition})); {mm.group(5)})'
    body=COND.sub(repl,body)
    pre=('\n#include <stdio.h>\nstatic int epp_trace(int id,int v){fprintf(stderr,"EPP_BRANCH %d %d\\n",id,!!v);return v;}\n'
         '#define EPP_TRACE(id,expr) epp_trace((id),(expr))\n')
    return pre+source[:opening+1]+body+source[closing:],count

def run(cmd,cwd,input_text='',timeout=120,env=None):
    return subprocess.run(cmd,cwd=cwd,input=input_text,text=True,capture_output=True,timeout=timeout,env=env)

def trace(stderr: str) -> tuple[list[int],set[str]]:
    pairs=[(int(a),int(b)) for a,b in re.findall(r'^EPP_BRANCH\s+(\d+)\s+([01])$',stderr,re.M)]
    return [b for _,b in pairs],{f'{a}:{b}' for a,b in pairs}

def exact_cover(sets: list[set[str]], universe: set[str]) -> list[int]:
    if not universe: return []
    try:
        import pulp
        prob=pulp.LpProblem('minimum_tests',pulp.LpMinimize)
        x=[pulp.LpVariable(f'x{i}',cat='Binary') for i in range(len(sets))]
        prob += pulp.lpSum(x)
        for edge in universe: prob += pulp.lpSum(x[i] for i,s in enumerate(sets) if edge in s)>=1
        prob.solve(pulp.PULP_CBC_CMD(msg=False,timeLimit=60))
        if pulp.LpStatus[prob.status]=='Optimal': return [i for i,v in enumerate(x) if v.value()>0.5]
    except Exception: pass
    chosen=[]; left=set(universe)
    while left:
        i=max((i for i in range(len(sets)) if i not in chosen),key=lambda j:len(sets[j]&left))
        if not sets[i]&left: break
        chosen.append(i); left-=sets[i]
    return chosen

def candidate_cases(model: Path,cnip: Path,work: Path,maxloop:int,maxpaths:int):
    env=os.environ.copy(); root=cnip.parent
    env['LD_LIBRARY_PATH']=':'.join(str(root/x) for x in ('','C','common','libParser/z3/bin','lpsolve'))+':'+env.get('LD_LIBRARY_PATH','')
    a=run([str(cnip),'-q','--maxloop',str(maxloop),'--maxpaths',str(maxpaths),str(model)],work,timeout=45,env=env)
    if a.returncode: raise RuntimeError('cnip '+(a.stderr or a.stdout)[-500:])
    cases=[]
    for rf in sorted(work.glob('result_epp_model_*.txt')):
        text=rf.read_text(errors='replace')
        if not re.search(r'(?m)^feasible$',text): continue
        pid=int(re.search(r'_(\d+)\.txt$',rf.name).group(1)); vals={int(i):int32(v) for i,v in MODEL_ARRAY.findall(text)}
        pf=work/f'path_epp_model_{pid}.txt'; path=pf.read_text(errors='replace')
        expected=[0 if re.sub(r'\s+',' ',x.strip()).startswith('!(') else 1 for x in PATH_COND.findall(path)]
        cases.append({'path_id':pid,'values':vals,'expected':expected})
    return cases

def compile_traced(source:str,entry_re:re.Pattern[str],wrapper:str,work:Path,name:str):
    inst,n=instrument_function(source,entry_re); c=work/f'{name}.c'; c.write_text(inst+wrapper)
    b=run(['cc','-std=c11','-O0',str(c),'-o',name],work)
    if b.returncode: raise RuntimeError('compile '+b.stderr[-500:])
    return work/name,n

def one_problem(problem:Path,cnip:Path,maxloop:int,maxpaths:int)->dict:
    meta=json.loads((problem/'metadata.json').read_text()); errors=[]
    for sol in meta['solutions'][:3]:
        source=(problem/'solutions'/f"{sol['judge_id']}.c").read_text(errors='replace')
        try: model,token_hint=normalize(source)
        except Exception as e: errors.append(str(e)); continue
        try:
            with tempfile.TemporaryDirectory() as td:
                w=Path(td); mp=w/'model.c'; mp.write_text(model)
                cases=candidate_cases(mp,cnip,w,maxloop,maxpaths)
                if not cases: raise ValueError('no feasible paths')
                model_bin,model_branches=compile_traced(model,re.compile(r'\bint\s+epp_model\s*\([^)]*\)\s*\{'),
                    '\nint main(int argc,char**argv){int input[64]={0};for(int i=1;i<argc&&i<=64;i++)input[i-1]=atoi(argv[i]);return epp_model(input);}\n',w,'model_run')
                original_bin,original_branches=compile_traced(source,FUNC,'',w,'original_run')
                if model_branches!=original_branches: raise ValueError('branch-id mapping changed')
                generated=[]
                for c in cases:
                    last=max(c['values'].keys(),default=max(token_hint-1,0)); base=[c['values'].get(i,0) for i in range(min(last+1,64))]
                    if not base: base=[0]
                    mr=run([str(model_bin),*map(str,base)],w,timeout=5); mout,medges=trace(mr.stderr)
                    # A scanf site inside a bounded loop reuses one symbolic
                    # slot. Repeat the slot pattern so the original program
                    # receives the same abstract stream for concrete replay.
                    vals=(base*((64+len(base)-1)//len(base)))[:64]
                    stdin=' '.join(map(str,vals))+'\n'; rr=run([str(original_bin)],w,stdin,5); rout,redges=trace(rr.stderr)
                    generated.append({**c,'stdin':stdin,'model_edges':medges,'original_edges':redges,
                                      'model_match':set(mout)==set(c['expected']),
                                      'original_match':medges<=redges})
                # Loop-bound replay may contain fewer repeated outcomes than the
                # unbounded original execution. Coverage is a set of branch
                # edges, so retain a case exactly when normalized and original
                # programs cover the same edge IDs/outcomes.
                valid=[x for x in generated if x['original_match']]
                sets=[x['model_edges'] for x in valid]; target=set().union(*sets) if sets else set(); picked=exact_cover(sets,target)
                predicted_union=set().union(*(sets[i] for i in picked)) if picked else set()
                gen_union=set().union(*(valid[i]['original_edges'] for i in picked)) if picked else set()
                official=set(); official_runs=0
                for ip in sorted((problem/'tests').glob('*.in')):
                    rr=run([str(original_bin)],w,ip.read_text(),5); official |= trace(rr.stderr)[1]; official_runs+=1
                denom=2*original_branches
                return {'problem_id':meta['problem_id'],'judge_id':sol['judge_id'],'status':'ok','branches':original_branches,
                    'candidate_paths':len(cases),'validated_candidates':len(valid),'minimum_tests':len(picked),
                    'eppather_predicted_edges':len(predicted_union),'eppather_predicted_coverage':100*len(predicted_union)/denom if denom else 100,
                    'eppather_covered_edges':len(gen_union),'eppather_coverage':100*len(gen_union)/denom if denom else 100,
                    'official_tests':official_runs,'official_covered_edges':len(official),'official_coverage':100*len(official)/denom if denom else 100,
                    'coverage_prediction_correct':gen_union==predicted_union,
                    'path_replay_matches':sum(x['original_match'] for x in generated),
                    'generated_tests':[valid[i]['stdin'] for i in picked]}
        except Exception as e: errors.append(str(e)); continue
    return {'problem_id':meta['problem_id'],'status':'not_applicable','detail':' | '.join(errors[-5:])}

def main():
    ap=argparse.ArgumentParser(); ap.add_argument('--dataset',type=Path,required=True); ap.add_argument('--cnip',type=Path,required=True)
    ap.add_argument('--shard-index',type=int,default=0); ap.add_argument('--shard-count',type=int,default=1); ap.add_argument('--maxloop',type=int,default=3); ap.add_argument('--maxpaths',type=int,default=200); ap.add_argument('--output',type=Path,required=True)
    a=ap.parse_args(); problems=sorted((a.dataset/'problems').iterdir())[a.shard_index::a.shard_count]; rows=[]
    for p in problems:
        try:r=one_problem(p,a.cnip.resolve(),a.maxloop,a.maxpaths)
        except Exception as e:r={'problem_id':p.name,'status':'error','detail':str(e)}
        rows.append(r); print(json.dumps({k:v for k,v in r.items() if k!='generated_tests'},ensure_ascii=False),flush=True)
    a.output.parent.mkdir(parents=True,exist_ok=True); a.output.write_text(json.dumps(rows,ensure_ascii=False,indent=2)); return 0
if __name__=='__main__': raise SystemExit(main())
