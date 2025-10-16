#include <stdio.h>
#define N 64

long long B[N];

void insert(long long x) {
    for (int i = N - 1; i >= 0; i--) {
        if (x & (1LL << i)) {
            if (B[i]) x ^= B[i];
            else {
                B[i] = x;
                break;
            }
        }
    }
}

long long ans() {
    long long res = 0;
    for (int i = N - 1; i >= 0; i--) {
        if ((res ^ B[i]) > res) res ^= B[i];
    }
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        long long x;
        scanf("%lld", &x);
        insert(x);
    }
    printf("%lld\n", ans());
    return 0;
}
