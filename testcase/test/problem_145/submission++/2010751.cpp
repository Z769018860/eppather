bool _Start;
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
Tp il void read(T& x) {
	x=0;bool f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}Ts il void read(T& x,_T&... y) {read(x),read(y...);}
using ll=long long;
const int N=1e6+5; 
int n,m,rt,val[N];
struct edge {
	int x,y,pre;
}a[N<<1];int alen,last[N];
il void ins(int x,int y) {
	a[++alen]=edge{x,y,last[x]};
	last[x]=alen;
}
int dfn[N],siz[N],tsp;
void dfs(int x,int fa) {
	dfn[x]=++tsp,siz[x]=1;
	for(int k=last[x];k;k=a[k].pre) {
		int y=a[k].y;
		if(y==fa) continue;
		dfs(y,x);
		siz[x]+=siz[y];
	}
}
struct Seg {
	int ls,rs;
	ll sum,lz;
}seg[N<<1];int trlen;
il void pushup(int p) {seg[p].sum=seg[seg[p].ls].sum+seg[seg[p].rs].sum;}
il void pushdown(int l,int r,int p) {
	if(!seg[p].lz) return ;
	ll lz=seg[p].lz;
	int mid=(l+r)>>1,ls=seg[p].ls,rs=seg[p].rs;
	seg[ls].sum+=(mid-l+1)*lz,seg[rs].sum+=(r-mid)*lz;
	seg[ls].lz+=lz,seg[rs].lz+=lz;
	seg[p].lz=0; 
}
int bt(int l,int r) {
	int p=++trlen;
	if(l==r) return p;
	int mid=(l+r)>>1;
	seg[p].ls=bt(l,mid);
	seg[p].rs=bt(mid+1,r);
	pushup(p);
	return p;
}
void change(int l,int r,int p,int x,int y,ll k) {
	if(l>=x&&r<=y) {
		seg[p].sum+=(r-l+1)*k,seg[p].lz+=k;
		return ;
	}
	pushdown(l,r,p);
	int mid=(l+r)>>1;
	if(x<=mid) change(l,mid,seg[p].ls,x,y,k);
	if(y>mid) change(mid+1,r,seg[p].rs,x,y,k);
	pushup(p);
}
ll query(int l,int r,int p,int x,int y) {
	if(l>=x&&r<=y) return seg[p].sum;
	pushdown(l,r,p);
	int mid=(l+r)>>1;
	ll res=0;
	if(x<=mid) res+=query(l,mid,seg[p].ls,x,y);
	if(y>mid) res+=query(mid+1,r,seg[p].rs,x,y);
	return res;
}
bool _End;
int main() {
	fprintf(stderr,"Memory: %.4lf Mib\n",abs(&_End-&_Start)/1048576.0);
	read(n,m,rt);
	for(int i=1;i<=n;i++) read(val[i]);
	for(int i=1;i<n;i++) {
		int x,y;read(x,y);
		ins(x,y),ins(y,x); 
	}
	dfs(rt,0);
	bt(1,n);
	for(int i=1;i<=n;i++) change(1,n,1,dfn[i],dfn[i],val[i]); 
	while(m--) {
		int op;read(op);
		if(op==1) {
			int x,k;read(x,k);
			change(1,n,1,dfn[x],dfn[x]+siz[x]-1,k);
		}
		else {
			int x;read(x);
			printf("%lld\n",query(1,n,1,dfn[x],dfn[x]+siz[x]-1)); 
		}
	}
	return 0;
}
