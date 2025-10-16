bool _Start;
#include<deque>
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
	{
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
constexpr int N=7e4+5,M=13e4+5+N,inf=0x7fffffff;
struct edge
{
	int y,f,pre;
}a[M<<1];int alen=1,last[N];
void ins(int x,int y,int f)
{
	a[++alen]=edge{y,f,last[x]};
	last[x]=alen;
	a[++alen]=edge{x,0,last[y]};
	last[y]=alen;
}
int n,m,st,ed,S,T;
int h[N],cur[N];
bool pd()
{
	static std::deque<int>q;q.clear();
	memset(h,0,sizeof(h));h[st]=1;
	q.push_back(st);
	cur[st]=last[st];
	while(q.size())
	{
		int x=q.front();q.pop_front();
		for(int k=last[x];k;k=a[k].pre)
		{
			int y=a[k].y;
			if(a[k].f&&!h[y])
			{
				cur[y]=last[y];
				h[y]=h[x]+1;
				q.push_back(y);
			}
		}
	}
	return h[ed];
}
int findflow(int x,int f)
{
	if(x==ed)
		return f;
	int sx=0,sy;
	for(int &k=cur[x];k;k=a[k].pre)
	{
		int y=a[k].y;
		if(a[k].f&&h[y]==h[x]+1)
		{
			sy=findflow(y,min(a[k].f,f-sx));
			if(!sy)
			{
				h[y]=-1;
				continue;
			}
			a[k].f-=sy;sx+=sy;
			a[k^1].f+=sy;
			if(sx==f)
				return sx;
		}
	}
	return sx;
}
int dinic()
{
	int s=0;
	while(pd())
		s+=findflow(st,inf);
	return s;
}
int in[N];
bool _End;
signed main()
{
	
	read(n,m,S,T);
	st=n+1;ed=st+1;
	for(int i=1;i<=m;i++)
	{
		int x,y,dn,up;
		read(x,y,dn,up);
		ins(x,y,up-dn);
		in[x]-=dn,in[y]+=dn;
	}
	int sum=0;
	for(int i=1;i<=n;i++)
		if(in[i]<0)
			ins(i,ed,-in[i]);
		else if(in[i]>0)
			ins(st,i,in[i]),sum+=in[i];
	ins(T,S,inf);
	if(dinic()!=sum)
		puts("please go home to sleep");
	else
	{
		for(int k=last[st];k;k=a[k].pre)
			a[k^1].f=a[k].f=0;
		for(int k=last[ed];k;k=a[k].pre)
			a[k^1].f=a[k].f=0;
		sum=a[alen].f;
		a[alen].f=a[alen^1].f=0;
		st=T,ed=S;
		writeln(sum-dinic());
	}
	return 0;
}