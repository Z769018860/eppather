#!/bin/bash

# 检查依赖
if ! command -v klee &> /dev/null; then
    echo "KLEE is not installed. Please install KLEE before running this script."
    exit 1
fi

# 创建临时目录保存结果
RESULT_DIR="klee_results"
mkdir -p $RESULT_DIR

# 初始化 CSV 文件
CSV_FILE="klee_analysis.csv"
echo "File Name,Instructions,Covered Instructions,Time" > $CSV_FILE

# 遍历当前目录下的所有 .c 文件
for c_file in *.c; do
    if [[ -f "$c_file" ]]; then
        echo "Processing file: $c_file"

        # 编译 C 文件为 LLVM 位码文件（.bc）
        bc_file="${c_file%.c}.bc"
        clang -emit-llvm -c "$c_file" -o "$bc_file" || { echo "Failed to compile $c_file"; continue; }

        # 运行 KLEE 并限制时间为 1 秒
        klee_out_dir="$RESULT_DIR/${c_file%.c}_klee"
        klee --max-time=1 --output-dir="$klee_out_dir" "$bc_file" &> /dev/null

        # 检查 KLEE 运行是否生成了 stats 文件
        stats_file="$klee_out_dir/run.stats"
        if [[ -f "$stats_file" ]]; then
            # 提取 stats 数据：指令数、覆盖指令数、运行时间
            instructions=$(grep "^Instructions" "$stats_file" | awk '{print $2}')
            covered_instructions=$(grep "^CoveredInstructions" "$stats_file" | awk '{print $2}')
            time=$(grep "^WallTime" "$stats_file" | awk '{print $2}')

            # 添加数据到 CSV 文件
            echo "$c_file,$instructions,$covered_instructions,$time" >> $CSV_FILE
        else
            echo "$c_file,Error,Error,Error" >> $CSV_FILE
            echo "No stats file generated for $c_file."
        fi

        # 删除临时生成的 .bc 文件
        rm -f "$bc_file"
    fi
done

echo "Analysis complete. Results are saved in $CSV_FILE."
