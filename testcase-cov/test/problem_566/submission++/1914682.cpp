#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5,M=5e5+5;
int n,m,k,fa[N];
ll ans,res;
struct edge{
	int x,y,z;
	bool operator <(const edge a)const{return z<a.z;}
}e[M];
int gf(int x){
	return fa[x]==x?fa[x]:fa[x]=gf(fa[x]);
}
bool check(int d){
	int cl=0,tot=0;ans=0;
	for(int i=1;i<=n;++i)fa[i]=i;
	for(int l=1,r=m,p;tot<k<<1;){
		bool fg=false;
		if(d-e[l].z>e[r].z)p=l,++l,fg=true;
		else p=r,--r;
		int x=gf(e[p].x),y=gf(e[p].y);
		if(x==y)continue;
		if(fg)++cl,ans+=d-e[p].z;
		else ans+=e[p].z;
		++tot,fa[x]=y;
	}
	ans-=1ll*k*d;
	return cl<=k;
}
int main(){
	scanf("%d%d",&n,&m);
	k=n-1>>1;
	for(int i=1;i<=m;++i)scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].z);
	sort(e+1,e+m+1);
	int l=1,r=2e9+7;
	while(l<r){
		int mid=(ll)l+r>>1;
		if(check(mid))l=mid+1,res=ans;
		else r=mid;
	}
	printf("%lld\n",res);
	return 0;
}