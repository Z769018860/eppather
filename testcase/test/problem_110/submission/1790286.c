#include<stdio.h>
#include<stdlib.h>

long long n, p;
long long* inv;

int main() {
    scanf("%lld %lld", &n, &p);

    inv = (long long*)malloc((n + 5) * sizeof(long long));
    inv[1] = 1;
    printf("1\n");

    for (long long i = 2; i <= n; i++) {
        inv[i] = (p - p / i) * inv[p % i] % p;
        printf("%lld\n", inv[i]);
    }

    free(inv);
    return 0;
}
