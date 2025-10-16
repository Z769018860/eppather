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
constexpr int N=1e6+10;
int n,q;
int a[N];
struct trnode
{
	int l,r,lc,rc;LL c;
	LL lazy;
}tr[N<<1];int trlen;
#define lc tr[now].lc
#define rc tr[now].rc
void Plus(int now,LL c)
{
	tr[now].c+=(tr[now].r-tr[now].l+1)*c;
	tr[now].lazy+=c;
}
void pushup(int now)
{
	tr[now].c=tr[lc].c+tr[rc].c;
}
void pushdown(int now)
{
	if(tr[now].lazy)
	{
		Plus(lc,tr[now].lazy);
		Plus(rc,tr[now].lazy);
		tr[now].lazy=0;
	}
}
void build(int l,int r)
{
	int now=++trlen;
	tr[now]={l,r};
	if(l==r)
		tr[now].c=a[l];
	else
	{
		int mid=(l+r)>>1;
		lc=trlen+1;build(l,mid);
		rc=trlen+1;build(mid+1,r);
		pushup(now);
	}
}
void modify(int now,int l,int r,LL c)
{
	if(l<=tr[now].l&&tr[now].r<=r)
		return Plus(now,c),void();
	int mid=(tr[now].l+tr[now].r)>>1;
	pushdown(now);
	if(l<=mid)
		modify(lc,l,r,c);
	if(r>=mid+1)
		modify(rc,l,r,c);
	pushup(now);
}
LL query(int now,int l,int r)
{
	if(l<=tr[now].l&&tr[now].r<=r)
		return tr[now].c;
	int mid=(tr[now].l+tr[now].r)>>1;
	pushdown(now);
	LL ans=0;
	if(l<=mid)
		ans+=query(lc,l,r);
	if(r>=mid+1)
		ans+=query(rc,l,r);
	return ans;
}
bool _End;
int main()
{

	read(n,q);
	for(int i=1;i<=n;i++)
		read(a[i]);
	build(1,n);
	while(q--)
	{
		int op,x;LL c;
		read(op);
		if(op==1)
		{
			int l,r;
			read(l,r,c);
			modify(1,l,r,c);
		}
		else
		{
			int l,r;
			read(l,r);
			writeln(query(1,l,r));
		}
	}
	return 0;
}
