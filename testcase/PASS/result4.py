import pandas as pd
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from scipy.stats import pearsonr
import numpy as np

# 读取数据
df = pd.read_excel("all_results.xlsx")

# 支持科学计数法小数
df["time(ms)"] = pd.to_numeric(df["time(ms)"], errors='coerce')
df["test0_time(ms)"] = pd.to_numeric(df["test0_time(ms)"], errors='coerce')
df["valgrind_test0_time(ms)"] = pd.to_numeric(df["valgrind_test0_time(ms)"], errors='coerce')

metrics = ["mems", "cond_count"]
times = ["time(ms)", "test0_time(ms)", "valgrind_test0_time(ms)"]

# 每个程序分组
for program, group in df.groupby("filename"):
    print(f"\n========== {program} ==========")
    for metric in metrics:
        for t in times:
            x = group[metric].values.reshape(-1, 1)
            y = group[t].values
            mask = (~pd.isna(x).flatten()) & (~pd.isna(y))
            x = x[mask]
            y = y[mask]
            if len(x) < 3:
                continue  # 点太少不分析

            # 皮尔逊相关系数
            corr, pval = pearsonr(x.flatten(), y)
            # 线性回归
            model = LinearRegression()
            model.fit(x, y)
            r2 = model.score(x, y)
            k, b = model.coef_[0], model.intercept_
            
            # 可视化
            plt.figure(figsize=(5, 3.5))
            plt.scatter(x, y, alpha=0.8, label='data')
            plt.plot(x, model.predict(x), color='red', label=f'fit: y={k:.2g}x+{b:.2g}')
            plt.xlabel(metric)
            plt.ylabel(t)
            plt.title(f"{program}: {metric} vs. {t}\nPearson r={corr:.3f}, $R^2$={r2:.3f}")
            plt.legend()
            plt.tight_layout()
            plt.savefig(f"{program}_{metric}_vs_{t}.pdf")
            plt.close()
            print(f"{metric} vs {t}:  r={corr:.3f}, p={pval:.2g}, R^2={r2:.3f}, y={k:.3g}x+{b:.3g}")

print("\n每个PDF为某个程序/某种关系的矢量趋势图。相关系数和拟合参数见控制台输出。")
