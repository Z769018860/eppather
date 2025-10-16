#include<cstdio>
const int mod=998244353,B=19190506,E=768906335,A=917504,N=11e5+7;
typedef long long ll;const ll Mod=mod;
ll qpow(ll x,int y){ll r=1;for(;y;x=x*x%Mod,y>>=1)if(y&1)r=r*x%Mod;return r;}
int pw[A],qrc[A],invq[A],frc[N],invf[N];
ll C(int n,int k){return n>=k?(ll)frc[n]*invf[k]%Mod*invf[n-k]%Mod:0;}
ll qC(int n,int k){return n>=k?(ll)qrc[n]*invq[k]%Mod*invq[n-k]%Mod:0;}
int main()
{
	*pw=*qrc=1;for(int i=1;i<A;++i)pw[i]=(ll)pw[i-1]*E%Mod,qrc[i]=(ll)qrc[i-1]*(pw[i]-1)%Mod;
	invq[A-1]=qpow(qrc[A-1],mod-2);for(int i=A-1;i;--i)invq[i-1]=(ll)invq[i]*(pw[i]-1)%Mod;
	*frc=1;for(int i=1;i<N;++i)frc[i]=(ll)frc[i-1]*i%Mod;
	invf[N-1]=qpow(frc[N-1],mod-2);for(int i=N-1;i;--i)invf[i-1]=(ll)invf[i]*i%Mod;
	
	int T;scanf("%d",&T);
	while(T--)
	{
		ll n,m;scanf("%lld%lld",&n,&m);
		ll res=C(n/A,m/A)*qC(n%A,m%A)%Mod;
		n%=A;m%=A;int p=(m-n+A)*m%A;
		printf("%lld\n",res*pw[p]%Mod);
	}
	return 0;
}