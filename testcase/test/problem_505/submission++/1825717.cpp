#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define is insert
#define inf 0x3f3f3f3f
#define pb push_back
#define int long long
using namespace std;

static char ibuf[(1 << 20) + 1], *iS, *iT;
#define getchar() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
inline void read(int& num) {
    num = 0;
    int g = 1;
    char x = getchar();
    while (x < '0' || x > '9') {
    	g = x == '-' ? -1 : g;
    	x = getchar();
	}
    while (x >= '0' && x <= '9') {
        num = (num << 1) + (num << 3) + (x ^ 48);
        x = getchar();
    }
    num *= g;
}

int n, m, T, s, t, sum, now[1000005];
bool vis[1000005];
int head[1000005], nxt[1000005], Ecnt = 1;
struct edge {
	int id, d;
} to[1000005];
struct Person {
	int x, y, r, val;
} P[1000005];
struct Ball {
	int x, y, val;
} B[1000005];

void Add(int u, int v, int w) { nxt[++Ecnt] = head[u], head[u] = Ecnt, to[Ecnt] = edge({v, w}); }
namespace Network_Flow {
	int d[1000005];
	bool bfs() {
		for (int i = 0; i <= t; i++) d[i] = 0;
		queue<int> q;
		now[s] = head[s];
		d[s] = 1;
		q.push(s);
		while (q.size()) {
			int id = q.front(); q.pop();
			for (int i = head[id]; i; i = nxt[i]) {
				if (to[i].d > 0 && !d[to[i].id]) {
					d[to[i].id] = d[id] + 1;
					now[to[i].id] = head[to[i].id];
					if (to[i].id == t) return 1;
					q.push(to[i].id);
				}
			}
		}
		return 0;
	}
	int dinic(int p, int flow) {
		if (p == t) return flow;
		int rest = flow, tmp, i;
		for (i = now[p]; i && rest; now[p] = i, i = nxt[i])
			if (to[i].d && d[to[i].id] == d[p] + 1) {
				tmp = dinic(to[i].id, min(rest, to[i].d));
				if (!tmp) d[to[i].id] = 0;
				to[i].d -= tmp;
				to[i ^ 1].d += tmp;
				rest -= tmp;
			}
		return flow - rest;
	}
	int NF() {
		int res(0), c;
		while (bfs()) while (c = dinic(s, inf)) res += c;
		return res;
	}
}
void init() {
	for (int i = 2; i <= Ecnt; i++) nxt[i] = 0;
	for (int i = 1; i <= m; i++) vis[i] = 0;
	for (int i = 0; i <= n + m + 1; i++) head[i] = 0;
	Ecnt = 1;
}
bool dis(int i, int j) { return (P[i].x - B[j].x) * (P[i].x - B[j].x) + (P[i].y - B[j].y) * (P[i].y - B[j].y) <= P[i].r * P[i].r; }
void Debug() {
	printf("sum: %lld\n", sum);
	for (int i = 1; i <= n; i++) printf("val: %lld = %lld\n", i, P[i].val);
	for (int i = 0; i <= n + m + 1; i++) {
		for (int j = head[i]; j; j = nxt[j]) printf("edge: %lld %lld %lld\n", i, to[j].id, to[j].d);
	}
	puts("-----------------------------------");
}

signed main() {


	read(T);
	while (T--) {
		read(n), read(m);
		s = sum = 0;
		t = n + m + 1;
		init();
		for (int i = 1; i <= n; i++) read(P[i].x), read(P[i].y), read(P[i].val), read(P[i].r);
		for (int i = 1; i <= m; i++) {
			read(B[i].x), read(B[i].y), read(B[i].val);
			if (dis(1, i)) vis[i] = 1, P[1].val += B[i].val;
			for (int j = 2; j <= n + 1; j++) {
				if (j == n + 1) {
					vis[i] = 1;
					break;
				}
				if (dis(j, i)) break;
			}
		}
		for (int i = 1; i <= m; i++) if (!vis[i]) {
			sum += B[i].val;
			Add(i + n, t, B[i].val), Add(t, i + n, 0);
			for (int j = 2; j <= n; j++) if (dis(j, i)) {
				Add(j, i + n, inf), Add(i + n, j, 0);
			}
		}
		bool flag = 0;
		for (int i = 2; i <= n; i++) {
			if (P[1].val < P[i].val) {
				flag = 1;
				puts("qaq");
				break;
			}
			Add(0, i, P[1].val - P[i].val);
			Add(i, 0, 0);
		}

		if (flag) continue;
		if (Network_Flow::NF() == sum) puts("ZQC! ZQC!");
		else puts("qaq");
	}
	return 0;
}