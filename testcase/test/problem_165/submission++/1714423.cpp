#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define rd(i,n) for(int i=0;i<n;i++)
#define rp(i,n) for(int i=1;i<=n;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=max(a,b);i>=min(a,b);i--)
#define st string
#define vt vector
#define pb push_back

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
namespace number_theory{
	struct hash_table{
		#define S 1919810
		#define N 1000005
		vector<int>used;
		int sz=0,hd[S+5],id[N],nxt[N],w[N];
		inline void ins(int k,int val){
			int u=k%S;
			for(int i=hd[u];i;i=nxt[i])if(id[i]==k)return (void)(w[i]=val);
			++sz,nxt[sz]=hd[u],w[sz]=val,id[sz]=k,hd[u]=sz;
			used.push_back(u);
		}
		inline int qry(int k){
			for (int i=hd[k%S];i;i=nxt[i])if(id[i]==k)return w[i];
			return -1;
		}
		inline void flush(){
			sz=0;
			for(int i:used)hd[i]=0;
		}
	};
	bool isprime[1000005];
	int prime[100005],pricnt=0;
	inline void init_prime(){
		isprime[1]=1;
		for(ll i=2;i<=1000000;i++){
			if(!isprime[i])prime[++pricnt]=i;
			for(int j=1;j<=pricnt&&prime[j]*i<=1000000;j++){
				isprime[prime[j]*i]=1;
				if(i%prime[j]==0)break;
			}
		}
	}
	inline int fast_pow(int a,int b,int p){
		int cyr=1;
		for(;b;b>>=1){
			if(b&1)cyr=1ll*cyr*a%p;
			a=1ll*a*a%p;
		}
		return cyr;
	}
	inline int inversion(int a,int p){
		return fast_pow(a,p-2,p);
	}
	inline void prime_factorize(int n,vector<int>&v){
		int m=n;
		for(int a=2;a*a<=n;++a)if(m%a==0){
			for (v.push_back(a);m%a==0;m/=a);
		}
		if(m>1)v.push_back(m);
	}
	inline int phi(int n){
		vector<int>v;int res=n;
		prime_factorize(n,v);
		for(int i:v)res=res/i*(i-1);
		return res;
	}
	inline int primitive_root(int n){
		int m=phi(n);vector<int>v;
		prime_factorize(m,v);
		for(int i=1;i<n;i++){
			if(fast_pow(i,m,n)!=1)continue;
			bool flag=1;
			for(int j:v)if(fast_pow(i,m/j,n)==1){flag=0;break;}
			if(flag)return i;
		}
		return -1;
	}
	inline int BSGS(int a,int b,int p,int k=1){
		hash_table table;
		int B=(int)sqrt(p),bi=fast_pow(a,B,p),cyr=b;
		for(int i=0;i<B;i++,cyr=1ll*cyr*a%p){
			table.ins(cyr,i);
		}cyr=1ll*k*bi%p;
		for(int i=1;i<=B+2;i++,cyr=1ll*cyr*bi%p){
			int id=table.qry(cyr);
			if(id!=-1){
				table.flush();
				return i*B-id;
			}
		}table.flush();
		return -1;
	}
	inline int exBSGS(int a,int b,int p){
		int cnt=1,k=1;
		for(int g=(__gcd(a,p));g>1;g=(__gcd(a,p)),cnt++){
			if(b%g!=0){
				return -1;
			}
			b/=g,p/=g,k=1ll*k*(a/g)%p;
			if(k==b)return cnt;
		}
		int res=BSGS(a,b,p,k);
		if(res==-1)return -1;
		return res+cnt-1;
	}
	int fac[200005],ifac[200005];
	inline void init_fac(int p){
		fac[0]=ifac[0]=1;
		for(int i=1;i<=p-1;i++)fac[i]=1ll*fac[i-1]*i%p;
		for(int i=1;i<=p-1;i++)ifac[i]=1ll*ifac[i-1]*fac[i]%p;
		ifac[p-1]=inversion(ifac[p-1],p);
		for(int i=p-1;i>=1;i--){
			int tmp=ifac[i];ifac[i]=1ll*ifac[i]*ifac[i-1]%p;
			ifac[i-1]=1ll*tmp*fac[i]%p;
		}
		ifac[0]=1;
	}
	inline int Binomal(int n,int m,int p){
		if(n<m||n<0||m<0)return 0;
		return 1ll*fac[n]*ifac[m]%p*ifac[n-m]%p;
	}
	inline int Lucas(int n,int m,int p){
		if(n<m)return 0;
		if(n<p&&m<p)return Binomal(n,m,p);
		return Lucas(n/p,m/p,p)*Binomal(n%p,m%p,p)%p;
	}
	struct nt_complex{
		int real,imag,imag2,p;
		nt_complex(int _real,int _imag,int _imag2,int _p){
			real=_real,imag=_imag,imag2=_imag2,p=_p;
		}
		nt_complex operator *(const nt_complex b)const{
			return nt_complex((1ll*real*b.real%p+1ll*imag2*imag%p*b.imag%p)%p,
			(1ll*real*b.imag%p+1ll*imag*b.real%p)%p,imag2,p);
		}
		nt_complex operator ^(const int b){
			nt_complex a(real,imag,imag2,p),cyr(1,0,imag2,p);
			for(int i=b;i;i>>=1){
				if(i&1)cyr=cyr*a;
				a=a*a;
			}
			return cyr;
		}
	};
	mt19937 rng(time(0));
	inline int Quadratic_residue(int n,int p){
		if(fast_pow(n,(p-1)/2,p)==p-1)return -1;
		if(fast_pow(n,(p-1)/2,p)==0)return 0;
		rd(_,16){
			int x=rng()%(p);
			if(fast_pow((1ll*x*x%p-n+p)%p,(p-1)/2,p)==p-1){
				nt_complex e(x,1,(1ll*x*x%p-n+p)%p,p);
				int res=(e^((p+1)/2)).real;
				return res;
			}
		}
		return -1;
	}
}
int q,n,t,k,a,b;
int f[3005],x[3005],y[3005];
int pre[3005],suf[3005];
const int P=998244353;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>q;
	rd(_,q){
		cin>>t;
		if(t==1){
			cin>>x[n+1]>>y[n+1];
			rep(i,1,n)f[i]=1ll*f[i]*(x[i]-x[n+1]+P)%P;
			n++;f[n]=1;
			rep(i,1,n-1)f[n]=1ll*f[n]*(x[n]-x[i]+P)%P;
		}else{
			cin>>k;
			pre[0]=1,suf[n+1]=1;
			rep(i,1,n)pre[i]=1ll*pre[i-1]*(k-x[i]+P)%P;
			per(i,1,n)suf[i]=1ll*suf[i+1]*(k-x[i]+P)%P;
			int ans=0;
			rep(i,1,n)ans=(ans+1ll*y[i]*pre[i-1]%P*suf[i+1]%P*number_theory::inversion(f[i],P)%P)%P;
			cout<<ans<<'\n';
		}
	}
	
	return 0;
}
