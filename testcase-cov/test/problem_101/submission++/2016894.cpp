#include <bits/stdc++.h>
using namespace std;
const int _ = 110;
const int __ = 10010;
int n, m, s, t, e = 1, hd[_], nx[__], to[__];
long long ln[__], ans;
inline void r_add(int u, int v, long long w) {
    e++;
    nx[e] = hd[u];
    to[e] = v;
    ln[e] = w;
    hd[u] = e;
}
inline void add(int u, int v, long long w) {
    r_add(u, v, w);
    r_add(v, u, 0);
}
int cr[_], dis[_], L, R, Q[_];
inline bool bfs(void) {
    for (int i = 1; i <= n; i++) {
        cr[i] = hd[i];
        dis[i] = 0;
    }
    dis[s] = 1;
    L = R = 1;
    Q[1] = s;
    while (L <= R) {
        int u = Q[L++];
        for (int i = hd[u]; i; i = nx[i]) {
            if (ln[i]) {
                int v = to[i];
                if (!dis[v]) {
                    dis[v] = dis[u] + 1;
                    Q[++R] = v;
                }
            }
        }
    }
    return dis[t];
}
long long dfs(int u, long long flow) {
    if (u == t) return flow;
    long long ans = 0LL;
    for (int i = cr[u]; i; i = nx[i]) {
        cr[u] = i;
        int v = to[i];
        if (ln[i] && dis[v] == dis[u] + 1) {
            long long tmp = dfs(v, min(flow, ln[i]));
            flow -= tmp;
            ans += tmp;
            ln[i] -= tmp;
            ln[i^1] += tmp;
            if (!flow) break;
        }
    }
    if (ans == 0LL) dis[u] = 0;
    return ans;
}
int main() {
    cin >> n >> m >> s >> t;
    while (m--) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        add(u, v, w);
    }
    while (bfs()) {
        ans += dfs(s, 1e18);
    }
    cout << ans << endl;
    return 0;
}