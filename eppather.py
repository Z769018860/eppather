import os
import subprocess
import re
import csv
import shutil
import time  # 引入time模块来计算运行时间

# 设置根目录和目标文件夹
base_dir = './testcase/eppather'
output_file = 'results.csv'
testresult_dir = 'testresult'

# 获取eppather目录下的所有.c文件
c_files = [f for f in os.listdir(base_dir) if f.endswith('.c')]

# 定义一个函数来提取compute.py的输出结果中的Objective value和Coverage percent
def extract_results(matrix_file):
    try:
        # 运行python compute.py matrix2.txt，获取输出
        result = subprocess.check_output(['python', 'compute.py', matrix_file]).decode('utf-8')
        
        # 使用正则表达式提取Objective value和Coverage percent
        objective_value = re.search(r'Objective value:\s+([\d.]+)', result)
        coverage_percent = re.search(r'Coverage percent:\s+([\d.]+)%', result)
        
        if objective_value and coverage_percent:
            return float(objective_value.group(1)), float(coverage_percent.group(1))
        else:
            return None, None
    except subprocess.CalledProcessError as e:
        print(f"Error during running compute.py for {matrix_file}: {e}")
        return None, None

# 准备写入CSV文件
with open(output_file, mode='w', newline='') as csvfile:
    fieldnames = ['C File', 'Objective Value', 'Coverage Percent', 'Error', 'Run Time (s)']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    
    writer.writeheader()  # 写入表头
    
    for c_file in c_files:
        c_file_path = os.path.join(base_dir, c_file)
        error_message = ''  # 默认没有错误
        
        # 记录开始时间
        start_time = time.time()
        
        try:
            print(f"Processing {c_file}...")
            result = subprocess.run(['./cnip', '-q', c_file_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            
            # 如果发生错误，输出到debug.txt并记录错误信息
            if result.returncode != 0:
                error_message = f"Error executing './cnip' for {c_file}: {result.stderr}"
                with open('debug.txt', 'a') as debug_file:
                    debug_file.write(error_message + '\n')
            
            # 提取计算结果
            matrix_file = 'matrix2.txt'
            objective_value, coverage_percent = extract_results(matrix_file)
            
            # 如果提取到结果，则写入CSV
            if objective_value is not None and coverage_percent is not None:
                end_time = time.time()  # 记录结束时间
                run_time = end_time - start_time  # 计算运行时间
                writer.writerow({'C File': c_file, 'Objective Value': objective_value, 'Coverage Percent': coverage_percent, 'Error': error_message, 'Run Time (s)': run_time})
            else:
                error_message = f"Error extracting results from {matrix_file}."
                end_time = time.time()  # 记录结束时间
                run_time = end_time - start_time  # 计算运行时间
                writer.writerow({'C File': c_file, 'Objective Value': '', 'Coverage Percent': '', 'Error': error_message, 'Run Time (s)': run_time})
            
            # 创建对应的结果目录
            foldername = os.path.splitext(c_file)[0]
            result_dir = os.path.join(testresult_dir, foldername)
            os.makedirs(result_dir, exist_ok=True)
            
            # 移动所有生成的txt文件到结果目录
            for file in os.listdir('.'):
                if file.endswith('.txt') and file != 'CMakeCache.txt' and file != 'CMakeLists.txt':
                    shutil.move(file, os.path.join(result_dir, file))
            
            # 删除matrix2.txt文件，以便下次循环使用
            if os.path.exists(matrix_file):
                os.remove(matrix_file)
        
        except Exception as e:
            # 捕获其他错误并记录
            error_message = f"Error processing {c_file}: {str(e)}"
            print(error_message)
            with open('debug.txt', 'a') as debug_file:
                debug_file.write(error_message + '\n')
            
            # 记录错误信息到CSV文件
            end_time = time.time()  # 记录结束时间
            run_time = end_time - start_time  # 计算运行时间
            writer.writerow({'C File': c_file, 'Objective Value': '', 'Coverage Percent': '', 'Error': error_message, 'Run Time (s)': run_time})

print(f"Results have been written to {output_file}")
