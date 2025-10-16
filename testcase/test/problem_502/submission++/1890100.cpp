#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;

const int N = 1e6 + 10, M = 2e6 + 10;
const ull MOD = 12157665459056928801ull;    
int n, m;

ull s[2187][2187], r[177147];
inline void init() {
    for(int i = 0; i < 2187; i ++)
        for(int j = 0; j < 2187; j ++)
            s[i][j] = s[i / 3][j / 3] * 3 + (i + j) % 3;
    for(int i = 0; i < 177147; i ++)
        r[i] = r[i / 3] * 3 + (3 - i % 3) % 3;
}
inline ull Plus(ull x, ull y) {
    ull res = 0ull, it = 1ull;
    while(x || y) 
        res += it * s[x % 2187ull][y % 2187ull], x /= 2187ull, y /= 2187ull, it *= 2187ull;
    return res;
}
inline ull Minus(ull x) {
    ull res = 0ull, it = 1ull;
    while(x) 
        res += it * r[x % 177147ull], x /= 177147ull, it *= 177147ull;
    return res;
}

mt19937_64 RAND(time(0));
inline ull Rand() {return (ull)RAND() % MOD; }

ull val[N], path_val[M];
int h[M], e[2 * N], ne[2 * N], idx; ull w[2 * N];
inline void add(int a, int b, ull c) {e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++; }

inline int get(ull x) {
    for(int i = h[x % M]; i != -1; i = ne[i])
        if(w[i] == x) return e[i];
    return 0;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    memset(h, -1, sizeof h);

    init();
    cin >> n >> m;

    for(int i = 1; i <= n; i ++) val[i] = Rand();
    for(int i = 1; i <= n; i ++) {
        ull x = val[i], y = Minus(val[i]);
        add(x % M, i, x), add(y % M, i, y);
    }

    int lastans = 0;
    for(int i = 1; i <= m; i ++) {
        int x, y; cin >> x >> y; x ^= lastans, y ^= lastans;
        ull ans = Plus(val[x], path_val[y]);
        path_val[i] = ans;
        if(ans) {
            int r = get(ans);
            if(r) lastans = r;
            else lastans = -2;
        } else lastans = -1;

        cout << lastans << '\n';
    }

    return 0;
}