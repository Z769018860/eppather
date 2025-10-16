#include<bits/stdc++.h>
#define rg register
#define file(x)freopen(x".in","r",stdin);freopen(x".out","w",stdout)

using namespace std;

const long long mod=998244353;
inline long long ksm(long long a,long long b)
{
	long long re=1;
	while(b)
	{
		if(b&1)re=re*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return re;
}
inline void Adder(long long &x,long long y)
{
	if((x+=y)>=mod)x-=mod;
}
inline void Reduce(long long&x,long long y)
{
	if((x-=y)<0)x+=mod;
}

const int maxS=1<<20;

int n,m,K;
long long F[maxS<<1];
long long G[22][maxS];

inline void FWT_Or(long long *f,int sz,int flag)
{
	int ALL=1<<sz;
	for(rg int i=1;i<ALL;i<<=1)
		for(rg int j=0;j<ALL;j+=(i<<1))
			for(rg int k=j;k<j+i;k+=1)
			{
				if(flag==1)Adder(f[k+i],f[k]);
				else Reduce(f[k+i],f[k]);
			}
}

int main()
{
	scanf("%d %d %d",&n,&m,&K);
	for(rg int i=1;i<=m;i+=1)
	{
		int x;scanf("%d",&x);
		++F[x];
	}
	for(rg int i=0;i<=K;i+=1)G[i][0]=1;
	for(rg int i=1;i<n;i+=1)
	{
		int Current=1<<i;
		static long long H[22][maxS];
		static long long Mul[22][maxS];
		for(rg int j=0;j<=min(K,n-i);j+=1)
			for(rg int k=0;k<Current;k+=1)
				H[j][k]=0;
		for(rg int j=1;j<=i;j+=1)
			for(rg int k=0;k<Current;k+=1)
				Mul[j][k]=0;
		for(rg int k=(Current>>1);k<Current;k+=1)Mul[__builtin_popcount(k)][k]=F[k];
		for(rg int j=1;j<=i;j+=1)FWT_Or(Mul[j],i,1);
		if(i==3&&false)
		{
			for(rg int j=1;j<=i;j+=1,cerr<<endl)
				for(rg int l=0;l<Current;l+=1)
					cerr<<Mul[j][l]<<" ";
		}
		for(rg int j=0;j<=min(K,n-i+1);j+=1)
		{
			if(j<=n-i)
				for(rg int k=0;k<(Current>>1);k+=1)
					Adder(H[j][k],G[j][k]);
			if(j)
			{
				static long long Mul2[22][maxS];
				for(rg int k=0;k<i;k+=1)
					for(rg int l=0;l<Current;l+=1)
						Mul2[k][l]=0;
				for(rg int l=0;l<(Current>>1);l+=1)Mul2[__builtin_popcount(l)][l]=G[j][l];
				for(rg int k=0;k<i;k+=1)FWT_Or(Mul2[k],i,1);
				for(rg int k=1;k<=i;k+=1)
				{
					static long long ANS[maxS];
					for(rg int l=0;l<Current;l+=1)ANS[l]=0;
					for(rg int a=1;a<=k;a+=1)
						for(rg int l=0;l<Current;l+=1)
							Adder(ANS[l],Mul[a][l]*Mul2[k-a][l]%mod);
					FWT_Or(ANS,i,-1);

					for(rg int l=0;l<Current;l+=1)
						if(__builtin_popcount(l)==k)
							Adder(H[j-1][l],ANS[l]);
				}
			}
		}
		for(rg int j=0;j<=min(K,n-i);j+=1)
			for(rg int k=0;k<Current;k+=1)
				G[j][k]=H[j][k];
	}
	long long Ans=0;
	int ALL=1<<n;
	for(rg int i=(ALL>>1);i<ALL;i+=1)Adder(Ans,G[1][(ALL-1)^i]*F[i]%mod);
	printf("%lld\n",Ans);
	return 0;
}
