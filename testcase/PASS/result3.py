import pandas as pd
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from scipy.stats import pearsonr
import numpy as np

# 1. 读取数据
df = pd.read_excel("all_results.xlsx")

# 2. 定义要分析的自变量和因变量
metrics = ["mems", "cond_count"]
times = ["time(ms)", "test0_time(ms)", "valgrind_test0_time(ms)"]

for metric in metrics:
    for t in times:
        # 过滤有效数据
        x = df[metric].values.reshape(-1, 1)
        y = df[t].values
        mask = (~pd.isna(x).flatten()) & (~pd.isna(y))
        x = x[mask]
        y = y[mask]
        if len(x) == 0: continue
        
        # 相关系数
        corr, pval = pearsonr(x.flatten(), y)
        
        # 线性回归
        model = LinearRegression()
        model.fit(x, y)
        r2 = model.score(x, y)
        k, b = model.coef_[0], model.intercept_
        
        # 画图
        plt.figure(figsize=(6, 4))
        plt.scatter(x, y, alpha=0.7, label='data')
        plt.plot(x, model.predict(x), color='red', label=f'fit: y={k:.3g}x+{b:.3g}')
        plt.xlabel(metric)
        plt.ylabel(t)
        plt.title(f"{metric} vs. {t}\nPearson r={corr:.3f}, p={pval:.3g}, $R^2$={r2:.3f}")
        plt.legend()
        plt.tight_layout()
        plt.savefig(f"{metric}_vs_{t}.pdf")
        plt.show()
        print(f"{metric} vs {t}:  Pearson r={corr:.3f}, p={pval:.3g}, R^2={r2:.3f}, 回归方程: y={k:.6g}x+{b:.6g}")

