#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<map>
#include<unordered_map>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
#define DE(fmt,...) fprintf(stderr, "Line %d : " fmt "\n",__LINE__,##__VA_ARGS__)
using namespace std;
typedef long long ll;
typedef __int128 i128;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pll>vpll;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}

mt19937_64 rnd(0);
ll rd(ll a,ll b){return a+rnd()%(b-a+1);}
ll p;
inline ll add(ll x,ll y){return (x+y>=p)?(x+y-p):(x+y);}
inline ll del(ll x,ll y){return (x<y)?(x-y+p):(x-y);}
ll ksm(ll x,ll y){
	ll s=1;
	while(y){
		if(y&1)s=(i128)s*x%p;
		x=(i128)x*x%p;
		y>>=1;
	}
	return s;
}
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1;y=0;return a;}
	ll tx,ty,g=exgcd(b,a%b,tx,ty);
	x=ty;y=tx-(i128)a/b*ty;
	return g;
}
ll q,w,z,K;
ll fac[100010],inv[100010];
ll pw[100010];
ll solve(ll a,ll k,ll t,ll r){

	if(k==0){
		ll x,y;
		exgcd(t,q,x,y);
		return ksm(a,(((i128)((-x)%q+q)%q)*t+1)/q);
	}
	ll v=ksm(a,r/q);
	if(v==1)return solve(a,k-1,t,r/q);
	int B=ceil(sqrt((long long)q));
	fac[0]=1;
	for(int i=1;i<=B;i++)
		fac[i]=(i128)fac[i-1]*z%p;
	inv[B]=ksm(fac[B],p-2);
	for(int i=B-1;~i;--i)inv[i]=(i128)inv[i+1]*z%p;
	unordered_map<ll,ll>vis;
	for(int i=0;i<=B;i++)vis[inv[i]]=i;
	ll now=1,zB=fac[B],b=-1;
	for(int i=0;;i++){
		ll s=(i128)now*v%p;
		if(vis.find(s)!=vis.end()){
			b=vis[s]+i*B;
			break;
		}
		now=(i128)now*zB%p;
	}
	ll z0=ksm(w,pw[K-1-k]*b);
	ll _a=(i128)a*ksm(z0,q)%p;
	ll _x=solve(_a,k-1,t,r/q);
	return (i128)_x*ksm(z0,p-2)%p;
}
void solve(){
	ll a;q=3;
	read(a,p);
	ll k=0,t;
	{
		ll x=p-1;
		while(x%q==0)x/=q,++k;
		t=x;
	}
	K=k;
	pw[0]=1;
	for(int i=1;i<=K;i++)pw[i]=pw[i-1]*q;
	if(k==0){
		long long ans=solve(a,k,t,p-1);
		cout << ans << '\n';
		return ;
	}
	if(k>=1){
		if(ksm(a,(p-1)/q)!=1){
			puts("0");
			return ;
		}
		w=rd(1,p-1);
		z=ksm(w,(p-1)/q);
		while(z==1){
			w=rd(1,p-1);
			z=ksm(w,(p-1)/q);
		}
	}
	long long ans=solve(a,k-1,t,(p-1)/q);
	cout << ans << '\n';
}
signed main(){
	#ifdef do_while_true


	#endif
	int T;read(T);
	while(T--)solve();	
    #ifdef do_while_true

	#endif
	return 0;
}