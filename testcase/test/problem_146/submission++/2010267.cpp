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
struct Seg{int l,r;ll sum,sd;}tr[N<<2];
inline void pushup(int p){
	tr[p].sum=tr[lc].sum+tr[rc].sum;
	tr[p].sd=tr[lc].sd+tr[rc].sd;
}
inline void bt(int p,int l,int r){
	tr[p]={l,r,0,0};
	if(l==r)return;
	int mid=l+r>>1;
	bt(lc,l,mid);bt(rc,mid+1,r);
	pushup(p);
}
inline void change(int p,int x,ll k){
	if(tr[p].l==tr[p].r){
		tr[p].sum+=k;
		tr[p].sd+=k*dep[tr[p].l];
		return;
	}
	int mid=tr[p].l+tr[p].r>>1;
	if(x<=mid)change(lc,x,k);
	else change(rc,x,k);
	pushup(p);
}
Seg solve(int p,int l,int r){
	if(l<=tr[p].l&&r>=tr[p].r)return tr[p];
	int mid=tr[p].l+tr[p].r>>1;
	Seg ans={0,0,0,0};
	if(l<=mid){
		Seg ls=solve(lc,l,r);
		ans.sum+=ls.sum;ans.sd+=ls.sd;
	}
	if(r>mid){
		Seg rs=solve(rc,l,r);
		ans.sum+=rs.sum;ans.sd+=rs.sd;
	}
	return ans;
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
	for(int i=1;i<=n;i++)val[i]+=val[i-1];
	bt(1,1,n);
	while(m--){
		int op;read(op);
		if(op==1){
			int x,y;ll k;read(x,y,k);
			change(1,dfn[x],k);change(1,dfn[y],k);
			int lca=LCA(dfn[x],dfn[y]);
			change(1,lca,-k);
			if(lca!=dfn[root])change(1,par[lca][0],-k);
		}
		else{
			int x;read(x);
			Seg ans=solve(1,dfn[x],R[x]);
			if(op==2)printf("%lld\n",ans.sum+val[dfn[x]]-val[dfn[x]-1]);
			else printf("%lld\n",ans.sd-ans.sum*(dep[dfn[x]]-1)+val[R[x]]-val[dfn[x]-1]);
		}
	}
	return 0;
}