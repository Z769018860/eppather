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
    # mems 和 test0_time(ms) 的散点趋势图
    plt.figure(figsize=(10, 6))
    mems = df['mems'].values  # 转换为numpy数组
    test0_time = df['test0_time(ms)'].values  # 转换为numpy数组
    plt.scatter(mems, test0_time, alpha=0.5)
    z = np.polyfit(mems, test0_time, 1)
    p = np.poly1d(z)
    plt.plot(mems, p(mems), "r--")  # 绘制趋势线
    plt.xlabel('Memory Usage (mems)')
    plt.ylabel('Execution Time (test0_time ms)')
    plt.title('Memory Usage vs. Execution Time (test0)')
    plt.grid(True)
    plt.savefig('mems_vs_test0_time.png')
    plt.show()

    # mems 和 valgrind_test0_time(ms) 的散点趋势图
    plt.figure(figsize=(10, 6))
    valgrind_test0_time = df['valgrind_test0_time(ms)'].values  # 转换为numpy数组
    plt.scatter(mems, valgrind_test0_time, alpha=0.5)
    z_valgrind = np.polyfit(mems, valgrind_test0_time, 1)
    p_valgrind = np.poly1d(z_valgrind)
    plt.plot(mems, p_valgrind(mems), "g--")  # 绿色趋势线
    plt.xlabel('Memory Usage (mems)')
    plt.ylabel('Valgrind Execution Time (ms)')
    plt.title('Memory Usage vs. Valgrind Execution Time')
    plt.grid(True)
    plt.savefig('mems_vs_valgrind_test0_time.png')
    plt.show()

    # length_of_path 和 test0_time(ms) 的散点趋势图
    plt.figure(figsize=(10, 6))
    length_of_path = df['length_of_path'].values  # 转换为numpy数组
    plt.scatter(length_of_path, test0_time, alpha=0.5)
    z_path = np.polyfit(length_of_path, test0_time, 1)
    p_path = np.poly1d(z_path)
    plt.plot(length_of_path, p_path(length_of_path), "r--")
    plt.xlabel('Path Length')
    plt.ylabel('Execution Time (test0_time ms)')
    plt.title('Path Length vs. Execution Time (test0)')
    plt.grid(True)
    plt.savefig('path_length_vs_test0_time.png')
    plt.show()

    # length_of_path 和 valgrind_test0_time(ms) 的散点趋势图
    plt.figure(figsize=(10, 6))
    plt.scatter(length_of_path, valgrind_test0_time, alpha=0.5)
    z_valgrind_path = np.polyfit(length_of_path, valgrind_test0_time, 1)
    p_valgrind_path = np.poly1d(z_valgrind_path)
    plt.plot(length_of_path, p_valgrind_path(length_of_path), "g--")  # 绿色趋势线
    plt.xlabel('Path Length')
    plt.ylabel('Valgrind Execution Time (ms)')
    plt.title('Path Length vs. Valgrind Execution Time (test0)')
    plt.grid(True)
    plt.savefig('path_length_vs_valgrind_test0_time.png')
    plt.show()
