#include<bits/stdc++.h>
using namespace std;
int n,m,P;
int fa[201000];
int F(int x){
	if(x==fa[x])return x;
	return fa[x]=F(fa[x]);
}
#define ll long long
struct qq{int u,v;ll w;int t;}b[500100],a[1001000];
bool cmp(qq a,qq b){return a.w<b.w;}
ll qd;int ks;
bool check(ll x){
	int i1=m,i2=1,i=0;
	while(i1&&i2<=m){
		if(b[i1].w>x-b[i2].w)a[++i]=b[i1],a[i].t=1,i1--;
		else a[++i]=b[i2],a[i].w=x-a[i].w,a[i].t=-1,i2++;
	}
	while(i1)a[++i]=b[i1],a[i].t=1,i1--;
	while(i2<=m)a[++i]=b[i2],a[i].w=x-a[i].w,a[i].t=-1,i2++;
	for(i=1;i<=n;i++)fa[i]=i;
	int j=0;qd=0,ks=0;
	for(i=1;i<=m*2&&j<P*2;i++){
		if(F(a[i].u)!=F(a[i].v)){
			j++;
			ks+=(a[i].t==-1),qd+=a[i].w;
			fa[F(a[i].u)]=F(a[i].v);
		}
	}
	return ks>=P;
}
int main(){
	scanf("%d%d",&n,&m);P=(n-1)/2;
	for(int i=1;i<=m;i++)scanf("%d%d%lld",&b[i].u,&b[i].v,&b[i].w);
	sort(b+1,b+m+1,cmp);
	ll l=0,r=2e9+10,ans;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(mid))ans=qd-1ll*mid*P,r=mid-1;
		else l=mid+1;
	}
	return printf("%lld",ans),0;
} 