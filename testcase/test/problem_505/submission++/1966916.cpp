#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 505;
int S, T;
vector<int> v[MAXN+5], back[MAXN+5];
vector<ll> o[MAXN+5];
inline void connect(int x, int y, int z) {
	back[x].push_back(v[y].size());
	back[y].push_back(v[x].size());
	v[x].push_back(y);
	v[y].push_back(x);
	o[x].push_back(z);
	o[y].push_back(0);
	return ;
}
int dis[MAXN+5];
bool vis[MAXN+5];
bool bfs() {
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(S);
	vis[S] = 1;
	while (!q.empty()) {
		int i = q.front();
		q.pop();
		for (int p=0;p<v[i].size();p++) {
			if (o[i][p]&&!vis[v[i][p]]) {
				dis[v[i][p]] = dis[i]+1;
				vis[v[i][p]] = 1;
				q.push(v[i][p]);
			}
		}
	}
	return vis[T];
}
int cur[MAXN+5];
ll dfs(int i, ll u) {
	if (i==T) return u;
	ll all = 0;
	for (int p=cur[i];p<v[i].size();p++) {
		cur[i] = p;
		if (dis[v[i][p]]==dis[i]+1&&o[i][p]) {
			ll flow = dfs(v[i][p], min(u, o[i][p]));
			u-=flow;
			all+=flow;
			o[i][p]-=flow;
			o[v[i][p]][back[i][p]]+=flow;
			if (!u) return all;
		}
	}
	return all;
}
ll dinic() {
	ll ans = 0;
	while (bfs()) {
		memset(cur, 0, sizeof(cur));
		ans+=dfs(S, 1e18);
	}
	return ans;
}
int t, n, m;
struct e{
	ll x, y, w, r;
}a[105], b[405];
bool book[405];
int main() {
	scanf("%d", &t);
	for (int zqw=1;zqw<=t;zqw++) {
		scanf("%d %d", &n, &m);
		S = n+m+1, T = S+1;
		for (int p=1;p<=n;p++) {
			scanf("%lld %lld %lld %lld", &a[p].x, &a[p].y, &a[p].w, &a[p].r);
		}
		ll sum = 0;
		for (int p=1;p<=m;p++) {
			scanf("%lld %lld %lld", &b[p].x, &b[p].y, &b[p].w);
			if ((a[1].x-b[p].x)*(a[1].x-b[p].x)+(a[1].y-b[p].y)*(a[1].y-b[p].y)<=a[1].r*a[1].r) {
				a[1].w+=b[p].w;
				p--;
				m--;
				continue;
			}
			connect(p+n, T, b[p].w);
			book[p] = 0;
		}
		bool flag = 0;
		for (int p=2;p<=n;p++) {
			if (a[p].w>a[1].w) {
				flag = 1;
				break;
			}
			connect(S, p, a[1].w-a[p].w);
		}
		if (flag) {
			puts("qaq");
			for (int p=1;p<=T;p++) {
				v[p].clear();
				o[p].clear();
				back[p].clear();
			}
			continue;
		}
		for (int p=2;p<=n;p++) {
			for (int k=1;k<=m;k++) {
				if ((a[p].x-b[k].x)*(a[p].x-b[k].x)+(a[p].y-b[k].y)*(a[p].y-b[k].y)<=a[p].r*a[p].r) {
					connect(p, k+n, 1e9);
					if (!book[k]) {
						book[k] = 1;
						sum+=b[k].w;
					}
				}
			}
		}
		if (dinic()==sum) puts("ZQC! ZQC!");
		else puts("qaq");
		for (int p=1;p<=T;p++) {
			v[p].clear();
			o[p].clear();
			back[p].clear();
		}
	}
	return 0;
}