#include<bits/stdc++.h>
#define ls (2*x)
#define rs (2*x+1)
using namespace std;
struct seg{
	int l,r;
	long long sum;
}t[4000005];
vector<long long> link1[1000005];
int v[1000005],arr[1000005],lx[1000005],rx[1000005];
long long n,m,r,tot=0;
void pushup(long long x){
	t[x].sum=t[ls].sum+t[rs].sum;
}
void build(long long x,long long l,long long r){
	t[x].l=l;
	t[x].r=r;
	if(l==r){
		t[x].sum=arr[l];
		return;
	}
	long long mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(x);
}
void dfs(long long u,long long pr){
	if(u==0) return;
	lx[u]=++tot;
	arr[tot]=v[u];
	long long vv;
	for(long long i=0;i<link1[u].size();i++){
		vv=link1[u][i];
		if(vv!=pr) dfs(vv,u);
	}
	rx[u]=tot;
}
void update(long long x,long long pos,long long d){
	if(pos>=t[x].l&&pos<=t[x].r){
		t[x].sum+=d;
	}
	if(t[x].l==t[x].r) return;
	long long mid=(t[x].l+t[x].r)>>1;
	if(pos<=mid) update(ls,pos,d);
	else update(rs,pos,d);
}
long long query(long long x,long long l,long long r){
	if(l<=t[x].l&&r>=t[x].r) return t[x].sum;
	long long mid=(t[x].l+t[x].r)/2;
	if(r<=mid) return query(ls,l,r);
	else if(l>mid) return query(rs,l,r);
	return (query(ls,l,r)+query(rs,l,r));
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>r;
	for(long long i=1;i<=n;i++){
		cin>>v[i];
	}
	for(long long i=1;i<n;i++){
		long long p,q;
		cin>>p>>q;
		link1[p].push_back(q);
		link1[q].push_back(p); 
	}
	dfs(r,0);
	build(1,1,n);
	for(long long i=1,temp,a,x;i<=m;i++){
		cin>>temp;
		if(temp==1){
			cin>>a>>x;
			update(1,lx[a],x);
		}else{
			cin>>a;
			cout<<query(1,lx[a],rx[a])<<'\n';
		}
	}
	return 0;
}
