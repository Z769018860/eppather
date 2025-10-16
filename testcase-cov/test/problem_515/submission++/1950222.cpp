#include<unordered_map>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cassert>
#include<fstream>
#include<cstdio>
#include<string>
#include<vector>
#include<bitset>
#include<ctime>
#include<queue>
#include<stack>
#include<cmath>
#include<list>
#include<map>
#include<set>
#define ull unsigned long long
#define ui unsigned int
#define ld long double
#define ll long long
#define fi first
#define se second
#define e emplace
#define eb emplace_back
#define db double
#define ef emplace_front
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mp make_pair
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
#define DE(fmt,...) fprintf(stderr, "Line %d : " fmt "\n",__LINE__,##__VA_ARGS__)


#define LL
bool ST;
static const ll MOD=998244353;
static const ll Root=3;
static const ll inf=1073741823;
static const ll INF=4557430888798830399;
static const double eps=1e-6;
static const double pi=3.1415926535;
char in[1<<20],*p1=in,*p2=in;
using namespace std;
#ifdef LL
#define int ll
#endif
#ifdef LOCALJUDGE
#define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,1<<20,stdin),p1==p2)?EOF:*p1++)
#endif
namespace FastIO
{
	inline void read(int&s)
	{
		s=0;char ch=getchar();
		while((ch>'9'||ch<'0')&&ch!='-')ch=getchar();
		bool tf=(ch=='-')&&(ch=getchar());
		while((ch>='0')&&(ch<='9'))s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
		s=(tf?-s:s);
	}
	inline void read(pii &s){read(s.fi),read(s.se);}
	#ifndef LL
	inline void read(ll&s)
	{
		s=0;char ch=getchar();
		while((ch>'9'||ch<'0')&&ch!='-')ch=getchar();
		bool tf=(ch=='-')&&(ch=getchar());
		while((ch>='0')&&(ch<='9'))s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
		s=(tf?-s:s);
	}
	inline void write(ll x,char ch=' ')
	{
		if(x<0)x=-x,putchar('-');
		static char st[25];int top=0;
		do{st[top++]=x%10+'0',x/=10;}while(x);
		while(top)putchar(st[--top]);
		ch!='~'?putchar(ch):0;
	}
	#endif
	inline void write(int x,char ch=' ')
	{
		if(x<0)x=-x,putchar('-');
		static char st[25];int top=0;
		do{st[top++]=x%10+'0',x/=10;}while(x);
		while(top)putchar(st[--top]);
		ch!='~'?putchar(ch):0;
	}
	template<typename T,typename... Args> inline void read(T&x,Args&...args){read(x),read(args...);}
}
using namespace FastIO;
namespace MTool
{
	inline int Cadd(int a,int b){return a+b>=MOD?a+b-MOD:a+b;}
	inline int Cdel(int a,int b){return a-b<0?a-b+MOD:a-b;}
	inline int Cmul(int a,int b){return a*b%MOD;}
	inline void Madd(int&a,int b){a=(a+b>=MOD?a+b-MOD:a+b);}
	inline void Mdel(int&a,int b){a=(a-b<0?a-b+MOD:a-b);}
	inline void Mmin(int&a,int b){a=min(a,b);}
	inline void Mmax(int&a,int b){a=max(a,b);}
	inline void Mmul(int&a,int b){a=a*b%MOD;}
	inline void Mmod(int&a){a%=MOD;}
	template<typename...Args> inline void Madd(int&a,int b,Args...args){Madd(a,b),Madd(a,args...);}
	template<typename...Args> inline void Mmul(int&a,int b,Args...args){Mmul(a,b),Mmul(a,args...);}
	template<typename...Args> inline void Mdel(int&a,int b,Args...args){Mdel(a,b),Mdel(a,args...);}
	template<typename...Args> inline int Cadd(int a,int b,Args...args){return Cadd(Cadd(a,b),args...);}
	template<typename...Args> inline int Cmul(int a,int b,Args...args){return Cmul(Cmul(a,b),args...);}
	template<typename...Args> inline int Cdel(int a,int b,Args...args){return Cdel(Cdel(a,b),args...);}
}
using namespace MTool;
namespace WrongAnswer_90
{
	int n;
	bitset<1000001> f[101];
	inline void mian()
	{
		read(n),f[0][0]=1;int x,y;
		for(int i=1;i<=n;++i)
		{
			read(x,y);
			for(int j=x;j<=y;++j)f[i]|=f[i-1]<<(j*j);
		}
		write(f[n].count());
	}
}
bool ED;
signed main()
{
	srand(time(0));
	#ifdef LOCALJUDGE
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	#endif
	double st=clock();
	WrongAnswer_90::mian();
	double ed=clock();
	#ifndef LOCALJUDGE
 	cerr<<endl;
	#endif
 	cerr<<"Time: "<<ed-st<<" ms\n";
	#ifdef LOCALJUDGE
 	cerr<<"     ";
	#endif
 	cerr<<"Memory: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB\n";
	return 0;
}
