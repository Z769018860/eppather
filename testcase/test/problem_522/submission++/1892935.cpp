#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int maxN = 3e5 + 5;
const int mod = 998244353;

struct explode {
    ll X, R, V;
    int id;
} ex[maxN];

int n, bj[maxN], d[maxN], pos[maxN];
int p[maxN], sbj[maxN];
ll f[maxN];
vector<int> E[maxN], G[maxN];

void dfs(int u, int rt) {
	if (!u) return;
	
	if (sbj[u] == rt) return;
	
	sbj[u] = rt;
	
	if (rt != u)
		f[rt] = max(f[rt], ((ex[rt].V ^ ex[u].V) % mod + ex[rt].V * ex[u].V % mod) % mod + f[u]);
		
	for (auto v : G[u]) {
		if(p[v])
			dfs(v, rt);
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> ex[i].X, ex[i].id = i;

    for (int i = 1; i <= n; ++i)
        cin >> ex[i].R;

    for (int i = 1; i <= n; ++i)
        cin >> ex[i].V;

    sort(ex + 1, ex + 1 + n, [&](explode a, explode b) {
        return a.X < b.X;
    });

    for (int i = 1; i <= n; ++i)
        pos[ex[i].id] = i;

    for (int i = 1; i <= n; ++i) {
        int x = i;
        ll L = ex[x].X - ex[x].R;
        ll R = ex[x].X + ex[x].R;
        int l = 1, r = x - 1, ret = -1;

        while (l <= r) {
            int mid = (l + r) >> 1;

            if (ex[mid].X >= L)
                ret = mid, r = mid - 1;
            else
                l = mid + 1;
        }

        if (ret != -1) {
            for (int j = ret; j < x; ++j) {
                E[x].emplace_back(j);
                G[j].emplace_back(x);
                ++d[j];
            }
        }

        l = x + 1, r = n, ret = -1;

        while (l <= r) {
            int mid = (l + r) >> 1;

            if (ex[mid].X <= R)
                ret = mid, l = mid + 1;
            else
                r = mid - 1;
        }

        if (ret != -1) {
            for (int j = x + 1; j <= ret; ++j) {
                E[x].emplace_back(j);
                G[j].emplace_back(x);
                ++d[j];
            }
        }
    }

    queue<int> q;

    for (int i = 1; i <= n; ++i)
        if (!d[i]) {
            q.emplace(i);
            f[i] = 0;
        }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
       
        dfs(u, u);
		p[u] = 1;
 		
        for (auto v : E[u]) {
            --d[v];

            if (d[v] == 0)
                q.emplace(v);
        }
    }

    for (int i = 1; i <= n; ++i)
        cout << f[pos[i]] << '\n';

    return 0;
}