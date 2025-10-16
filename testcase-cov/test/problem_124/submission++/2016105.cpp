bool _Start;
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
namespace IO
{
	#define TP template<typename T>
	#define TP_ template<typename T,typename ... T_>
	#ifdef DEBUG
	#define gc() (getchar())
	#else
	char buf[1<<20],*p1,*p2;
	#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
	#endif
	#ifdef DEBUG
	void pc(const char &c)
	{O
		putchar(c);
	}
	#else
	char pbuf[1<<20],*pp=pbuf;
	void pc(const char &c)
	{
		if(pp-pbuf==1<<20)
			fwrite(pbuf,1,1<<20,stdout),pp=pbuf;
		*pp++=c;
	}
	struct IO{~IO(){fwrite(pbuf,1,pp-pbuf,stdout);}}_;
	#endif
	TP void read(T &x)
	{
		x=0;static int f;f=0;static char ch;ch=gc();
		for(;ch<'0'||ch>'9';ch=gc())ch=='-'&&(f=1);
		for(;ch>='0'&&ch<='9';ch=gc())x=(x<<1)+(x<<3)+(ch^48);
		f&&(x=-x);
	}
	TP void write(T x)
	{
		if(x<0)
			pc('-'),x=-x;
		static T sta[35],top;top=0;
		do
			sta[++top]=x%10,x/=10;
		while(x);
		while(top)
			pc(sta[top--]^48);
	}
	TP_ void read(T &x,T_&...y){read(x);read(y...);}
	TP void writeln(const T x){write(x);pc('\n');}
	TP void writesp(const T x){write(x);pc(' ');}
	TP_ void writeln(const T x,const T_ ...y){writesp(x);writeln(y...);}
	TP void debugsp(const T x){fprintf(stderr,"%d ",x);}
	TP void debug(const T x){fprintf(stderr,"%d\n",x);}
	TP_ void debug(const T x,const T_...y){debugsp(x);debug(y...);}
	TP inline T max(const T &a,const T &b){return a>b?a:b;}
	TP_ inline T max(const T &a,const T_&...b){return max(a,max(b...));} 
	TP inline T min(const T &a,const T &b){return a<b?a:b;}
	TP_ inline T min(const T &a,const T_&...b){return min(a,min(b...));}
	TP inline void swap(T &a,T &b){static T t;t=a;a=b;b=t;}
	TP inline T abs(const T &a){return a>0?a:-a;}
	#undef TP
	#undef TP_
}
using namespace IO;
using std::cerr;
using LL=long long;
constexpr int N=1e7+10;
constexpr LL P=1e9+7;
LL qpow(LL a,LL b)
{
	LL ans=1%P;a%=P;
	for(;b;b>>=1,a=a*a%P)
		if(b&1)
			ans=ans*a%P;
	return ans;
}
int prime[N],pr,n,K;
bool v[N];
LL g[N];
void init()
{
	g[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!v[i])
		{
			prime[++pr]=i;
			g[i]=(qpow(i,K)+1)%P;
		}
		for(int j=1;j<=pr&&prime[j]*i<=n;j++)
		{
			int k=i*prime[j];
			g[k]=g[i]*g[prime[j]]%P;
			v[k]=1;
			if(i%prime[j]==0)
			{
				g[k]=(g[i]+((g[i]-g[i/prime[j]]+P)%P)*(g[prime[j]]-1)%P+P)%P;
				break;
			}
		}
	}
}
bool _End;
int main()
{

	read(n,K);
	init();
	LL ans=0;
	for(int i=1;i<=n;i++)
		ans=((ans+g[i])%P+P)%P;
	writeln(ans);
	return 0;
}
