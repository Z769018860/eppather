#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define maxn 1000010
typedef long long ll;
const ll mod = 998244353;
ll rd() {
    ll k = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')f = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        k = (k << 1) + (k << 3) + c - 48;
        c = getchar();
    }
    return k * f;
}
int c[maxn];
int a[maxn];
int n;
ll fac, ans;
int lowbit(int c) {
    return c & (-c);
}
void init(int N) {
    n = N;
    for (int i = 0; i <= n; ++i) c[i] = 0;
}
void add(int loc, int v) {
    while (loc <= n) {
        c[loc] += v, loc += lowbit(loc);
    }
}
int sum(int loc) {
    int ret = 0;
    while (loc) {
        ret += c[loc], loc -= lowbit(loc);
    }
    return ret;
}
int query(int l, int r) {
    if (l > r) return 0;
    return sum(r) - sum(l - 1);
}
int main() {
    n = rd();
    for (int i = 1; i <= n; ++i) a[i] = rd();
    fac = 1;
    for (int i = n; i; --i) {
        ans += fac * (ll)query(1, a[i] - 1), ans %= mod;
        fac *= ((ll)n - i + 1), fac %= mod;
        add(a[i], 1);
    }
    printf("%lld\n", ans + 1);
}