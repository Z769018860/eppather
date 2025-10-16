import os
import re
import pandas as pd
from pathlib import Path
import subprocess

def extract_g_results(output):
    # 提取最大路径、MEMS和DP时间
    path_lines = []
    mems = None
    time_cost = None
    in_path = False
    for line in output.splitlines():
        if "[MAX MEMS PATH]:" in line:
            in_path = True
            continue
        if in_path:
            if line.startswith("MEMS:"):
                mems = int(re.search(r'\d+', line).group())
                in_path = False
                continue
            path_lines.append(line)
        if "[DP TIME COST]:" in line:
            m = re.search(r"([0-9.]+)", line)
            if m:
                time_cost = float(m.group(1))
    return "\n".join(path_lines), mems, time_cost

def extract_f_results(output):
    # 提取averagemems, DFS max/min mems, DFS TIME
    avgmems = None
    dfs_time = None
    maxmems = None
    minmems = None
    for line in output.splitlines():
        if "[averagemem]:" in line:
            avgmems = int(re.search(r'\d+', line).group())
        if "[DFS TIME COST]:" in line:
            m = re.search(r"([0-9.]+)", line)
            if m:
                dfs_time = float(m.group(1))
        if "[DFS MAX MEMS]:" in line:
            maxmems = int(re.search(r'\d+', line).group())
        if "[DFS MIN MEMS]:" in line:
            minmems = int(re.search(r'\d+', line).group())
    return avgmems, maxmems, minmems, dfs_time

results = []
base_dir = Path('testcase/WCA')
for f in sorted(base_dir.glob("*.c")):
    fname = str(f)
    # 1. 执行 -g 获取最大路径和 mems
    g_proc = subprocess.run(['./cnip', '-g', fname], capture_output=True, text=True)
    path_str, mems, dp_time = extract_g_results(g_proc.stdout)
    # 2. 执行 -f 获取DFS的平均、最大、最小mems和DFS时间
    f_proc = subprocess.run(['./cnip', '-f', fname], capture_output=True, text=True)
    avgmems, maxmems, minmems, dfs_time = extract_f_results(f_proc.stdout)
    results.append({
        "filename": f.name,
        "max_mem_path": path_str,
        "max_mems": mems,
        "dp_time_cost(s)": dp_time,
        "dfs_avgmems": avgmems,
        "dfs_maxmems": maxmems,
        "dfs_minmems": minmems,
        "dfs_time_cost(s)": dfs_time,
    })

# 输出成Excel或csv
df = pd.DataFrame(results)
df.to_excel("cnip_summary.xlsx", index=False)
print(df)
