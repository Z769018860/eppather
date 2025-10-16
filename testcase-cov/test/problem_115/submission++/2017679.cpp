#include <iostream>
#include <cstring>
using namespace std;

const int N = 210, M = (10200 + N) * 2, INF = 1e8;
int n, m, S, T;
int h[N], e[M], ne[M], f[M], l[M], idx;
int q[N], d[N], cur[N], A[N];


void add(int a, int b, int c, int d) {
    e[idx] = b, ne[idx] = h[a], f[idx] = d - c, l[idx] = c, h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx++;
}

bool bfs() {
    memset(d, -1, sizeof d);
    
    int hh = 0, tt = 0;
    q[tt++] = S, d[S] = 0, cur[S] = h[S];
    while (hh < tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int v = e[i];
            if (d[v] == -1 && f[i]) {
                d[v] = d[t] + 1;
                if (v == T) return true;

                cur[v] = h[v];
                q[tt++] = v;
            }
        }
    }
    
    return false;
}

int dfs(int u, int limit) {
    if (u == T) return limit;
    int flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
        cur[u] = i;
        int v = e[i];
        if (d[v] == d[u] + 1 && f[i]) {
            int t = dfs(v, min(limit - flow, f[i]));
            if (!t) d[v] = -1;
            f[i] -= t, f[i ^ 1] += t, flow += t;
        }
    }

    return flow;
}

int dinic() {
    int r = 0, flow;
    while (bfs()) while(flow = dfs(S, INF)) r += flow;
    return r;
}

int main() {
    cin >> n >> m;
    S = 0, T = n + 1;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        add(a, b, c, d);
        A[a] -= c, A[b] += c;
    }

    int tot = 0;
    
    for (int i = 1; i <= n; i++)
        if (A[i] > 0) add(S, i, 0, A[i]), tot += A[i];
        else if (A[i] < 0) add(i, T, 0, -A[i]);

	
    if (dinic() < tot) cout << "NO" << endl;
    else {
        cout << "YES" << endl;
        for (int i = 0; i < m * 2; i += 2) 
        	
            cout << f[i ^ 1] + l[i] << endl;
    }

    return 0;
}
