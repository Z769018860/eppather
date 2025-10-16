







#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define inf 1e9
#define pii pair<int,int>
#define F(i,a,b) for(int i=a;i<=(b);i++)
#define dF(i,a,b) for(int i=a;i>=(b);i--)
#define wh(lzm) while(lzm--)
#define lowbit(x) (x&(-x))
#define HH printf("\n")
#define eb emplace_back
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
const int mod=998244353,maxn=500005;
namespace DSU{
	tuple<int,int>st[maxn];
	int top,sz[maxn],fa[maxn];
	void init(int N){
		top=0;
		F(i,1,N) fa[i]=i,sz[i]=1;
	}
	int find(int x){
		return fa[x]==x?x:x=find(fa[x]);
	}
	void merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y) return;
		if(sz[x]>sz[y]) swap(x,y);
		st[++top]=make_tuple(x,y);
		fa[x]=y;
		sz[y]+=sz[x];
	}
	void rickroll(int lst){
		for(;top>lst;--top){
			auto [x,y]=st[top];
			fa[x]=x;
			sz[y]-=sz[x];
		}
	}
}
using namespace DSU;
int n,m;
map<pii,int>mp;
vector<int>t[maxn<<2];
#define ls (o<<1)
#define rs (o<<1|1)
struct node{
	int op,u,v;
}q[maxn];
void update(int o,int l,int r,int ql,int qr,int x){
	if(ql<=l&&qr>=r) return t[o].push_back(x),void();
	int mid=(l+r)>>1;
	if(ql<=mid) update(ls,l,mid,ql,qr,x);
	if(qr>mid) update(rs,mid+1,r,ql,qr,x);
}
void solve(int o,int l,int r){
	int lst=top;
	for(int x:t[o]) merge(q[x].u,q[x].v);
	if(l==r){
		if(q[l].op==2) puts(find(q[l].u)==find(q[l].v)?"Y":"N");
		rickroll(lst);
		return;
	}
	int mid=(l+r)>>1;
	solve(ls,l,mid),solve(rs,mid+1,r),rickroll(lst);
}
signed main(){
	n=read(),m=read();
	init(n);
	F(i,1,m){
		int op=read(),u=read(),v=read();
		if(u>v) swap(u,v);
		if(!op) mp[{u,v}]=i;
		if(op&1) update(1,1,m,mp[{u,v}],i-1,i),mp.erase({u,v});
		q[i]=(node){op,u,v};
	}
	for(auto it:mp) update(1,1,m,it.second,m,it.second);
	solve(1,1,m);
}