#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll N=3300000;
const ll mod=998244353;
ll n,m,ans,vL,vR,vS;
ll mu[N],pri[N/8],tot;bool vis[N];
inline void read(ll &x)
{
	ll f=1;char c;
	for(x=0,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48); x*=f;
}
inline ll mn(ll _x,ll _y){return _x<_y?_x:_y;}
inline ll mx(ll _x,ll _y){return _x>_y?_x:_y;}
inline ll ab(ll _x){return _x<0?-_x:_x;}
inline void Sieve(){
	mu[1]=1;
	for(int i=2;i<=N;i++){
		if(!vis[i]){mu[i]=-1;pri[++tot]=i;}
		for(int j=1;j<=tot&&pri[j]<=N/i;j++){
			int v=i*pri[j];vis[v]=true;
			if(i%pri[j]) mu[v]=-mu[i];
			else break;
		}
	}
	for(int i=1;i<=N;i++)
		if(mu[i]==-1) mu[i]+=mod;
	return ;
}
int main()
{
	read(n);read(m);if(n>m) swap(n,m);
	Sieve();
	vL=1;vR=0;vS=0;
	for(ll l=1,r;l<=n;l=r+1){
		r=mn(n/(n/l),m/(m/l));
		while((vR+1)*(vR+1)<=r){++vR;vS=(vS+mu[vR])%mod;}
		while(vL*vL<l){vS=(vS-mu[vL]+mod)%mod;++vL;}
		ans=(ans+1ll*vS*((n/l)%mod)%mod*((m/l)%mod)%mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}

