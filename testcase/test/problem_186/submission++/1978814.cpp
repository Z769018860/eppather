#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,Q,a[N];
#define L tr[x][0]
#define R tr[x][1]
#define gt(x) (tr[f[x]][1]==x)
#define ck(x) (tr[f[x]][gt(x)]!=x)
#define lk(x,y,z) tr[x][z]=y,f[y]=x
int sz[N],lz[N],f[N],tr[N][2];
void up(int x){sz[x]=sz[L]^sz[R]^a[x];}
void ch(int x){swap(L,R),lz[x]^=1;}
void dn(int x){if(lz[x])ch(L),ch(R),lz[x]=0;}
void upd(int x){if(!ck(x))upd(f[x]);dn(x);}
void zh(int x){
	int y=f[x],z=f[y],u=gt(x);
	if(!ck(y))tr[z][gt(y)]=x;
	lk(y,tr[x][!u],u),lk(x,y,!u),f[x]=z,up(y),up(x);
}
void sp(int x){
	upd(x);
	for(;!ck(x);zh(x))
		if(!ck(f[x]))zh(gt(x)==gt(f[x])?f[x]:x);
}
int ac(int x,int p=0){
	for(;x;p=x,x=f[x])sp(x),R=p,up(x);
	return p;
}
void mk(int x){x=ac(x),ch(x);}
int fd(int x){
	x=ac(x);while(L)x=L;sp(x);
	return x;
}
void li(int x,int y){if(fd(x)!=fd(y))mk(x),f[x]=y;}
void ct(int x,int y){
	if(fd(x)!=fd(y))return;
	mk(x),ac(y),sp(x);
	if(R==y&&!tr[y][0])R=f[y]=0,up(x);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>Q;
	for(int i=1;i<=n;i++)cin>>a[i],sz[i]=a[i];
	while(Q--){
		int op,x,y;cin>>op>>x>>y;
		if(!op)mk(x),cout<<sz[ac(y)]<<'\n';
		else if(op==1)li(x,y);
		else if(op==2)ct(x,y);
		else sp(x),sz[x]^=a[x]^y,a[x]=y;
	}
	return 0;
}