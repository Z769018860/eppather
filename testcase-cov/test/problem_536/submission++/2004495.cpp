#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5,  M = 6e5 + 5;

int he[N], to[M], ne[M], w[M], idx;
int d[N], q[N], cur[N];
int S, T;

void add(int a, int b, int c, int d_ = 0){
	to[idx] = b, ne[idx] = he[a], w[idx] = c, he[a] = idx ++;
	to[idx] = a, ne[idx] = he[b], w[idx] = d_, he[b] = idx ++;
}

bool bfs(){
	int hh = 0, tt = -1;
	memset(d, -1, sizeof(d));
	q[++ tt] = S;
	d[S] = 1, cur[S] = he[S];
	
	while(hh <= tt){
		int x = q[hh ++];
		
		for(int j = he[x]; j != -1; j = ne[j]){
			int u = to[j];
			if(d[u] == -1 && w[j]){
				d[u] = d[x] + 1;
				cur[u] = he[u];
				if(u == T)return 1;
				q[++ tt] = u;
			}
		}
	}
	
	return 0;
}

int find(int x, int limit){
	if(x == T)return limit;
	int flow = 0;
	
	for(int j = cur[x]; j != -1 && flow < limit; j = ne[j]){
		cur[x] = j;
		int u = to[j];
		
		if(d[u] == d[x] + 1 && w[j]){
			int t = find(u, min(w[j], limit - flow));
			if(t == 0)d[u] = -1;
			flow += t, w[j] -= t, w[j ^ 1] += t;
		}
	}
	
	return flow;
}

int Dinic(){
	int ans = 0;
	while(bfs())ans += find(S, int(1e9));
	return ans;
}

int w1[N][2], w2[N][2];
int ans[N];

int main(){
	int k1, k2;
	scanf("%d%d", &k1, &k2);
	
	int n, m;
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)scanf("%d%d", &w1[i][0], &w1[i][1]);
	
	scanf("%d", &m);
	for(int i = 1; i <= m; i ++)scanf("%d%d", &w2[i][0], &w2[i][1]);
	
	S = n + m + k1 + k2 + 1, T = n + m + k1 + k2 + 2;
	
	memset(he, -1, sizeof(he));
	for(int i = 1; i <= n; i ++){
		add(S, i, 1);
		add(i, n + m + w1[i][0], 1);
		add(i, n + m + k1 + w1[i][1], 1);
	}
	
	for(int i = 1; i <= m; i ++){
		add(n + i, T, 1);
		add(n + m + w2[i][0], n + i, 1);
		add(n + m + k1 + w2[i][1], n + i, 1);
	}
	
	Dinic();
	
	for(int j = he[S]; j != -1; j = ne[j]){
		int u = to[j];
		if(u < 1 || u > n)continue;
		if(!w[j] && d[u] == -1)ans[u] = 1;
		else ans[u] = 0;
	}
	
	for(int i = 1; i <= n; i ++)printf("%d\n", ans[i]);
}