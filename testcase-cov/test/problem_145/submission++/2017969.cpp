#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
vector<int> q[N];
int st[N],en[N],tmp=0;
int n,m,r,b[N];
long long sum[N<<2],lazy[N<<2];
int mp[N];
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
		x=x*10+ch-'0',ch=getchar();
	return x*f;
}
void dfs(int u, int fa) {
	st[u]=++tmp;
	mp[tmp] = u;
	for(auto v:q[u]) {
		if(v==fa) continue;
		dfs(v,u);
	}
	en[u]=tmp;
}
int a[1005],c[1005];
void pushup(int i) {
	sum[i]=sum[i<<1]+sum[i<<1|1];
}
void up(int i,long long len,long long v) {
	sum[i]+=len * v;
	lazy[i]+=v;
}
void pushdown(int i,int l,int r) {
	int mid=(l+r)/2;
	if(lazy[i]) {
		up(i<<1,mid-l+1,lazy[i]);
		up(i<<1|1,r-mid,lazy[i]);
		lazy[i] = 0;
	}
}
void build(int i,int l,int r) {
	if(l==r) {
		sum[i] = b[mp[l]];
		return ;
	}
	int mid=(l+r)/2;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	pushup(i);
}
void zeng(int i,int ql,int qr,int l,int r,int v) {
	if(ql<=l && qr >=r) {
		up(i,r-l+1,v);
		return ;
	}
	int mid=(l+r)/2;
	pushdown(i,l,r);
	if(ql<=mid)
		zeng(i<<1,ql,qr,l,mid,v);
	if(qr>mid)
		zeng(i<<1|1,ql,qr,mid+1,r,v);
	pushup(i);
}
long long he(int i,int ql,int qr,int l,int r) {
	if(ql<=l && qr >=r) {
		return sum[i];
	}
	int mid=(l+r)/2;
	pushdown(i,l,r);
	long long ans = 0;
	if(ql<=mid)
		ans+=he(i<<1,ql,qr,l,mid);
	if(qr>mid)
		ans+=he(i<<1|1,ql,qr,mid+1,r);
	return ans;
}
int main() {
	n=read(),m=read(),r=read();
	for(int i=1; i<=n; i++) {
		b[i]=read();
	}
	int x,y;
	for(int i=1; i<n; i++) {
		x=read(),y=read();
		q[x].push_back(y);
		q[y].push_back(x);
	}
	dfs(r,0);
	build(1, 1, n);
	int f;
	while(m--) {
		f=read();
		if(f==1) {
			x=read(),y=read();
			zeng(1, st[x], en[x], 1, n, y);
		} else {
			x=read();
			cout<<he(1,st[x],en[x],1,n)<<endl;
		}
	}
	return 0;
}