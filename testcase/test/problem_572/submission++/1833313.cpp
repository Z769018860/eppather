#include<bits/stdc++.h>
#define N 1600010
#define M 1600010
#define LL long long
#define uint unsigned int
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define INF 0x3f3f3f3f
#define pir pair<int,int>
#define mp(i,j) make_pair(i,j)
#define fi first
#define se second
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int n,k,sn,pri[M],cc,val[N<<1],bid1[N],bid2[N],g[N<<1],bnum;
uint ans,phi[M],S[N];
bool inp[M];
unordered_map<int,uint> Phi;
inline uint qpow(uint a,uint b)
{
	uint res=1;
	for(;b;b>>=1,a=a*a) if(b&1) res=a*res;
	return res;
}
inline void Pre()
{
	phi[1]=1;
	rep(i,2,M-10)
	{
		if(!inp[i]){pri[++cc]=i;phi[i]=i-1;}
		for(int j=1;j<=cc&&i*pri[j]<=M-10;j++)
		{
			inp[i*pri[j]]=1;
			if(i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j];break;}
			else phi[i*pri[j]]=phi[i]*phi[pri[j]];
		}
	}
	rep(i,1,M-10) phi[i]+=phi[i-1];
}
inline uint sieve(int n)
{
	if(n<=M-10) return phi[n];if(Phi[n]) return Phi[n];
	uint res=(1+n)*n/2;
	for(int l=2,r;l<=n;l=r+1) r=n/(n/l),res-=sieve(n/l)*(r-l+1);
	return Phi[n]=res;
}
inline void Min_25()
{
	for(int l=1,r;l<=n;l=r+1)
	{
		r=min(n,n/(n/l));val[++bnum]=n/l;
		(val[bnum]<=sn?bid1[val[bnum]]:bid2[n/val[bnum]])=bnum;
		g[bnum]=val[bnum]-1;
	}
	rep(i,1,cc) if(pri[i]<=sn) for(int j=1;j<=bnum&&pri[i]*pri[i]<=val[j];j++)
	{
		int x=val[j]/pri[i],id=x<=sn?bid1[x]:bid2[n/x];
		g[j]-=g[id]-(i-1);
	}
	per(i,cc,1) if(pri[i]<=sn)
	{
		uint v=qpow(pri[i],k);
		for(int j=1;j<=bnum&&pri[i]*pri[i]<=val[j];j++)
		{
			LL pk=pri[i];
			for(int e=1;pk<=val[j];e++,pk*=pri[i])
			{
				int x=val[j]/pk,id=x<=sn?bid1[x]:bid2[n/x];
				S[j]+=S[id]+v*((g[id]<i?0:g[id]-i)+(e>1));
			}
		}
	}
	rep(i,1,bnum) S[i]+=g[i];
}
signed main()
{
	Pre();read(n,k);sieve(n);
	sn=sqrt(n);Min_25();
	for(int l=1,r;l<=n;l=r+1)
	{
		r=n/(n/l);
		int id1=r<=sn?bid1[r]:bid2[n/r];
		int id2=(l-1)<=sn?bid1[l-1]:bid2[n/(l-1)];
		ans+=(S[id1]-S[id2])*(sieve(n/l)*2-1);
	}
	printf("%u\n",ans);
	return 0;
}