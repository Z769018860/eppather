#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 105 , M = 1e4 + 5 , INF = 0x3f3f3f3f;
int n , m , rt , mn[N] , in[N] , id[N] , fa[N] , top[N];
ll ans; struct Edge{int u , v , w;}e[M];
bool Solve(int n , int m)
{
	while(1)
	{
		memset(mn , 0x3f , sizeof mn);
		memset(id , 0 , sizeof id);
		memset(top , 0 , sizeof top);
		for(int i = 1 ; i <= m ; i++)
		{
			auto [u , v , w] = e[i];
			if(w < mn[v])mn[v] = w , fa[v] = u;
		}
		for(int i = 1 ; i <= n ; i++)
		{
			if(i != rt)
			{
				if(mn[i] == INF)return 0;
				ans += mn[i];
			}
		}
		int cnt = 0 , tot = 0;
		for(int i = 1 ; i <= n ; i++)
		{
			if(id[i] || i == rt)continue ;
			int u = i;
			while(u != rt && top[u] != i && !id[u])
				top[u] = i , u = fa[u];
			if(u != rt && !id[u])
			{
				id[u] = ++cnt;
				for(int v = fa[u] ; v != u ; v = fa[v])
					id[v] = cnt;
			}
		}
		if(!cnt)return 1;
		for(int i = 1 ; i <= n ; i++)if(!id[i])id[i] = ++cnt;
		for(int i = 1 ; i <= m ; i++)
		{
			auto [u , v , w] = e[i];
			if(id[u] == id[v])continue ;
			e[++tot] = {id[u] , id[v] , w - mn[v]};
		}
		n = cnt , m = tot , rt = id[rt];
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0) , cout.tie(0);
	cin >> n >> m >> rt;
	for(int i = 1 ; i <= m ; i++)
		cin >> e[i].u >> e[i].v >> e[i].w;
	if(Solve(n , m))cout << ans << "\n";
	else cout << "-1\n";
	return 0;
}