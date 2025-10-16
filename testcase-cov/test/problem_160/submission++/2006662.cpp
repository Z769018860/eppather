#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, w; cin >> n >> w;
    vector<int> W(n + 2), V(n + 2), dfn(n + 2), r(n + 2), nw(n + 2), nv(n + 2);
    vector<vector<int> > v(n + 2, vector<int>());
    vector<vector<int> > dp(n + 3, vector<int>(w + 1));

    int tot = 0;

    for (int i = 1; i <= n; ++i) {
        int fa; cin >> fa;
        v[fa].push_back(i);
    }
    for (int i = 1; i <= n; ++i) cin >> W[i];
    for (int i = 1; i <= n; ++i) cin >> V[i];

    function<void(int, int)> dfs = [&](int node, int fa) {
        dfn[node] = ++tot;
        nw[dfn[node]] = W[node];
        nv[dfn[node]] = V[node];
        for (auto to : v[node]) {
            if (to == fa) continue;
            dfs(to, node);
        }
        r[dfn[node]] = tot;
    };

    dfs(0, -1);

    for (int i = tot; i >= 1; --i) {
        for (int j = 0; j <= w; ++j) {
            if (j - nw[i] >= 0) dp[i][j] = max(dp[r[i] + 1][j], dp[i + 1][j - nw[i]] + nv[i]);
            else dp[i][j] = dp[r[i] + 1][j];
        }
    }

    cout << dp[1][w];
}