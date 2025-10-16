# epat++

data structure protocol for the EPAT++ tool.

## 简介

epat++是一个程序路径可行性分析工具。它接受一条程序路径作为输入，输出该路径的可行性分析结果。

当前版本为1.5.0。

更新日志请点[这里](CHANGELOG.md)。

## 安装

主要提供了两种安装方式：

### CMake

如果你的项目使用cmake构建的，你可以将epat++文件夹复制到你的项目目录，用cmake的add_subdirectory命令添加epat++子目录，然后用target_link_libraries命令将epat++链接到你的项目中。具体可以参照下面的示例。

目录结构：

```text
project
├── epat++
│   ├── ...
│   └── ...
├── main.cpp
└── CMakeLists.txt
```

CMakeLists.txt：

```cmake
# project/CMakeLists.txt
cmake_minimum_required(VERSION 3.12)
project("demo" VERSION 0.0.0)

add_subdirectory("epat++")
add_executable(demo "main.cpp")
target_link_libraries(demo "libepat++")
target_include_directories(demo PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/epat++/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/epat++/epat-protocol/include"
)
target_compile_features(demo PRIVATE cxx_std_17)
if(CMAKE_SYSTEM_NAME MATCHES "[Ww]indows")
  string(REPLACE ".lib" ".dll" Z3_DLL ${Z3_LIB})
  add_custom_command(TARGET demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${Z3_DLL}
    $<TARGET_FILE_DIR:demo>
  )
endif()
```

### 静态库文件

编译epat++，然后将头文件和库文件复制到你的工程目录下使用，编译命令如下（在epat++主目录下执行）:

```bash
mkdir build
cd build
cmake ..
make -j 10
```

编译要求环境支持最低C++17标准。
TODO: 安装命令
TODO: 可执行文件

## 使用说明

首先你需要通过epat-protocol的接口来构造程序路径，epat-protocol的[文档](epat-protocol/README.md)中有详细介绍：

```c++
#include "stmt.h"
auto root = epat::Root::create();
*root << epat::VarDecl::create("a", epat::ArrayType::create(epat::IntType::create(), 10));
      << epat::SignStmt::create(epat::DeclRefExpr::create(root->getValueDecl("a")));
```

也可以调用接口来分析C11标准的C语言代码或CPath代码：

```c++
#include "stmt.h"
...
std::string path = R"(
    int a[10], x;
    @(a[x]==x);
)";
auto root = epat::Root::fromString(path);
```

然后调用epat++的接口进行求解：

```c++
#include "solver.h"
...
auto solver = epat::Solver::create(move(root));
auto result = solver->feasible();
std::cout << result << std::endl;
```

## 备注

已知问题：

1. 无法处理结构体作为右值的情形；
2. 无法处理浮点数，会被转换为整数；
