#include<bits/stdc++.h>
#define Gc() getchar()
#define Me(x,y) memset(x,y,sizeof(x))
#define Mc(x,y) memcpy(x,y,sizeof(x))
#define d(x,y) ((m)*(x-1)+(y))
#define R(n) (rnd()%(n)+1)
#define Pc(x) putchar(x)
#define LB lower_bound
#define UB upper_bound
#define fi first
#define se second
#define eb emplace_back
#define all(x) x.begin(),x.end()
using namespace std;using ll=long long;using db=double;using lb=long db;using ui=unsigned;using ull=unsigned long long;using pii=pair<int,int>;
const int N=1.5e5+5,M=N*10+5,K=1000+5,mod=998244353,Mod=mod-1;const db eps=1e-9;const int INF=1e9+7;mt19937 rnd(263082);
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#ifdef LOCAL
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
	#else 
	#define gdb(...) void()
	#endif
}using namespace Debug;
int n;
ll f[51];
void Solve(){
	int i,j;scanf("%d",&n);int flag=0;
	for(i=1;i<=n;i++){
		ll x;scanf("%lld",&x);
		for(int j=50;~j;j--) if(x>>j&1){
			if(!f[j]){f[j]=x;break;}
			x^=f[j]; 
		}
		if(!x) flag=1;
	}
	int cnt=0;
	for(i=50;~i;i--) if(f[i]){
		cnt++;for(j=i+1;j<=50;j++) if(f[j]>>i&1) f[j]^=f[i];
	}
	int q;scanf("%d",&q);while(q--){
		ll k;scanf("%lld",&k);k-=flag;
		if((1ll<<cnt)-1<k) {puts("-1");continue;}
		ll ans=0;
		for(int j=0;j<=50;j++) if(f[j]){
			if(k&1) ans^=f[j];k>>=1;
		} 
		printf("%lld\n",ans);
	}
}
int main(){
	int t=1;
	
	while(t--) Solve();
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<'\n';
}