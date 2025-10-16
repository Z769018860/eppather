bool _Start;
#include<queue>
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
using PII=std::pair<int,int>;
using LL=long long;
constexpr int N=5e3+10,M=3e5+10,inf=0x3f3f3f3f;
int n,m,st,ed;
LL w[N];
int h[N],gap[N<<1];
struct edge
{
	int y;LL f;int pre;
}a[M<<1];int alen=1,last[N];
inline void ins(int x,int y,LL f)
{
	a[++alen]=edge{y,f,last[x]};
	last[x]=alen;
	a[++alen]=edge{x,0,last[y]};
	last[y]=alen;
}
struct cmp
{
	inline bool operator()(const int &x,const int &y)const
	{
		return h[x]<h[y];
	}
};
bool bfs()
{
	static std::priority_queue<PII,std::vector<PII>,std::greater<PII>>q;
	memset(h,0x3f,sizeof(h));
	h[ed]=1;
	q.push({h[ed],ed});
	while(q.size())
	{
		int x=q.top().second;q.pop();
		for(int k=last[x];k;k=a[k].pre)
		{
			int y=a[k].y;
			if(a[k^1].f&&h[y]>h[x]+1)
			{
				h[y]=h[x]+1;
				q.push({h[y],y});
			}
		}
	}
	return h[st]!=h[0];
}
bool inq[N];
std::priority_queue<int,std::vector<int>,cmp>q;
inline void push(int x)
{
	int f=0;
	for(int k=last[x];k;k=a[k].pre)
	{
		int y=a[k].y;
		if(a[k].f&&h[y]==h[x]-1)
		{
			f=min(w[x],a[k].f);
			w[x]-=f;w[y]+=f;
			a[k].f-=f;
			a[k^1].f+=f;
			if(y!=st&&y!=ed&&!inq[y]&&h[y]<inf)
				q.push(y),inq[y]=1;
			if(!w[x])
				return ;
		}
	}
}
inline void rebuild(int x)
{
	h[x]=inf;
	for(int k=last[x];k;k=a[k].pre)
	{
		int y=a[k].y;
		if(a[k].f&&h[y]+1<h[x])
			h[x]=h[y]+1;
	}
}
int HLPP()
{
	if(!bfs())
		return 0;
	for(int i=1;i<=n;i++)
		if(h[i]<inf)
			++gap[h[i]];
						
	h[st]=n;
	for(int k=last[st],f;k;k=a[k].pre)
	{
		int y=a[k].y;
		if(a[k].f)
		{
			f=a[k].f;
			w[st]-=f;w[y]+=f;
			a[k].f-=f;
			a[k^1].f+=f;
			if(y!=st&&y!=ed&&!inq[y]&&h[y]<inf)
				q.push(y),inq[y]=1;
		}
	}
	while(q.size())
	{
		int x=q.top();q.pop();inq[x]=0;
		push(x);
		if(w[x])
		{
			if(--gap[h[x]]<=0)
				for(int i=1;i<=n;i++)
					if(i!=st&&i!=ed&&h[i]>h[x]&&h[i]<n+1)
						h[i]=n+1;
			rebuild(x);++gap[h[x]];
			q.push(x);inq[x]=1;
		}
	}
	return w[ed];
}
bool _End;
int main()
{

	read(n,m,st,ed);
	for(int i=1,x,y,f;i<=m;i++)
	{
		read(x,y,f);
		ins(x,y,f);
	}
	writeln(HLPP());
	return 0;
}
