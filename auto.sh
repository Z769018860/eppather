#!/bin/bash

# 构建项目
echo "开始构建项目..."
if cmake CMakeLists.txt && make -j 4; then
    echo "项目构建成功。"
else
    echo "项目构建失败，退出脚本。"
    exit 1
fi

#删除之前所有的txt文件
find . -maxdepth 1 -type f -name "*.txt" ! -name "CMakeCache.txt" ! -name "CMakeLists.txt" -exec rm -f {} \;

# 获取testcase目录下的所有.c文件
testcases=$(find testcase -type f -name "*.c")

# 测试案例总数
total=$(echo "$testcases" | wc -l | tr -d ' ')
# 已处理的测试案例数
count=0

# 批量执行测试
for testcase in $testcases; do
    count=$(expr $count + 1)
    echo "处理进度：$count / $total"
    filename=$(basename "$testcase")
    foldername="${filename%.*}"

    # 使用GDB执行测试命令，并将输出重定向到debug.txt
    gdb -batch -ex "set pagination off" -ex "run -f \"$testcase\"" -ex "quit" ./cnip >> debug.txt 2>&1
    result=$?
    if [ $result -ne 0 ]; then
        echo "Warning: '$testcase' 执行过程中出现错误。" >> debug.txt
    fi

    # 创建对应的结果目录，如果不存在
    mkdir -p "testresult/$foldername"

    # 移动生成的.txt文件到对应目录，排除CMakeCache.txt和CMakeLists.txt
    find . -maxdepth 1 -type f -name "*.txt" ! -name "CMakeCache.txt" ! -name "CMakeLists.txt" -exec mv {} "testresult/$foldername/" \;

    echo "'$testcase' 测试完成，结果已移动。"
done

echo "所有测试案例处理完成。"