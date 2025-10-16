#!/bin/bash

# 创建结果目录保存所有分析结果
RESULT_DIR="./result_zhanglw"

# 定义 .bc 文件的存储路径
BC_DIR="/home/klee/test_zhanglw/testresult"

# 清空 BC_DIR 目录中的所有内容
rm -rf $BC_DIR/*
mkdir -p $BC_DIR  # 确保目录存在

# 打印表头
echo -e "File Name\tInstructions\tCovered Instructions\tTime(s)\tICov(%)\tBCov(%)\tICount\tTSolver(%)"

# 计数器，用于创建 klee-out-x 目录
file_counter=0

# 遍历当前目录下的所有 .c 文件
for c_file in *.c; do
    if [ -f "$c_file" ]; then  # 使用 [ ... ] 代替 [[ ... ]]
        echo "Processing file: $c_file"

        # 定义输出的 .bc 文件路径
        bc_file="$BC_DIR/test.bc"

        # 编译 C 文件为 LLVM 位码文件（.bc）并指定输出路径
        clang -emit-llvm -g -c "$c_file" -o "$bc_file" || { echo "Failed to compile $c_file"; continue; }

        # 运行 KLEE 并限制时间为 1 秒
        klee_out_dir="$BC_DIR/klee-out-$file_counter"  # 定义 klee 输出目录
        klee --max-time 1 "$bc_file"&> /dev/null

        # 检查 KLEE 运行是否生成了 stats 文件
        stats_file="$klee_out_dir/run.stats"
        if [ -f "$stats_file" ]; then  # 使用 [ ... ] 代替 [[ ... ]]
            # 直接输出 klee-stats 终端的所有内容
            echo "KLEE analysis for $c_file:"
            klee-stats "$klee_out_dir" 2>/dev/null

        else
            echo -e "$c_file\tError\tError\tError\tError\tError\tError"
            echo "No stats file generated for $c_file."
        fi

        # 删除临时生成的 .bc 文件
        rm -f "$bc_file"

        # 更新文件计数器
        ((file_counter++))
    fi
done

echo "Analysis complete."
