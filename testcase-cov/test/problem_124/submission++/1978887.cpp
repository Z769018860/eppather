#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

const int Lim=1e7, MAXN=Lim+10;
const int P=1e9+7;
inline int kpow(int a, int x) { int ans=1; for(; x; x>>=1, a=(ull)a*a%P) if(x&1) ans=(ull)ans*a%P; return ans; }
int n, k;
int minp[MAXN], prime[MAXN/10], cntprime;
int f[MAXN];
inline void sieve(int n) {
	f[1]=1;
	for(int i=2; i<=n; ++i) {
		if(!minp[i]) {
			minp[i]=prime[++cntprime]=i;
			f[i]=kpow(i, k);
		}
		for(int j=1, x; j<=cntprime; ++j)
			if((x=prime[j]*i)>n || prime[j]>minp[i])
				break;
			else {
				minp[x]=prime[j];
				f[x]=(ull)f[prime[j]]*f[i]%P;
			}
	}
}
int g[MAXN];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>k;
	sieve(n);
	for(int i=1; i<=cntprime; ++i) {
		int p=prime[i], pe=p;
		while(pe<=n/p) pe*=p;
		for(int j=p; j<=n; j+=p)
			g[j]=f[j]*1;
		for(int w=pe; w>1; w/=p)
			for(int j=n/w, k=j*w; j; --j, k-=w) {
				g[k]+=f[j]*1;
				if(g[k]>=P) g[k]-=P;
			}
		for(int j=p; j<=n; j+=p)
			f[j]=g[j];





	}
	ull res=0;
	for(int i=1; i<=n; ++i) res+=f[i];
	cout<<res%P;
	return 0;
}