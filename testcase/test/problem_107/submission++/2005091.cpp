bool _Start;
#include<vector>
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
constexpr int N=3e5+5,inf=0x3f3f3f3f;
struct trnode
{
	int lc,rc,siz;
	trnode()
	{
		lc=rc=siz=0;
	}
}tr[N<<1];int trlen;
int rt,len;
#define lc(x) tr[x].lc
#define rc(x) tr[x].rc
struct Query
{
	int op,x;
}q[N];
std::vector<int>v;
void insert(int &now,int l,int r,int x,int c)
{
	if(!now)
		now=++trlen;
	tr[now].siz+=c;
	if(l==r)
		return ;
	int mid=(l+r)>>1;
	if(x<=v[mid-1])
		insert(lc(now),l,mid,x,c);
	else
		insert(rc(now),mid+1,r,x,c);
}
int query_kth(int now,int l,int r,int c)
{
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	if(c>tr[lc(now)].siz)
		return query_kth(rc(now),mid+1,r,c-tr[lc(now)].siz);
	else
		return query_kth(lc(now),l,mid,c);
}
int query_rank(int now,int l,int r,int c)
{
	if(l==r)
		return 0;
	int mid=(l+r)>>1;
	if(c>v[mid-1])
		return tr[lc(now)].siz+query_rank(rc(now),mid+1,r,c);
	else
		return query_rank(lc(now),l,mid,c);
}
int query_nxt(int c)
{
	int rk=query_rank(1,1,len,c);
	int tmp=query_kth(1,1,len,rk)-1;
	return v[tmp];
}
int query_pre(int c)
{
	int rk=query_rank(1,1,len,c+1)+1;
	return v[query_kth(1,1,len,rk)-1];
}
int n;
bool _End;
int main()
{
	
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(q[i].op,q[i].x);
		if(q[i].op!=2&&q[i].op!=1)
			v.emplace_back(q[i].x);
	}
	v.emplace_back(inf);
	v.emplace_back(-inf);
	std::sort(v.begin(),v.end());
	v.erase(std::unique(v.begin(),v.end()),v.end());
	len=v.size();
	insert(rt,1,len,inf,1);
	insert(rt,1,len,-inf,1);
	for(int i=1;i<=n;i++)
	{
		switch(q[i].op)
		{
			case 0:
			{
				insert(rt,1,len,q[i].x,1);
				break;
			}
			case 1:
			{
				insert(rt,1,len,q[i].x,-1);
				break;
			}
			case 2:
				writeln(v[query_kth(1,1,len,q[i].x+1)-1]);
				break;
			case 3:
				writeln(query_rank(1,1,len,q[i].x)-1);
				break;
			case 4:
			{
				int ans=query_nxt(q[i].x);
				writeln(ans==-inf?-1:ans);
				break;
			}
			case 5:
			{
				int ans=query_pre(q[i].x);
				writeln(ans==inf?-1:ans);
				break;
			}
		}
	}
	return 0;
}
