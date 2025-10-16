
#include<bits/stdc++.h>
#define pb push_back
#define P make_pair
#define st first
#define nd second
using namespace std;
typedef long long ll; 
typedef unsigned long long ull; 

typedef long double ld;
typedef pair<int,int> pii; typedef pair<ll,int> pli; typedef pair<ll,ll> pll; typedef pair<int,ll> pil;
inline ll read(){
	ll x=0,f=1,c=getchar();
	while(c<'0'||c>'9')f=(c=='-'?-1:1),c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
inline void write(ll x){ if(x<0) putchar('-'),x=-x; if(x>9) write(x/10); putchar(x%10+'0'); }

const int mod=998244353;
inline void plust(int &x,int y){x=x+y<0?x+y+mod:x+y<mod?x+y:x+y-mod;}
inline void multi(int &x,int y){x=1ll*x*y%mod;}
inline int fp(int x,ll p=mod-2,int res=1){for(;p;p>>=1)multi(res,p&1?x:1),multi(x,x);return res;}
inline void ckmax(ll &x,ll y){x=max(x,y);} inline void ckmin(ll &x,ll y){x=min(x,y);}
const ll N=1e12;
const int INF=0x3fffffff;


const int B=19190506,A=fp(B),d=917504;
const int M=N/d+1;
int fac[M],inv[M];
int qfac[d],qinv[d],fq[d];
inline int binom(int n,int m){ return n>=m && m>=0?1ll*fac[n]*inv[m]%mod*inv[n-m]%mod:0; }
inline int q_binom(int n,int m){ return n>=m && m>=0?1ll*qfac[n]*qinv[m]%mod*qinv[n-m]%mod:0; }
inline void solve(){
	ll n=read(),m=read();
	int p=((n-m)%(mod-1))*(m%(mod-1))%(mod-1);
	int ans=fp(B,p);
	multi(ans,binom(n/d,m/d));
	multi(ans,q_binom(n%d,m%d));
	printf("%d\n",ans);
}
int main() {
    
    
    
	int T=read();
	fac[0]=1;
	for(int i=1;i<M;++i)fac[i]=1ll*fac[i-1]*i%mod;
	inv[M-1]=fp(fac[M-1]);
	for(int i=M-2;~i;--i)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	fq[0]=1;
	for(int i=1;i<d;++i)fq[i]=1ll*fq[i-1]*A%mod;
	qfac[0]=1;
	for(int i=1;i<d;++i)qfac[i]=1ll*qfac[i-1]*(fq[i]-1)%mod;
	qinv[d-1]=fp(qfac[d-1]);
	for(int i=d-2;~i;--i)qinv[i]=1ll*qinv[i+1]*(fq[i+1]-1)%mod;
	while(T--)solve();
    return 0;
}
