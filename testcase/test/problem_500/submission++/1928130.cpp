#include<bits/stdc++.h>
using namespace std;
int rd(int x=0,char c=getchar()){int f=1;while(!isdigit(c))f=(c^'-'?1:-1),c=getchar();while(isdigit(c))x=x*10+(c^48),c=getchar();return x*f;}
const int N=102;using ll=long long;
int n,m;ll a[N],b[N],f[N][N];
bool check(ll x){
	memset(f,-127,sizeof f);f[0][0]=0;
	for(int i=1;i<=n;i++)for(int j=0;j<=m;j++)for(int k=0;k<=j;k++){
		if(x-a[i]*(j-k)>=0)f[i][j]=max(f[i][j],f[i-1][k]+(x-a[i]*(j-k))/b[i]);
	}return f[n][m]>=m;
}
int main(){
	n=rd();m=rd();
	for(int i=1;i<=n;i++)a[i]=rd(),b[i]=rd();
	ll l=1,r=1e8,ans=1e8;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}printf("%lld",ans);
	return 0;
}