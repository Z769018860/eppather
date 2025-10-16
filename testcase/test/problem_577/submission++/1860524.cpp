#include <bits/stdc++.h>
#define For(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define ll long long
#define uint unsigned
#define ull unsigned ll
#define ldb long double
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n, p, Q, a[55];
int C[55][55];
int f[55][55][2555];
void init() {
    For(i, 0, p) C[i][0] = 1;
    For(i, 1, p) For(j, 1, i)
    C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
    f[0][0][0] = 1;
    For(i, 0, n) {
        For(j, 0, p - 1) For(k, 0, i * j) {
            int val = f[i][j][k];
            For(l, 0, p - 1 - j) {
                f[i + 1][j + l][k + i * l] = (f[i + 1][j + l][k + i * l] + val * C[j + l][j]) % p;
                val = 1ll * val * a[i] % p;
            }
        }
    }
    
}
int g[65][10005];
int A[65], B[65], len;
int tmp[10005];
ll m, k;
void solve() {
    scanf("%lld%lld", &m, &k);
    len = 0;

    for (; m || k;) {
        len++;
        A[len] = m % p;
        m /= p;
        B[len] = k % p;
        k /= p;
    }

    int las = 0;
    memset(g, 0, sizeof(g));
    g[0][0] = 1;
    For(i, 1, len) {
        las /= p;
        For(j, 0, las) tmp[j] = g[i - 1][j * p + B[i - 1]];
        For(j, 0, las) For(k, 0, A[i]*n)
        g[i][j + k] += tmp[j] * f[n + 1][A[i]][k];
        las += A[i] * n;
        For(j, 0, las) g[i][j] %= p;
    }
    printf("%d\n", g[len][B[len]]);
}
int main() {
    
    
    scanf("%d%d", &n, &p);
    ll INF = 1000000000000000000ll;

    for (; INF; ++len, INF /= p);

    For(i, 0, n) scanf("%d", &a[i]);
    init();
    scanf("%d", &Q);

    while (Q--)
        solve();
}
