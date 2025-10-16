#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int n = 0, m = 0, deg[N] = {}, cnt[N] = {};
long long ans = 0;
vector<int> G[N] = {}, Gx[N] = {};

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1, u = 0, v = 0 ; i <= m ; i ++){
		scanf("%d %d", &u, &v);
		G[u].push_back(v), G[v].push_back(u);
		deg[u] ++, deg[v] ++;
	}
	for(int u = 1 ; u <= n ; u ++) for(int v : G[u]) if(deg[u] > deg[v] || (deg[u] == deg[v] && u < v)) Gx[u].push_back(v);
	for(int u = 1 ; u <= n ; u ++){
		for(int v : Gx[u]) for(int w : G[v]) if(deg[u] > deg[w] || (deg[u] == deg[w] && u < w)) ans += cnt[w] ++;
		for(int v : Gx[u]) for(int w : G[v]) cnt[w] = 0;
	}
	printf("%lld\n", ans);
	return 0;
}
