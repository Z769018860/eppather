# epat-protocol
data structure protocol for the EPAT++ tool.
## 简介
epat-protocol定义了epat++可接受的数据结构和协议，并且可以作为语法分析前端使用。
## 编译
将epat-protocol文件夹复制到你的项目中，用cmake的add_subdirectory命令编译，然后用target_link_libraries命令将epat-protocol链接到你的项目中。下面是一个例子:
```cmake
add_subdirectory (epat-protocol)
add_executable (your_program test.cpp)
target_include_directories (your_program PRIVATE "../epat-protocol/include")
target_link_libraries (your_program PRIVATE epat-protocol)
```
编译要求环境支持C++17标准。
TODO: 安装命令
TODO: 可执行文件
## 使用
你可以通过调用epat-protocol的接口来构造代表数据结构的路径：
```c++
#include "stmt.h"
auto root = epat::Root::create();
*root << epat::VarDecl::create("a", epat::ArrayType::create(epat::IntType::create(), 10));
      << epat::SignStmt::create(epat::DeclRefExpr::create(root->getValueDecl("a")));
```
也可以调用接口来分析C11标准的C语言代码或CPath代码：
```c++
#include "reader.h"
std::string path = R"(
    int a[10], x;
    @(a[x]==x);
)";
auto parser = epat::Parser(path);
auto root = parser.getRoot();
```
## CPath
在C11的基础上修改，如果不含有分支语句，那么是一条路径，可以被epat++接受。否则是一个C程序。
增加了两个特性：
1.允许顶层语句；
2.@语法，用于表示路径约束。
下面是不支持的语法：
1.变长参数列表
2.designation
3.switch
4.do-while
5.goto
