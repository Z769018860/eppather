#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = l; i <= r; i++)
#define rep2(i, l, r) for(int i = l; i >= r; i--)
#define fi first
#define se second
#define bit(i, x) (x >> i & 1)
const int N = 3e5 + 3;
const int mod = 998244353;
using namespace std;
int n;
array<long long, 4> a[N];
namespace sub123{
    vector<int> G[N], G2[N];
    int deg[N];
    long long d[N], res[N];
    int vst[N], b[N];
    int F(long long x, long long y) {
        return ((x ^ y) + (x*y) % mod) % mod;
    }
    void dfs(int u, int rt) {
        if (b[u] == rt) return;
        b[u] = rt;
        if (u != rt) d[rt] = max(d[rt], d[u] + F(a[u][2], a[rt][2]));
        for(int v : G2[u]) if (vst[v]) {
            dfs(v, rt);
        }
    }
    void solve() {
        rep(i, 1, n) {
            int l = 1, r = n, ll, rr;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (a[mid][0] >= a[i][0] - a[i][1]) ll = mid, r = mid - 1;
                else l = mid + 1;
            }
            l = 1, r = n;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (a[mid][0] <= a[i][0] + a[i][1]) rr = mid, l = mid + 1;
                else r = mid - 1;
            }

            rep(j, ll, rr) if (j != i) {
                G[i].push_back(j);
                G2[j].push_back(i);
                deg[j]++;
            }
        }
        queue<int> q;
        rep(i, 1, n) if (!deg[i]) q.push(i);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            dfs(u, u);
            vst[u] = 1;
            for(int v : G[u]) {

                if (!--deg[v]) q.push(v);
            }
        }

        rep(i, 1, n) res[a[i][3]] = d[i];
        rep(i, 1, n) cout << res[i] << "\n";
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #define task "bus"



    cin >> n;
    rep(i, 1, n) cin >> a[i][0];
    rep(i, 1, n) cin >> a[i][1];
    rep(i, 1, n) cin >> a[i][2];
    rep(i, 1, n) a[i][3] = i;

    sort(a + 1, a + n + 1);

    sub123::solve();

    return 0 ^ 0;
}

