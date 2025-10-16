#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = l; i <= r; i++)
#define rep2(i, l, r) for(int i = l; i >= r; i--)
#define fi first
#define se second
#define bit(i, x) (x >> i & 1)
const int mod = 1e9 + 7;
const int N = (1 << 22) + 3;
using namespace std;
int n, m, k;
int a[N];
namespace sub1{
    int res = 0;
    void backtrack(int p, int val) {
        if (p > k) {
            res += (val > 0);
            return;
        }
        rep(i, 1, m) backtrack(p + 1, (val & a[i]));
    }
    int solve() {
        res = 0;
        backtrack(1, (1 << n) - 1);
        return res;
    }
}
namespace sub2{
    void add(int &x, int y) {
        x += y;
        if (x >= mod) x -= mod;
    }
    int solve() {
        vector<vector<int>> dp(k + 3, vector<int>((1 << n) + 3, 0));
        dp[0][(1 << n) - 1] = 1;
        rep(i, 0, k - 1) {
            rep(j, 0, (1 << n) - 1) {
                rep(l, 1, m) {
                    add(dp[i + 1][j & a[l]], dp[i][j]);
                }
            }
        }
        int res = 0;
        rep(i, 1, (1 << n) - 1) add(res, dp[k][i]);
        return res;
    }
}
namespace sub3{
    int f[N], f2[N];
    int pw(int x, int y) {
        int s = 1;
        while (y) {
            if (y & 1) s = (1ll*s*x) % mod;
            x = (1ll*x*x) % mod;
            y >>= 1;
        }
        return s;
    }
    int solve() {
        rep(i, 1, m) f2[a[i]]++;
        int mx = *max_element(a + 1, a + m + 1);







        rep(i, 1, m) f[a[i]]++;


        rep(i, 0, 21) {
            rep(mask, 0, (1 << 22) - 1) {
                if (bit(i, mask)) f[mask ^ (1 << i)] += f[mask];
            }
        }


        int res = 0;
        rep(i, 1, mx) {
            if (__builtin_popcount(i) & 1) res = (res + pw(f[i], k)) % mod;
            else res = (res - pw(f[i], k) + mod) % mod;

        }
        return res;
    }
}
mt19937 rng(time(0));
int rnd(int l, int r) {
    return rng() % (r - l + 1) + l;
}
void Gen(int _n, int _m, int _k) {
    n = _n, m = _m, k = _k;
    rep(i, 1, m) a[i] = rnd(1, (1 << n) - 1);
}
void Pint() {
    cout << n << " " << m << " " << k << "\n";
    rep(i, 1, m) cout << a[i] << " ";
    cout << "\n";
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define task "bus"



    cin >> n >> m >> k;
    rep(i, 1, m) cin >> a[i];






    cout << sub3::solve();



    return 0 ^ 0;
}

