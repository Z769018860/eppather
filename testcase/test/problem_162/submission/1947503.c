#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

long long mod_power(long long x, long long a, long long p) {
     long long result = 1;
    x = x % p;
    while (a > 0) {
        if (a % 2 == 1)
            result = (result * x) % p;
        a = a /2;
        x = (x * x) % p;
    }
    return result;
}
int main() {
     long long x, n, ai, p = 998244352;
    scanf("%lld%lld", &x, &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &ai);
        printf("%lld ", mod_power(x, ai, p));
    }
    return 0;
}

