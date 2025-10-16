import os
import re

# 插桩函数，向 .c 文件插入 KLEE 插桩代码
def insert_klee_instrumentation(input_file, output_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()

    # 处理每一行，进行插桩操作
    modified_lines = []
    for line in lines:
        # 插入 klee_make_symbolic 到变量声明和赋值的位置
        if re.match(r'.*\bint\b.*;', line):  # 检测int类型的变量声明
            # 提取变量名
            variables = re.findall(r'\bint\b\s+([^;]+);', line)
            for var in variables:
                # 替换每个变量为 klee_make_symbolic
                modified_lines.append(f'    klee_make_symbolic(&{var}, sizeof({var}), "{var}");\n')
        
        # 插入 //klee_assume 到 range 假设的位置
        if 'klee_make_symbolic' in line:  # 在插入了klee_make_symbolic之后插入 //klee_assume
            var_name = re.findall(r'klee_make_symbolic\(&(\w+),', line)
            if var_name:
                var_name = var_name[0]
                modified_lines.append(f'    //klee_assume({var_name} >= 0 && {var_name} <= 1000);\n')
        
        # 添加原始行
        modified_lines.append(line)

    # 写入插桩后的文件
    with open(output_file, 'w') as f:
        f.writelines(modified_lines)

# 批量处理当前目录下所有的 .c 文件
def process_all_c_files():
    # 获取当前目录下所有的 .c 文件
    current_directory = os.getcwd()
    files = [f for f in os.listdir(current_directory) if f.endswith('.c')]

    # 确保输出目录存在
    output_directory = os.path.join(current_directory, 'kleetest')
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)

    # 对每个 .c 文件进行插桩
    for file in files:
        input_file = os.path.join(current_directory, file)
        output_file = os.path.join(output_directory, file)

        print(f"Processing file: {input_file}")
        insert_klee_instrumentation(input_file, output_file)
        print(f"Inserted KLEE instrumentation into: {output_file}")

# 运行批量处理函数
process_all_c_files()
