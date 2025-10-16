#include <stdio.h>
#include <klee/klee.h>  // KLEE 插桩头文件

#define MAX 100

void sieveOfEratosthenes(int n) {
    int prime[MAX];
    
    // 初始化所有数字为质数
    for (int i = 0; i < n; i++) {
        prime[i] = 1;
    }
    prime[0] = prime[1] = 0;  // 0 和 1 不是质数
    
    // 使用筛法标记质数
    for (int p = 2; p * p <= n; p++) {
        if (prime[p] == 1) {
            for (int i = p * p; i <= n; i += p) {
                prime[i] = 0;
            }
        }
    }

    // 输出所有质数
    printf("Prime numbers up to %d: ", n);
    for (int i = 0; i <= n; i++) {
        if (prime[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int n;
    
    // 使用 KLEE 符号化整数 n
    klee_make_symbolic(&n, sizeof(n), "n");
    //klee_assume(n > 0 && n <= MAX);  // 假设 n 的范围为 1 到 MAX
    
    printf("Prime numbers up to %d: \n", n);
    sieveOfEratosthenes(n);
    
    return 0;
}
