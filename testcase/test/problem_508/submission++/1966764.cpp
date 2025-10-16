#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0;
    char c;

    while (c = getchar())
        if (c >= '0' && c <= '9')
            break;

    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }

    return x;
}
const int N = 1000005;
int n, m, Q, fa[N], GCD[N], l[31][N];
bool tag[31][N];
inline int gcd(int a, int b) {
    if (!b)
        return a;

    return gcd(b, a % b);
}
inline void exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return;
    }

    exgcd(b, a % b, y, x);
    y = y - a / b * x;
}
inline int find(int x) {
    if (x == fa[x])
        return x;

    int pa = fa[x];
    fa[x] = find(fa[x]);

    for (int i = 0; i <= 30; ++i)
        l[i][x] ^= l[i][pa];

    return fa[x];
}
inline int solve(int a, int b, int c, int n) {
    int g = gcd(a, b);

    if (c % g)
        return 0;

    a /= g, b /= g, c /= g;
    int x, y;
    exgcd(a, b, x, y);
    c = (1ll * c * x % b + b) % b;
    return (n / b) + (c <= (n % b));
}
int main() {
    n = read(), m = read(), Q = read();

    for (int i = 1; i <= n; ++i)
        fa[i] = i;

    for (int i = 0; i <= 30; ++i)
        for (int j = 1; j <= n; ++j)
            tag[i][j] = 1;

    int op, u, v, w, x, b, c;

    while (Q--) {
        op = read(), u = read(), v = read();

        if (op == 1) {
            w = read();
            int fx = find(u), fy = find(v);

            if (fx != fy) {
                fa[fy] = fx;
                GCD[fx] = gcd(GCD[fx], gcd(GCD[fy], w));

                for (int i = 0; i <= 30; ++i) {
                    l[i][fy] = l[i][v] ^ (w & 1)^l[i][u];
                    w >>= 1;
                    tag[i][fx] &= tag[i][fy];
                }
            } else {
                GCD[fx] = gcd(GCD[fx], w);

                for (int i = 0; i <= 30; ++i) {
                    if ((l[i][u]^l[i][v] ^ (w & 1)) == 1)
                        tag[i][fx] = 0;

                    w >>= 1;
                }
            }
        } else {
            x = read(), b = read(), c = read();
            int fx = find(u), fy = find(v);

            if (fx != fy) {
                puts("0");
                continue;
            }

            int g = gcd(GCD[fx], m);

            if ((m / g) & 1) {
                printf("%d\n", solve(b, g, ((-x) % g + g) % g, c - 1));
                continue;
            }

            int num = 0;
            int gg = g;

            while (gg % 2 == 0)
                ++num, gg >>= 1;

            if (!tag[num][fx]) {
                printf("%d\n", solve(b, g, ((-x) % g + g) % g, c - 1));
                continue;
            }

            int L = l[num][u] ^ l[num][v];

            if (L & 1) {
                printf("%d\n", solve(b, g << 1, ((-x + g) % (g << 1) + (g << 1)) % (g << 1), c - 1));
            } else {
                printf("%d\n", solve(b, g << 1, ((-x) % (g << 1) + (g << 1)) % (g << 1), c - 1));
            }
        }
    }
}