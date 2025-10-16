#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define D(x,y) ((x-1)*m+y)
#define int long long
int head[200010],cur[200010],nxt[200010],wei[200010],to[200010],cnt = 2,level[200010],vis[200010],s,t;
const int inf = 0x3f3f3f3f;
void add(int u,int v,int w) {
	to[cnt] = v;
	wei[cnt] = w;
	nxt[cnt] = head[u];
	head[u] = cnt;
	cnt++;
	to[cnt] = u;
	wei[cnt] = 0;
	nxt[cnt] = head[v];
	head[v] = cnt;
	cnt++;
}
int bfs() {
	memset(level,-1,sizeof(level));
	memcpy(cur,head,sizeof(head));
	level[s] = 0;
	queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int top = q.front();
		q.pop();
		for(int i = head[top]; i ; i = nxt[i]) {
			int tp = to[i];
			if(level[tp] == -1 && wei[i] > 0) {
				level[tp] = level[top] + 1;
				q.push(tp);
			}
		}
	}
	if(level[t] == -1) return 0;
	return 1;
}
int dfs(int now,int flow) {
	if(now == t) return flow;
	int remain = flow;
	for(int i = cur[now]; i ; i = nxt[i]) {
		cur[now] = i;
		int tp = to[i],w = wei[i];
		if(w > 0 && level[now]+1 == level[tp]) {
			int c = dfs(tp,min(w,remain));
			remain -= c;
			wei[i] -= c;
			wei[i^1] += c;
		}
	}
	return flow - remain;
}
int dinic() {
	int ans = 0;
	while(bfs()) {
		ans += dfs(s,inf);
	}
	return ans;
}
int mappa[100010];
signed main() {
	cin.tie(0)->sync_with_stdio(false);
	int n,m,ans = 0;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		string s; cin >> s;
		for(int j = 1; j <= m; j++) {
			if(s[j-1] == '*') mappa[D(i,j)] = -1;
			else mappa[D(i,j)] = s[j-1]-'0';
		}
	}
	s = n*m+1,t = n*m+2;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(mappa[D(i,j)] == 1) {
				add(s,D(i,j),1);
				if(i > 1 && mappa[D(i-1,j)] == 3) add(D(i,j),D(i-1,j),1);
				if(j > 1 && mappa[D(i,j-1)] == 3)    add(D(i,j),D(i,j-1),1);
				if(i < n && mappa[D(i+1,j)] == 3) add(D(i,j),D(i+1,j),1);
				if(j < m && mappa[D(i,j+1)] == 3)    add(D(i,j),D(i,j+1),1);
			}
			if(mappa[D(i,j)] == 3) add(D(i,j),t,1);
			if(mappa[D(i,j)] == 2) ans++;
		}
	}
	cout << dinic()+ans;
	return 0;
}
