#include<bits/stdc++.h>
#define debug(a) cerr<<"Line: "<<__LINE__<<" "#a<<endl
#define print(a) cerr<<#a"="<<(a)<<endl
#define sign() puts("---------")
using namespace std;
const int N = 1e6+10;
int n,m,r,siz[N],dfn[N],to[N];
long long v[N];
vector<int> e[N];
struct Date{
	int l,r;
	long long sum,lazy;
}tr[N<<2];
#define ls (p<<1)
#define rs (p<<1|1)
#define len(p) (tr[p].r-tr[p].l+1)
#define mid ((tr[p].r+tr[p].l)>>1)
void pushup(int p){
	tr[p].sum = tr[ls].sum + tr[rs].sum;
}
void pushdown(int p){
	if(tr[p].lazy){
		tr[ls].sum += tr[p].lazy*len(ls),tr[ls].lazy += tr[p].lazy;
		tr[rs].sum += tr[p].lazy*len(rs),tr[rs].lazy += tr[p].lazy;
		tr[p].lazy = 0;
	}
}
void build(int p,int l,int r){
	tr[p].l = l,tr[p].r = r,tr[p].sum = tr[p].lazy = 0;
	if(l == r){
		tr[p].sum = v[to[l]];
		return ;
	}
	build(ls,l,mid),build(rs,mid+1,r),pushup(p);
}
void add(int p,int l,int r,long long v){
	if(l <= tr[p].l && tr[p].r <= r){
		tr[p].sum += 1ll*len(p)*v;
		tr[p].lazy += v;
		return ;
	}
	pushdown(p);
	if(l <= mid)add(ls,l,r,v);
	if(mid < r)add(rs,l,r,v);
	pushup(p);
}
long long query(int p,int l,int r){
	if(l <= tr[p].l && tr[p].r <= r)return tr[p].sum;
	long long res = 0;
	pushdown(p);
	if(l <= mid)res += query(ls,l,r);
	if(mid < r)res += query(rs,l,r);
	return res;
}
void dfs(int u,int f){
	siz[u] = 1;
	dfn[u] = ++dfn[0];
	to[dfn[u]] = u;
	for(int v:e[u])if(v != f){
		dfs(v,u);
		siz[u] += siz[v];
	}
}
signed main(){
	scanf("%d%d%d",&n,&m,&r);
	for(int i = 1;i<=n;++i)scanf("%lld",&v[i]);
	for(int i = 1,u,v;i<n;++i){
		scanf("%d%d",&u,&v);
		e[u].push_back(v),e[v].push_back(u);
	}
	dfs(r,0);
	build(1,1,n);
	int op,a;
	long long x;
	while(m--){
		scanf("%d",&op);
		if(op == 1){
			scanf("%d%lld",&a,&x);
			add(1,dfn[a],dfn[a]+siz[a]-1,x);
		}else{
			scanf("%d",&a);
			printf("%lld\n",query(1,dfn[a],dfn[a]+siz[a]-1));
		}
	}
	return 0;
}