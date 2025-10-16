import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import matplotlib

# 设置 Matplotlib 字体，以支持中文显示
matplotlib.rcParams['font.sans-serif'] = ['SimHei']  # 使用黑体显示中文
matplotlib.rcParams['axes.unicode_minus'] = False  # 正常显示负号

# 加载Excel文件到DataFrame
df = pd.read_excel('result.xlsx')

# 检查所需的列是否存在
required_columns = ['mems', 'test0_time(ms)', 'valgrind_test0_time(ms)', 'length_of_path']
missing_columns = [col for col in required_columns if col not in df.columns]
if missing_columns:
    print("缺少以下必要列：", missing_columns)
else:
    # 定义一个函数来根据路径长度变化20%的规则划分区间
    def define_length_groups(lengths, max_variation=0.2):
        sorted_lengths = sorted(lengths.unique())
        groups = []
        start = sorted_lengths[0]

        for length in sorted_lengths:
            if length > start * (1 + max_variation):
                groups.append((start, length / (1 + max_variation)))
                start = length

        if not groups or groups[-1][1] != sorted_lengths[-1]:
            groups.append((start, sorted_lengths[-1]))

        return groups

    # 计算路径长度区间
    groups = define_length_groups(df['length_of_path'])

    # 对每个路径长度范围进行分析
    for lower_bound, upper_bound in groups:
        subset = df[(df['length_of_path'] >= lower_bound) & (df['length_of_path'] <= upper_bound)]

        # mems 和 test0_time(ms) 的散点趋势图
        plt.figure(figsize=(10, 6))
        mems = subset['mems'].values  # 转换为numpy数组
        test0_time = subset['test0_time(ms)'].values  # 转换为numpy数组
        plt.scatter(mems, test0_time, alpha=0.5, label='Test0 Time')
        z_test = np.polyfit(mems, test0_time, 1)
        p_test = np.poly1d(z_test)
        plt.plot(mems, p_test(mems), "r--", label='Trend Line')

        # mems 和 valgrind_test0_time(ms) 的散点趋势图
        valgrind_test0_time = subset['valgrind_test0_time(ms)'].values  # 转换为numpy数组
        plt.scatter(mems, valgrind_test0_time, alpha=0.5, color='green', label='Valgrind Test0 Time')
        z_valgrind = np.polyfit(mems, valgrind_test0_time, 1)
        p_valgrind = np.poly1d(z_valgrind)
        plt.plot(mems, p_valgrind(mems), "g--", label='Valgrind Trend Line')

        plt.xlabel('Memory Usage (mems)')
        plt.ylabel('Execution Time (ms)')
        plt.title(f'Memory Usage vs. Execution Time for Path Lengths [{lower_bound:.2f}-{upper_bound:.2f}]')
        plt.legend()
        plt.grid(True)
        plt.savefig(f'mems_vs_execution_time_{lower_bound:.2f}_{upper_bound:.2f}.png')
        plt.show()
