
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=110;
const double eps=1e-9;
ll n,m,f[N][N],i,j,a[N],b[N],k,l,r;
bool check(ll s){

	memset(f,128,sizeof f);
	f[0][0]=0;
	for(i=1;i<=n;++i){
		for(j=0;j<=m;++j){
			double x=1.0*s/a[i],y=1.0*s/b[i];
			for(k=max(j-(ll)floor(x),0ll);k<=j;++k){
				ll ad=1.0*(x-(j-k))/x*y;
				f[i][j]=max(f[i][j],f[i-1][k]+ad);
			}

		}
	}
	return f[n][m]>=m;
}
ll ans;
int main(){
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=n;++i)scanf("%lld%lld",a+i,b+i);
	l=1,r=1e10;
	while(l<=r){

		ll mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld",ans);
	return 0;
}
