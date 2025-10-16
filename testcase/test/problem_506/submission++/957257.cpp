#include <cstdio>
#include <cmath>
int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
int solve(int p, int m, int a) {
    int ret = 1, t = 1;
    for (int i = 1; i <= m; i++, t *= p) {
        if ((m - i) % a == 0) {
            if (p == 2)
                ret += a % 2 ? t : (t - 1) / 2 / (a & -a) + 1;
            else
                ret += (p - 1) * t / gcd((p - 1) * t, a);
        }
    }
    return ret;
}
int main() {
    int a, t, n;
    while (scanf("%d%d%d", &a, &t, &n) == 3) {
        int ans = 1;
        int s = sqrt(n);
        for (int i = 2; i <= s; i++) {
            if (n % i)
                continue;
            int k = 0;
            for (; n % i == 0; n /= i) k++;
            ans *= solve(i, k, a);
        }
        if (n != 1)
            ans *= solve(n, 1, a);
        printf("%d\n", ans);
    }
}