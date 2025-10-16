#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
typedef long long LL;
LL bit[64], a[64], x, k;
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w+", stdout);
#endif
    int n, m, cnt = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &x);
        for (int j = 50; ~j; --j) {
            if (x & (1LL << j)) {
                if (!bit[j]) { bit[j] = x; break; }
                x ^= bit[j];
            }
        }
    }
    for (int i = 50; ~i; --i)
        for (int j = i - 1; ~j; --j)
            if (bit[i] & (1LL << j)) bit[i] ^= bit[j];
    for (int i = 0; i <= 50; ++i)
        if (bit[i]) a[cnt++] = bit[i];
    scanf("%d", &m);
    while (m--) {
        scanf("%lld", &k);
        if (cnt != n) --k;
        if (k >= (1LL << cnt)) puts("-1");
        else {
            LL ans = 0;
            for (int i = 0; i < cnt; ++i)
                if (k & (1LL << i)) ans ^= a[i];
            printf("%lld\n", ans);
        }
    }
    return 0;
}