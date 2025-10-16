#include <bits/stdc++.h>
#define show(x) cerr << #x << " = " << x << endl
using namespace std;
typedef long long ll;
typedef pair<int, int> Pairs;

const int N = 505;

inline char get(void) {
    static char buf[100000], *S = buf, *T = buf;
    if (S == T) {
        T = (S = buf) + fread(buf, 1, 100000, stdin);
        if (S == T) return EOF;
    }
    return *S++;
}
template<typename T>
inline void read(T &x) {
    static char c; x = 0; int sgn = 0;
    for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
    for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
    if (sgn) x = -x;
}

int n, ans, clc;
ll a[N];
int mp[N][N];
int usd[N], mat[N];

ll gcd(ll a, ll b) {
    ll c = 1;
    while (c) {
        c = a % b;
        a = b; b = c;
    }
    return a;
}
inline int match(int u) {
    for (int i = 1; i <= n; i++)
        if (usd[i] != clc && mp[u][i]) {
            usd[i] = clc;
            if (!mat[i] || match(mat[i])) {
                mat[i] = u; return 1;
            }
        }
    return 0;
}

int main(void) {
    read(n); ans = n;
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mp[i][j] = ((gcd(a[i], a[j]) == 1) && (gcd(a[i] + 1, a[j] + 1) == 1));
    for (int i = 1; i <= n; i++)
        if (a[i] & 1) {
            ++clc; ans -= match(i);
        }
    cout << ans << endl;
    return 0;
}
