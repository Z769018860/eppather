#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
long long w[3005],x[3005],y[3005],a[3005],n,m,r,k,i,j,l,ans;
long long inv(long long p){
	long long r=1,m=mod-2;
	while(m){
		if(m&1)r=r*p%mod;
		m>>=1;
		p=p*p%mod;
	}
	return r;
}

long long f(long long p){
    long long L=1,R=m+1,M;
    while(L<R){
        M=(L+R)>>1;
        if((a[M]>>30)>=p)R=M;
        else L=M+1;
    }
    if((a[L]>>30)==p)return a[L]^(p<<30);
    else return 0;
}
int main(){
	scanf("%lld",&n);
	for(i=1;i<=n;++i){
		scanf("%lld",&k);
		if(k==1){
			w[++m]=1;
			scanf("%lld%lld",&x[m],&y[m]); 
			a[m]=(x[m]<<30)^y[m];
			for(j=1;j<m;++j){
				w[j]=w[j]*(x[j]-x[m])%mod;
				w[m]=w[m]*(x[m]-x[j])%mod;
			}
		}
		if(k==2){
			scanf("%lld",&r);
			sort(a+1,a+m+1);
			l=1,ans=f(r);
			if(ans)printf("%lld\n",ans);
			else{
				for(j=1;j<=m;++j){
					l=l*(r+mod-x[j])%mod;
					ans=(ans+inv((w[j]*(r-x[j]))%mod)*y[j]%mod+mod)%mod;
				}
				printf("%lld\n",ans*l%mod);	
			}	
		}
	}
}