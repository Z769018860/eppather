#include<bits/stdc++.h>
#define ll long long
using namespace std;
template <typename T> inline void read(T &x)
{
	x=0;T f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-')f=-1;
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x*=f;
}
template <typename T,typename ...Args>void read(T &x,Args&...args){read(x),read(args...);}
template <typename T> void print(T x)
{
	if(x<0) x=-x,putchar('-');
	if(x>9) print(x/10);
	putchar(x%10+48);
}
template <typename T> void print(T x,char c){print(x); putchar(c);}
template<typename T>inline void output(T x){print(x,' ');}
template<typename T,typename ...Arg>inline void output(T x,Arg ...arg){output(x);output(arg...);}
const int N=200007;
int n,m,q,a[N];
struct node{int l,r;ll sum,suml,sumr;};
struct segment_tree
{
	#define ls (rt<<1)
	#define rs (rt<<1|1)
	node f[N<<2]; ll kl[N<<2],kr[N<<2];
	ll askl(int rt,int l,int r,int x)
	{
		if(!x) return 0;
		if(l==r) return (ll)x*l;
		int mid=(l+r)>>1;
		if(f[ls].l<x) return askl(rs,mid+1,r,x-f[ls].l+f[ls].r)-kl[rt]+f[ls].suml;
		return askl(ls,l,mid,x);
	}
	ll askr(int rt,int l,int r,int x)
	{
		if(!x) return 0;
		if(l==r) return (ll)x*l;
		int mid=(l+r)>>1;
		if(f[rs].r<x) return askr(ls,l,mid,x-f[rs].r+f[rs].l)-kr[rt]+f[rs].sumr;
		return askr(rs,mid+1,r,x); 
	}
	node merge(node L,node R,int Lnum,int Ll,int Lr,int Rnum,int Rl,int Rr,int opt)
	{
		int mn=min(L.r,R.l); node res;
		ll ql=askr(Lnum,Ll,Lr,mn),qr=askl(Rnum,Rl,Rr,mn);
		if(opt) kl[Lnum>>1]=qr,kr[Lnum>>1]=ql;
		res.l=L.l+R.l-mn,res.r=L.r+R.r-mn;
		res.sum=L.sum+R.sum+ql+qr;
		res.suml=L.suml+R.suml-qr;
		res.sumr=L.sumr+R.sumr-ql;
		return res;
	}
	void build(int rt,int l,int r)
	{
		if(l==r) return f[rt]={0,1,0,0,l},void();
		int mid=(l+r)>>1;
		build(ls,l,mid); build(rs,mid+1,r);
		f[rt]=merge(f[ls],f[rs],ls,l,mid,rs,mid+1,r,1);
	}
	void update(int rt,int l,int r,int p,int x)
	{
		if(l==r)
		{
			if(x==1)
			{
				if(f[rt].r) f[rt].r--,f[rt].sumr-=l,f[rt].sum+=l<<1;
				else f[rt].l++,f[rt].suml+=l;
			}
			else
			{
				if(f[rt].l) f[rt].l--,f[rt].suml-=l;
				else f[rt].r++,f[rt].sumr+=l,f[rt].sum-=l<<1;
			}
			return ;
		}
		int mid=(l+r)>>1;
		if(p<=mid) update(ls,l,mid,p,x);
		else update(rs,mid+1,r,p,x);
		f[rt]=merge(f[ls],f[rs],ls,l,mid,rs,mid+1,r,1);
	}
	node ask(int rt,int l,int r,int L,int R)
	{
		if(L>R) return (node){0,0,0,0,0};
		if(L<=l&&r<=R) return f[rt];
		int mid=(l+r)>>1;
		if(L<=mid&&R>mid) return merge(ask(ls,l,mid,L,R),ask(rs,mid+1,r,L,R),ls,l,mid,rs,mid+1,r,0);
		if(L<=mid) return ask(ls,l,mid,L,R);
		else return ask(rs,mid+1,r,L,R);
	}
}Tr;
signed main()
{
	read(n,q); m=n<<1;
	Tr.build(1,1,m);
	for(int i=1;i<=n;i++)
		read(a[i]),Tr.update(1,1,m,a[i],1);
	for(int i=1,opt,l,r;i<=q;i++)
	{
		read(opt,l,r);
		if(opt==1)
		{
			Tr.update(1,1,m,a[l],-1);
			Tr.update(1,1,m,a[l]=r,1);
		}
		else print(Tr.ask(1,1,m,1,m).sum-Tr.ask(1,1,m,1,r-1).sum-Tr.ask(1,1,m,l+1,m).sum+Tr.ask(1,1,m,l+1,r-1).sum,'\n');
	}
	return 0;
}