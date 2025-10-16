#include <bits/stdc++.h>

const int N = 310, M = 60010;

int n, m;
int S, T;

int head[N], ver[M], Next[M], cap[M], tot = 1;
void add_edge(int u, int v, int w) {
    ver[++ tot] = v, Next[tot] = head[u], head[u] = tot, cap[tot] = w;
    ver[++ tot] = u, Next[tot] = head[v], head[v] = tot, cap[tot] = 0;
}

int lev[N], cur[N];
int seq[N], r;

int in[N], out[N];

bool bfs() {
    for (int i = 1; i <= T; ++ i)
        lev[i] = -1, cur[i] = head[i];
    lev[seq[r = 1] = S] = 0;
    for (int e = 1; e <= r; ++ e) {
        int u = seq[e];
        for (int i = head[u]; i; i = Next[i]) {
            int v = ver[i];
            if (cap[i] && lev[v] == -1) {
                lev[seq[++ r] = v] = lev[u] + 1;
                if (v == T) return 1;
            }
        }
    }
    return 0;
}

int Dinic(int u, int flow) {
    if (u == T) return flow;
    int res = 0;
    for (int &i = cur[u]; i; i = Next[i]) {
        int v = ver[i];
        if (lev[v] == lev[u] + 1 && cap[i]) {
            int delta = Dinic(v, std::min(cap[i], flow - res));
            if (delta) {
                res += delta;
                cap[i] -= delta;
                cap[i ^ 1] += delta;
                if (res == flow) break;
            }
        }
    }

    if (res != flow) lev[u] = -1;
    return res;
}

int id[M], flow[M];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i) {
        int u, v, l, r; scanf("%d%d%d%d", &u, &v, &l, &r);
        add_edge(u, v, r - l);
        in[v] += l, out[u] += l;
        id[i] = tot, flow[i] = l;
    }

    int sum = 0;

    S = n + 1, T = n + 2;
    for (int i = 1; i <= n; ++ i) {
        if (in[i] > out[i]) {
            add_edge(S, i, in[i] - out[i]);
            sum += in[i] - out[i];
        } else add_edge(i, T, out[i] - in[i]);
    }

    while (bfs()) sum -= Dinic(S, 0x3f3f3f3f);

    if (sum) puts("NO");
    else {
        puts("YES");
        for (int i = 1; i <= m; ++ i)
            printf("%d\n", cap[id[i]] + flow[i]);
    }

    return 0;
}