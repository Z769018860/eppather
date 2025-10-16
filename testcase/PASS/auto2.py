import os
import pandas as pd
import glob

# 当前目录所有文件夹（不含隐藏文件夹）
folders = [f for f in os.listdir('.') if os.path.isdir(f) and not f.startswith('.')]

all_data = []

for folder in folders:
    xlsx_path = os.path.join(folder, 'results.xlsx')
    if os.path.exists(xlsx_path):
        df = pd.read_excel(xlsx_path)
        df['filename'] = folder
        all_data.append(df)

if not all_data:
    print("未找到任何 results.xlsx 文件。")
else:
    merged = pd.concat(all_data, ignore_index=True)
    # 建议将 filename 列放到第一列
    cols = ['filename'] + [c for c in merged.columns if c != 'filename']
    merged = merged[cols]
    merged.to_excel("all_results.xlsx", index=False)
    print(f"已合并所有 results.xlsx 到 all_results.xlsx，共 {len(merged)} 行。")
