#include <stdio.h>
#include <klee/klee.h>  // KLEE 插桩头文件

void primeFactorization(int n) {
    // 处理 2 的因数
    while (n % 2 == 0) {
        printf("%d ", 2);
        n /= 2;
    }
    
    // 处理奇数因数
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            printf("%d ", i);
            n /= i;
        }
    }

    // 如果 n 是质数且大于 2
    if (n > 2) {
        printf("%d ", n);
    }

    printf("\n");
}

int main() {
    int n;

    // 使用 KLEE 符号化整数 n
    klee_make_symbolic(&n, sizeof(n), "n");
    //klee_assume(n > 0 && n <= 1000);  // 假设 n 的范围为 1 到 1000

    printf("Prime factorization of %d: ", n);
    primeFactorization(n);

    return 0;
}
