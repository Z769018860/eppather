import numpy as np

# 样本数据
lines = [2684850,27886,2684850,27886,269641,17,23,25,28,11,25,13,53,29,16,27,27,30,30]

# Provided data
mems = [1596662, 16240, 256,256,156878, 10, 14, 36, 14, 2, 17, 4, 44,18,6,14,4,36,12]
run_time = [34.964, 5.42,2.32,2.264,7.922, 1.606, 1.64, 1.233, 1.401, 1.201, 1.686, 1.282, 1.556,1.428,1.024,1.446,1.202,1.784,1.318]

# Calculate the correlation coefficient
correlation_coefficient = np.corrcoef(mems, run_time)[0, 1]
correlation_coefficient2 = np.corrcoef(lines, run_time)[0, 1]

print("Correlation coefficient(mems):", correlation_coefficient)
print("Correlation coefficient2(lines):", correlation_coefficient2)