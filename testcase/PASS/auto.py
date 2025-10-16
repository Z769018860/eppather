import subprocess
import pandas as pd
import os
import shutil
import glob

file_name = input("请输入 C 源文件名（如 example.c）: ").strip()
base_name = os.path.splitext(file_name)[0]
c_pass_name = file_name + "_pass.c"
param_file = base_name + ".txt"
output_file = "results.xlsx"

# 编译
compile0 = subprocess.run(["clang", file_name, "-o", "test0.out"])
if compile0.returncode != 0:
    print(f"编译 {file_name} 失败！")
    exit(1)
if not os.path.exists(c_pass_name):
    print(f"未找到插桩后文件 {c_pass_name}，请先插桩生成。")
    exit(1)
compile1 = subprocess.run(["clang", c_pass_name, "-o", "test.out"])
if compile1.returncode != 0:
    print(f"编译 {c_pass_name} 失败！")
    exit(1)
print(f"{file_name} 和 {c_pass_name} 均已成功编译。")
print(f"参数输入文件默认为 {param_file}")

def run_test(params, index):
    input_str = " ".join(map(str, params)) + "\n"
    times = []
    test0_times = []
    valgrind_test0_times = []
    path_filename = f"path_{index}.txt"
    
    for _ in range(5):
        # 插桩版 test.out
        result = subprocess.run(["./test.out"], input=input_str, text=True, capture_output=True)
        output = result.stdout
        
        path_lines = []
        stats = {}
        capturing_path = False
        
        for line in output.split("\n"):
            if line.startswith("Path:"):
                capturing_path = True
                path_lines.append(line)
            elif capturing_path:
                path_lines.append(line)
                if line.strip() == "END":
                    capturing_path = False
                    continue
            if "Total path length:" in line:
                stats["path_length"] = int(line.split(": ")[1])
            elif "Total memory accesses:" in line:
                stats["mems"] = int(line.split(": ")[1])
            elif "Total conditional statements:" in line:
                stats["cond_count"] = int(line.split(": ")[1])
            elif "Execution time:" in line:
                times.append(float(line.split(": ")[1].split(" ")[0]))
        
        with open(path_filename, "w") as path_file:
            path_file.write("\n".join(path_lines))
        
        # 原版 test0.out
        test0_result = subprocess.run(["./test0.out"], input=input_str, text=True, capture_output=True)
        for line in test0_result.stdout.split("\n"):
            if "Execution time:" in line:
                test0_times.append(float(line.split(": ")[1].split(" ")[0]))
        
        # 原版 valgrind
        valgrind_test0_result = subprocess.run(["valgrind", "--tool=callgrind", "./test0.out"], input=input_str, text=True, capture_output=True)
        combined_output = valgrind_test0_result.stdout + "\n" + valgrind_test0_result.stderr
        for line in combined_output.split("\n"):
            if "Execution time:" in line:
                valgrind_test0_times.append(float(line.split(": ")[1].split(" ")[0]))
    
    avg_time = sum(times) / len(times) if times else 0.0
    avg_test0_time = sum(test0_times) / len(test0_times) if test0_times else 0.0
    avg_valgrind_test0_time = sum(valgrind_test0_times) / len(valgrind_test0_times) if valgrind_test0_times else 0.0
    
    return params + [path_filename, stats.get("path_length", 0), stats.get("mems", 0), stats.get("cond_count", 0),
                     f"{avg_time:.6f}", f"{avg_test0_time:.6f}", f"{avg_valgrind_test0_time:.6f}"]

# 读取参数并批量测试
data = []
with open(param_file, "r") as f:
    for index, line in enumerate(f):
        parts = line.strip().split()
        if parts:
            params = list(map(int, parts))
            data.append(run_test(params, index))

columns = [f"param_{i+1}" for i in range(len(data[0]) - 7)] + [
    "path_file", "length_of_path", "mems", "cond_count",
    "time(ms)", "test0_time(ms)", "valgrind_test0_time(ms)"
]
df = pd.DataFrame(data, columns=columns)
df.to_excel(output_file, index=False)

print("Batch execution completed. Results saved in results.xlsx.")

# 自动归档
folder_name = base_name
if not os.path.exists(folder_name):
    os.makedirs(folder_name)

for file in glob.glob("path_*.txt"):
    shutil.move(file, os.path.join(folder_name, file))

if os.path.exists(output_file):
    shutil.move(output_file, os.path.join(folder_name, output_file))

for exec_file in ["test.out", "test0.out"]:
    if os.path.exists(exec_file):
         shutil.move(exec_file, os.path.join(folder_name, exec_file))

print("All generated files and executables have been moved to folder:", folder_name)

for file in glob.glob("callgrind.out.*"):
    os.remove(file)

print("All callgrind.out.* files have been deleted.")
