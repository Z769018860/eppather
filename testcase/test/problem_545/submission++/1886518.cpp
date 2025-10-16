#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1200000 + 5;
const int MAXS = 100 + 5;
const int MAXM = 10000 + 5;
const int INF = 1e9;

queue<int> q;
bool inq[MAXS];
long long cost[MAXM], dis[MAXS];
int head[MAXS], to[MAXM], nxt[MAXM], cap[MAXM], flow[MAXM];
int cur[MAXS];
int a[MAXN], b[MAXN], cntA[MAXN], cntB[MAXN], cntC[MAXN];
int n, m, k, s, t, ss;
int tot = 1;
long long maxcost;

int lowbit(int k) {
    for(int i = 1; i <= 31; i++) {
        if(k >> (i - 1) & 1) {
            return i;
        }
    }
    return -1;
}

void addEdge(int u, int v, int c, int f, long long val) {
    to[++tot] = v;
    nxt[tot] = head[u];
    cap[tot] = c;
    flow[tot] = f;
    cost[tot] = val;
    head[u] = tot;
}

void addLine(int u, int v, int w, long long val) {
    addEdge(u, v, w, 0, val);
    addEdge(v, u, 0, 0, -val);
}

bool spfa() {
    while(!q.empty()) q.pop();
    memset(dis, -1, sizeof(dis));
    memset(inq, 0, sizeof(inq));
    dis[s] = 0;
    q.push(s);
    inq[s] = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;
        for(int i = head[u]; i != 0; i = nxt[i]) {
            if(cap[i] > flow[i] && dis[to[i]] < dis[u] + cost[i]) {
                dis[to[i]] = dis[u] + cost[i];
                if(!inq[to[i]]) {
                    q.push(to[i]);
                    inq[to[i]] = true;
                }
            }
        }
    }
    return dis[t] != -1;
}

int dinic(int u, int f) {
    if(u == t || f == 0) {
        return f;
    }
    inq[u] = true;
    int rest = f;
    for(int& i = cur[u]; i != 0; i = nxt[i]) {
        if(!inq[to[i]] && cap[i] > flow[i] && dis[to[i]] == dis[u] + cost[i]) {
            int k = dinic(to[i], min(rest, cap[i] - flow[i]));
            if(k == 0) {
                dis[to[i]] = -1;
                continue;
            }
            maxcost += k * cost[i];
            flow[i] += k;
            flow[i ^ 1] -= k;
            rest -= k;
            if(rest == 0) break;
        }
    }
    inq[u] = false;
    return f - rest;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        cntA[lowbit(a[i])]++;
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++) {
        scanf("%d", &b[i]);
        cntB[lowbit(b[i])]++;
    }
    s = 62; t = 63; ss = 64;
    scanf("%d", &k);
    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);
    int j = 1, last = 0;
    for(int i = 1; i <= n; i++) {
        if(i != n && a[i] == a[i + 1]) {
            continue;
        }
        int tot = 0;
        while(j <= m && b[j] < a[i]) j++;
        while(j <= m && b[j] == a[i]) j++, tot++;
        cntC[lowbit(a[i])] += min(tot, i - last);
        last = i;
    }
    long long ans = 0;
    for(int i = 1; i <= 31; i++) {
        ans += 1ll * (1 << (i - 1)) * cntA[i];
        addLine(ss, i, cntA[i], 0);
        addLine(i + 31, t, cntB[i], 0);
        if(cntC[i] > 0) {
            addLine(i, i + 31, cntC[i], (1 << (i - 1)));
        }
        for(int j = 1; j < i; j++) {
            if(cntA[i] > 0 && cntB[j] > 0) {
                addLine(i, j + 31, INF, (1 << (i - 1)) - (1 << j - 1));
            }
        }
    }
    addLine(s, ss, k, 0);
    while(spfa()) {
        memcpy(cur, head, sizeof(head));
        dinic(s, INF);
    }
    printf("%lld\n", ans - maxcost);

    return 0;
}
