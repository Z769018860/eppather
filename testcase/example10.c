#include <stdio.h>
#include <ctype.h>
#include <klee/klee.h>

#define NUMBER '0'  // 信号，表示一个数字

// 从符号化的输入数组中提取下一个操作符或操作数
int getop(char s[], int *index) {
    int i = 0;
    char c;

    // 跳过空白符
    while ((c = s[(*index)++]) == ' ' || c == '\t')
        ;

    // 如果是操作符则直接返回
    if (!isdigit(c) && c != '.') {
        return c;
    }

    // 收集整数部分
    if (isdigit(c)) {
        s[i++] = c;
        while (isdigit(c = s[(*index)++])) {
            s[i++] = c;
        }
    }

    // 如果读取到小数点，则继续收集小数部分
    if (c == '.') {
        s[i++] = c;
        while (isdigit(c = s[(*index)++])) {
            s[i++] = c;
        }
    }

    s[i] = '\0';  // 将数字字符串结束符加上
    (*index)--;   // 将多读的字符返回索引
    return NUMBER;
}

int main() {
    char s[100];
    int index = 0;

    // 将输入数组和索引声明为符号变量
    klee_make_symbolic(s, sizeof(s), "s");
    klee_make_symbolic(&index, sizeof(index), "index");

    // 限制 index 在合理范围内
    //klee_assume(index >= 0 && index < 100);

    int type = getop(s, &index);

    // 输出识别的类型
    if (type == NUMBER) {
        printf("识别到数字：%s\n", s);
    } else {
        printf("识别到运算符：%c\n", type);
    }

    return 0;
}
