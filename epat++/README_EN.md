# EPAT++

Data Structure Protocol for the EPAT++ Tool.

## Introduction

EPAT++ is a program path feasibility analysis tool. It accepts a program path as input and outputs the feasibility analysis results for that path.

The current version is 1.5.0.

For the update log, please click [here](CHANGELOG.md).

## Installation

Two main installation methods are provided:

### CMake

If your project is built with CMake, you can copy the EPAT++ folder to your project directory, add the EPAT++ subdirectory using the CMake `add_subdirectory` command, and then link EPAT++ to your project using the `target_link_libraries` command. You can refer to the example below for specifics.

Directory structure:

```text
project
├── epat++
│   ├── ...
│   └── ...
├── main.cpp
└── CMakeLists.txt
```

CMakeLists.txt:

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

### Static Library Files

Compile EPAT++, then copy the header files and library files to your project directory for use. The compilation command is as follows (execute in the main EPAT++ directory):

```bash
mkdir build
cd build
cmake ..
make -j 10
```

The compilation requires the environment to support at least the C++17 standard. TODO: Installation command TODO: Executable files

## Usage Instructions
First, you need to construct the program path through the EPAT-protocol interface, which is detailed in the EPAT-protocol documentation:

```c++
#include "stmt.h"
auto root = epat::Root::create();
*root << epat::VarDecl::create("a", epat::ArrayType::create(epat::IntType::create(), 10));
      << epat::SignStmt::create(epat::DeclRefExpr::create(root->getValueDecl("a")));
```

You can also call the interface to analyze C11 standard C code or CPath code:

```c++
#include "stmt.h"
...
std::string path = R"(
    int a[10], x;
    @(a[x]==x);
)";
auto root = epat::Root::fromString(path);
```

Then, call the EPAT++ interface for solving:

```c++
#include "solver.h"
...
auto solver = epat::Solver::create(move(root));
auto result = solver->feasible();
std::cout << result << std::endl;
```

## Notes
Known issues:
