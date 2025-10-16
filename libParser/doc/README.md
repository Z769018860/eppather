# 说明文档

## 简介

本工具功能主要是分析程序路径的可行性。其接受一个代表路径的字符串，返回其可行性。

当前版本为1.4.3版。

接口文档请点[这里](./doxygen/html/index.html)。

更新内容请点[这里](./doxygen/html/CHANGELOG.html)。

## 第三方库

linux下需要安装z3.

## 编译

### Linux

执行make命令，libParser.a即为生成的静态运行库。

### 其他OS

待补充

## 使用方法

所有的接口api写在driver.h中，在你的程序中包含driver.h，并实例化一个Driver对象以进行分析。可以参考下面的例子。

```C++
#include <iostream>
#include "driver.h"

using namespace std;
using namespace tool;

int main()
{
    string path_file = "./1.in";    // 路径文件的位置
    Driver driver;                  // 实例化Driver
    if (!driver.parsePath(path_file)) {   // 读取路径，返回0表示读取成功
        cout << "解析成功" << endl;
        cout << "树：" << endl;
        driver.printAST(cout);      // 打印读取的抽象语法树
        cout << "代码：" << endl;
        driver.printCode(cout);     // 打印读取的源代码
        
        cout << "正在分析可行性：" << endl;
        bool res = driver.feasible();   // 分析路径的可行性
        if (res) {
            cout << "路径可行！" << endl;
            cout << "模型：" << endl;
            driver.printModel(cout);    // 打印使路径可行的初始输入
            cout << "SMT2:" << endl;
            driver.printSMT2(cout);     // 打印使路径可行的输入空间，用SMT2表示
            cout << "mem:" << endl;
            driver.printMem(cout);      // 打印路径中读取数组的次数
        }
        else
            cout << "路径不可行！" << endl;
    }

    return 0;
}
```

关于api的详细介绍，请点击[这里](./doxygen/html/index.html)。

## 接受的输入

工具接受的输入是一个表示路径的字符串。表示路径的语法与C语言类似，如下面这个例子：

```C
int a, *b, c[10], **d[4];
struct A {
    int x, y[10];
    struct A *next;
};
a = *b;
b = &c[2];
struct A *p, q;
p = &q;
q.y[2] = 1;
@ p->y[2];
```

语法类似C，要先声明变量再使用，区别是代码不需要写在函数内。

### @语句

接受的输入是路径，因此**没有**```if,while,for```以及三目运算符等会产生分支的语句。取而代之的是形如```@ cond```的@语句，该语句表示路径进行所需的条件，如：

```C
if (cond)
    BB1
else
    BB2
```

可以形成两条路径，分别是

```C
@ cond;
BB1
```

```C
@ !cond;
BB2
```

### 限制的语法

相比于C语言，除了移除了上面说的会产生分支的语法外，工具还移除了下述语法或做了下述限制：

1. 移除编译命令，宏命令，包括```#include```；
2. 移除typedef；
3. 移除匿名结构体；
4. 移除函数声明；
5. 定义数组时长度必须要是自然数；
6. ......

## 备注

当前版本为1.4，版本支持数组、指针、结构体的路径分析。

注意事项：

1. 支持赋值语句的返回值，但是不建议使用。因为不符合编程规范，同时可能产生未知错误；
2. 当前版本还不支持```float,double,char```等类型，也不支持```const,mutable,unsigned```等类型限定符；
3. ```int```型的大小默认为64位；
4. ......
