#include <bits/stdc++.h>

using namespace std;

const int N = 110, M = 410, INF = 0x3f3f3f3f;
int n, m, x[N], y[N], w[N], r[N];

inline bool in(pair<int, int> p1, pair<int, int> O, int r) {
    return (p1.first - O.first) * (p1.first - O.first) + (p1.second - O.second) * (p1.second - O.second) <= r * r;
}

const int Dinic_N = 510;
struct Dinic {
    struct Edge {
        int from, to, cap, flow;
        Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
    };
    vector<Edge> edges; vector<int> G[Dinic_N];
    inline void AddEdge(int u, int v, int c) {
        static int M;
        edges.emplace_back(Edge(u, v, c, 0)), edges.emplace_back(Edge(v, u, 0, 0));
        M = edges.size(); G[u].emplace_back(M - 2), G[v].emplace_back(M - 1);
    }
    inline void clear() {
        for(int i = 0; i < Dinic_N; i ++) G[i].clear();
        edges.clear();
    }
    int s, t, cur[Dinic_N], d[Dinic_N];
    inline bool BFS() {
        memset(d, 0x3f, sizeof d); d[s] = 0;
        queue<int> Q; Q.push(s);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            for(auto &i : G[u]) {auto &e = edges[i];
                if(d[e.to] != INF || e.cap == e.flow) continue;
                d[e.to] = d[u] + 1; Q.push(e.to);
            }
        }
        return d[t] != INF;
    }
    int dfs(int u, int F) {
        if(u == t || F <= 0) return F;
        int flow = 0;
        for(int &i = cur[u]; i < G[u].size(); i ++) {
            auto &e = edges[G[u][i]];
            if(d[e.to] != d[e.from] + 1 || e.cap == e.flow) continue;
            int f = dfs(e.to, min(e.cap - e.flow, F));
            flow += f, F -= f, e.flow += f, edges[G[u][i] ^ 1].flow -= f;
            if(!F) break;
        }
        return flow;
    }
    int MaxFlow(int s, int t) {
        this->s = s, this->t = t;
        int ans = 0;
        while(BFS()) {
            memset(cur, 0, sizeof cur);
            ans += dfs(s, INF);
        }
        return ans;
    }
} solver;

int main() {
    ios::sync_with_stdio(false), cin.tie(0);

    int T; cin >> T;
    while(T --) {solver.clear();
        cin >> n >> m;
        for(int i = 1; i <= n; i ++) {
            cin >> x[i] >> y[i] >> w[i] >> r[i];
        }
        int s = 0, t = n + m + 1, sum = 0;
        for(int i = 1; i <= m; i ++) {
            int _x, _y, _w; cin >> _x >> _y >> _w;
            if(!in({_x, _y}, {x[1], y[1]}, r[1])) {
                bool flag = false;
                solver.AddEdge(n + i, t, _w);
                for(int j = 2; j <= n; j ++)
                    if(in({_x, _y}, {x[j], y[j]}, r[j])) 
                        solver.AddEdge(j, n + i, INF), flag = true;
                if(flag) sum += _w;
            } else w[1] += _w;
        }
        bool flag = true;
        for(int i = 2; i <= n; i ++) {
            if(w[i] > w[1]) flag = false;
        }

        if(flag) {
            int tt = 0;
            for(int i = 2; i <= n; i ++) 
                solver.AddEdge(s, i, w[1] - w[i]);
            int res = solver.MaxFlow(s, t);
            if(sum == res) cout << "ZQC! ZQC!\n";
            else cout << "qaq\n";
        } else cout << "qaq\n";
    }

    return 0;
}