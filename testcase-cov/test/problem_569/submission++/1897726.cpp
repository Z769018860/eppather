#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int n, m;

struct Dinic {
    struct Edge {
        int from, to, cap, flow;
        Edge(int u, int v, int c, int f): from(u), to(v), cap(c), flow(f) {}
    };
    vector<Edge> edges; vector<int> G[N];
    inline void AddEdge(int u, int v, int c) {
        static int M;
        edges.emplace_back(Edge(u, v, c, 0)), edges.emplace_back(Edge(v, u, 0, 0));
        M = edges.size(); G[u].emplace_back(M - 2), G[v].emplace_back(M - 1);
    }

    int d[N], s, t, cur[N];
    inline bool BFS() {
        memset(d, 0x3f, sizeof d), d[s] = 0;
        queue<int> Q; Q.push(s);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            for(auto i : G[u]) {auto &e = edges[i];
                if(d[e.to] != INF || e.flow == e.cap) continue;
                d[e.to] = d[u] + 1; Q.push(e.to);
            }
        }
        return d[t] != INF;
    }
    int dfs(int u, int F) {
        if(u == t || F <= 0) return F;
        int flow = 0;
        for(int &i = cur[u]; i < G[u].size(); i ++) {auto &e = edges[G[u][i]]; 
            if(d[e.to] != d[u] + 1 || e.flow == e.cap) continue;
            int f = dfs(e.to, min(F, e.cap - e.flow));
            flow += f, F -= f, e.flow += f, edges[G[u][i] ^ 1].flow -= f;
            if(!F) break;
        }
        return flow;
    }
    inline int MaxFlow(int s, int t) {
        this->s = s, this->t = t;
        int ans = 0;
        while(BFS()) {
            memset(cur, 0, sizeof cur);
            ans += dfs(s, INF);
        }
        return ans;
    }
} solver;

inline int get(int x, int y) {return x * m + y; }

int main() {
    ios::sync_with_stdio(false), cin.tie(0);

    int res = 0; cin >> n >> m;
    vector<string> vec(n);
    for(int i = 0; i < n; i ++) cin >> vec[i];

    int s = get(n - 1, m - 1) + 1, t = s + 1;
    for(int i = 0; i < n; i ++) for(int j = 0; j < m; j ++) {
        if(i + j & 1) solver.AddEdge(get(i, j), t, 1);
        else solver.AddEdge(s, get(i, j), 1);
        if(vec[i][j] == '2') res ++;
    }
    for(int i = 0; i < n; i ++) for(int j = 0; j < m; j ++) {
        if(j != m - 1 && ((vec[i][j] == '1' && vec[i][j + 1] == '3') || (vec[i][j] == '3' && vec[i][j + 1] == '1'))) {
            if(i + j & 1) solver.AddEdge(get(i, j + 1), get(i, j), 1);
            else solver.AddEdge(get(i, j), get(i, j + 1), 1);
        }
        if(i != n - 1 && ((vec[i][j] == '1' && vec[i + 1][j] == '3') || (vec[i][j] == '3' && vec[i + 1][j] == '1'))) {
            if(i + j & 1) solver.AddEdge(get(i + 1, j), get(i, j), 1);
            else solver.AddEdge(get(i, j), get(i + 1, j), 1);
        }
    }
    cout << res + solver.MaxFlow(s, t) << '\n';

    return 0;
}