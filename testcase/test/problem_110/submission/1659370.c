#include <stdio.h>

typedef unsigned long long ll;

ll FP(ll base, ll exp, ll mod) {
    ll ans = 1;
    while (exp) {
        if (exp & 1) ans = (ans * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return ans;
}

int main() {
    ll n, p, i;
    scanf("%llu %llu", &n, &p);
    for (i = 1; i <= n; ++i) {
        printf("%llu\n", FP(i, p - 2, p));
    }
    return 0;
}
