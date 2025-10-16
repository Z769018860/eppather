
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define ull unsigned long long
#define ll long long
#define ld double
#define yes {cout << "YES"; return;}
#define no {cout << "NO"; return;}
#define sz(x) (int) (x).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using pii = pair<int,int>;
constexpr int mod = 1e9 + 7;
constexpr ll oo = 1e18;
constexpr ld eps = 1e-9;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int dx[] = {0, 1, 0, -1, -1, 1, 1, -1};
int dy[] = {1, 0, -1, 0, 1, 1, -1, -1};
#define fi first
#define se second
#define name "pad"
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
#define For(i, l, r) for(int i = (l); i <= (r); ++i)
#define Ford(i, r, l) for(int i = (r); i >= (l); --i)
#define FindId(x, v) lower_bound(all(v), x) - (v).begin() + 1

template<typename T> bool maximize(T &a, T b) { return a < b && (a = b, true); }
template<typename T> bool minimize(T &a, T b) { return a > b && (a = b, true); }
template<typename T> void compress(vector<T> &v) { sort(all(v)); v.resize(unique(all(v)) - v.begin()); }

const int N = 5e4 + 5;
int n, w;
vector<vector<int>> dp;
vector<int> adj[N];
int node[N], timer = 0, sz[N], c[N], v[N];

void dfs(int u, int p = -1) {
    sz[u] = 1; node[++timer] = u;
    for(int v : adj[u]) if(v != p) {
        dfs(v, u); sz[u] += sz[v];
    }
}

int32_t main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);



    cin >> n >> w;
    dp.resize(n + 5, vector<int> (w + 5, 0));
    For(i, 1, n) {
        int d; cin >> d;
        adj[d].push_back(i);
        adj[i].push_back(d);
    }

    For(i, 1, n) cin >> c[i];
    For(i, 1, n) cin >> v[i];

    dfs(0);

    Ford(i, n + 1, 1) {
        For(j, 0, w) {
            dp[i][j] = dp[i + sz[node[i]]][j];
            if(j >= c[node[i]]) maximize(dp[i][j], dp[i + 1][j - c[node[i]]] + v[node[i]]);
        }
    }

    cout << dp[1][w];

    return 0;
}
