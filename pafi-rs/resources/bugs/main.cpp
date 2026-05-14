// a file with simple bugs

#include <stdio.h>

void clang_analyzer_eval(bool);
void clang_analyzer_value(int);

// int f() {
//     int *x = 0;
//     return *x;
// }

int func2(int size, void* priv) {
    int *buf = (int*)priv;

    if (size > 0) {
        int a = buf[0];
        clang_analyzer_eval(a);
    }

    // return *buf;
    return 0;
}

int func3() {
    // return func2(0, 0);
    return func2(1,(void*)1);
}

// unsigned int func(unsigned int a)
// {
//     unsigned int *z = 0;
//     // int x = a & 1, y = (a & 1) ^ 1;
//     // clang_analyzer_eval(x);
//     // clang_analyzer_value(x);
//     // clang_analyzer_eval(y);
//     // clang_analyzer_value(y);
//     // clang_analyzer_eval((a & 1) && ((a & 1) ^ 1));
//     // clang_analyzer_value((a ^ a));
//     clang_analyzer_eval((a ^ a));
//     // if (!(a & 1) && ((a & 1) ^ 1))
//     if ((a ^ a))
//     // if (!a)
//         // if (true)
//         return *z; // unreachable
//     return 0;
// }

int main()
{
    // unsigned int a;
    // scanf("%d", &a);
    // func(a);
    printf("Hello, World!\n");

    return 0;
}
