#include<bits/stdc++.h>
#define debug(a) cerr<<"Line: "<<__LINE__<<" "#a<<endl
#define print(a) cerr<<#a"="<<(a)<<endl
#define sign() puts("---------")
#define int long long
using namespace std;
const int N = 1e6+10;
int n,m,r,siz[N],dfn[N],v[N];
vector<int> e[N];
struct Binary_tree{
	#define lowbit(a) (a&(-a))
	int sum[N];






	void add(int x,int v){
		for(int i = x;i<=n;i += lowbit(i))sum[i] += v;
	}
	int query(int x){
		int res = 0;
		for(int i = x;i;i -= lowbit(i))res += sum[i];
		return res;
	}
	int query(int l,int r){
		return query(r)-query(l-1);
	}
}tr;
void dfs(int u,int f){
	siz[u] = 1;
	dfn[u] = ++dfn[0];
	tr.add(dfn[u],v[u]);
	for(int v:e[u])if(v != f){
		dfs(v,u);
		siz[u] += siz[v];
	}
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&r);
	for(int i = 1;i<=n;++i)scanf("%lld",&v[i]);
	for(int i = 1,u,v;i<n;++i){
		scanf("%lld%lld",&u,&v);
		e[u].push_back(v),e[v].push_back(u);
	}
	dfs(r,0);
	int op,a,x;
	while(m--){
		scanf("%lld",&op);
		if(op == 1){
			scanf("%lld%lld",&a,&x);
			tr.add(dfn[a],x);
		}else{
			scanf("%lld",&a);
			printf("%lld\n",tr.query(dfn[a],dfn[a]+siz[a]-1));
		}
	}
	return 0;
}