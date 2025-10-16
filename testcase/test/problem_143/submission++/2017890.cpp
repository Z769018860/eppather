#include<bits/stdc++.h>
#define fi first
#define se second
#define Me(x,y) memset(x,y,sizeof x)
#define Mc(x,y) memcpy(x,y,sizeof x)
#define LB lower_bound
#define UB upper_bound
#define R(n) (rnd()%(n)+1)
using namespace std;using ll=long long;using ull=unsigned ll;using db=double;using pii=pair<int,int>;
const int N=1e5+5,M=N*4,K=1e7,mod=1e9+7,Mod=mod-1;const int INF=1e9+7;mt19937 rnd(time(0));
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
namespace Debug{
	Tp void _debug(char *f,T x){cerr<<f<<'='<<x<<'\n';}
	Ts void _debug(char *f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x;_debug(f,y...);}
	#ifdef LOCAL
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
	#else 
	#define gdb(...) void()
	#endif
}using namespace Debug;
using LL=__int128;
ll mpow(ll x,ll y,ll p){ll ans=1;while(y) y&1&&(ans=(LL)ans*x%p),y>>=1,x=(LL)x*x%p;return ans;}
int ckp(ll n){
	if(n%2==0||n<2) return n==2;
	mt19937_64 rnd(263082);
	int i,lim=10;
	ll y=n-1;int ti=0;while(y%2==0) y>>=1,ti++;
	while(lim--){
		ll a=rnd()%(n-1)+1;
		a=mpow(a,y,n);if(a==1) continue;
		int flag=0;
		for(i=1;i<=ti;i++){
			if(a==n-1) break;
			a=(LL)a*a%n;
		}
		if(i==ti+1) return 0;
	}
	return 1;
}
void Solve(){
	ll x;while(~scanf("%lld",&x)){
		puts(ckp(x)?"Y":"N");
	}
}
int main(){
	int t=1;
	
	while(t--) Solve();
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<'\n';
}