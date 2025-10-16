#include<bits/stdc++.h>
#define ll long long
#define lc (p<<1)
#define rc (p<<1|1)
using namespace std;
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
char buf[1<<20],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
Tp inline void read(T& x){
    x=0;char c=getchar();bool f=0;
    for(;c<48||c>57;c=getchar())c=='-'&&(f=1);
    for(;c>47&&c<58;c=getchar())x=(x<<1)+(x<<3)+(c^48);
    f&&(x=-x);
}
Ts inline void read(T& x,_T&... y){read(x),read(y...);}
const int N=1e6+1;
struct edge{int y,pre;}a[N<<1];int alen,last[N];
inline void ins(int x,int y){alen++;a[alen]={y,last[x]};last[x]=alen;}
int n,m,root;ll w[N],val[N];
int dfn[N],id,R[N],dep[N],par[N][20];
struct Seg{int l,r;ll add,ls;}tr[N<<2];
void down(int p,ll x,ll y){
	tr[p].add+=x;
	tr[p].ls+=y;
}
void pushdown(int p){
	down(lc,tr[p].add,tr[p].ls);
	down(rc,tr[p].add,tr[p].ls);
	tr[p].add=tr[p].ls=0;
}
void bt(int p,int l,int r){
	tr[p]={l,r,0,0};
	if(l==r)return;
	int mid=l+r>>1;
	bt(lc,l,mid);bt(rc,mid+1,r);
}
void change1(int p,int l,int r,ll k){
	if(l<=tr[p].l&&r>=tr[p].r){
		tr[p].add+=k;
		return;
	}
	int mid=tr[p].l+tr[p].r>>1;
	if(l<=mid)change1(lc,l,r,k);
	if(r>mid)change1(rc,l,r,k);
}
void change2(int p,int l,int r,ll k){
	if(l<=tr[p].l&&r>=tr[p].r){
		tr[p].add-=k*(dep[l]-1);
		tr[p].ls+=k;
		return;
	}
	int mid=tr[p].l+tr[p].r>>1;
	if(l<=mid)change2(lc,l,r,k);
	if(r>mid)change2(rc,l,r,k);
}
ll solve(int p,int x){
	if(tr[p].l==tr[p].r){
		return dep[tr[p].l]*tr[p].ls+tr[p].add;
	}
	pushdown(p);
	int mid=tr[p].l+tr[p].r>>1;
	if(x<=mid)return solve(lc,x);
	return solve(rc,x);
}
inline void dfs(int x,int fa){
	dfn[x]=++id;
	par[dfn[x]][0]=dfn[fa];
	dep[dfn[x]]=dep[dfn[fa]]+1;
	for(int i=1;i<=19;i++)par[dfn[x]][i]=par[par[dfn[x]][i-1]][i-1];
	for(int k=last[x];k;k=a[k].pre){
		int y=a[k].y;
		if(y!=fa)dfs(y,x);
	}
	R[x]=id;
}
inline int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;i--){
		if(dep[par[x][i]]>=dep[y])x=par[x][i];
	}
	if(x==y)return y;
	for(int i=19;i>=0;i--){
		if(par[x][i]!=par[y][i]){
			x=par[x][i],y=par[y][i];
		}
	}
	return par[x][0];
}
int main(){
	read(n,m,root);
	for(int i=1;i<=n;i++)read(w[i]);
	for(int i=1;i<n;i++){
		int x,y;read(x,y);
		ins(x,y);ins(y,x);
	}
	dfs(root,0);
	for(int i=1;i<=n;i++)val[dfn[i]]=w[i];
	bt(1,1,n);
	for(int i=1;i<=n;i++)change1(1,dfn[i],R[i],w[i]);
	while(m--){
		int op,x;ll y;read(op,x,y);
		if(op==1)change1(1,dfn[x],R[x],y);
		else if(op==2)change2(1,dfn[x],R[x],y);
		else{
			int lca=LCA(dfn[x],dfn[y]);
			printf("%lld\n",solve(1,dfn[x])+solve(1,dfn[y])-solve(1,lca)-(lca==dfn[root]?0:solve(1,par[lca][0])));
		}
	}
	return 0;
}