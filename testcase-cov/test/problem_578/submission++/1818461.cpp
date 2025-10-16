#include<bits/stdc++.h>
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid ((l+r)>>1)
using namespace std;
typedef long long ll;
const int N=5e5+5;
int n,q,a[N],op,x,y,s[N],c[N],m,b[N],t1[N],t2[N],u;
tuple<int,int,int> f[N];
ll ans;
struct SegTree
{
	bool o[N<<2];
	ll qr(int rt,int k)
	{
		ll sum=0;
		while(k)
		{
			if(o[rt]) sum+=t[rt].sr,k=0;
			else if(t[rs].cr==k) sum+=t[rs].sr,k=0;
			else if(t[rs].cr>k) rt=rs;
			else sum=sum+t[rs].sr-t[rt].vr,k=k-t[rs].cr+t[rs].cl,rt=ls;
		}
		return sum;
	} 
	ll ql(int rt,int k)
	{
		ll sum=0;
		while(k)
		{
			if(o[rt]) sum+=t[rt].sl,k=0;
			else if(t[ls].cl==k) sum+=t[ls].sl,k=0;
			else if(t[ls].cl>k) rt=ls;
			else sum=sum+t[ls].sl-t[rt].vl,k=k-t[ls].cl+t[ls].cr,rt=rs;
		}
		return sum;
	}
	struct node
	{
		int cl,cr;
		ll sl,sr,s,vl,vr;
	}t[N<<2];
	node merge(int rt,node a,node b)
	{
		node c;int k=min(a.cr,b.cl);
		c.vr=qr(ls,k),c.vl=ql(rs,k);c.s=a.s+b.s+c.vl+c.vr;
		c.sl=a.sl+b.sl-c.vl;c.cl=a.cl+b.cl-k;
		c.sr=a.sr+b.sr-c.vr;c.cr=a.cr+b.cr-k;
		return c;
	}
	void push_up(int rt) {t[rt]=merge(rt,t[ls],t[rs]);}
	void build(int rt,int l,int r)
	{
		if(l==r) 
		{
			o[rt]=1;
			if(c[l]==-1) t[rt].cl++,t[rt].sl+=b[l];
			if(c[l]==1) t[rt].cr++,t[rt].sr+=b[l];
			return;
		}
		build(ls,l,mid);build(rs,mid+1,r);push_up(rt);
	}
	void modify(int rt,int l,int r,int x,int c,int v)
	{
		if(l==r) 
		{
			t[rt].cl=t[rt].cr=t[rt].sl=t[rt].sr=0;
			if(c==-1) t[rt].cl++,t[rt].sl+=v;
			if(c==1) t[rt].cr++,t[rt].sr+=v;
			return;
		}
		(x<=mid)?modify(ls,l,mid,x,c,v):modify(rs,mid+1,r,x,c,v);
		push_up(rt); 
	}
	node query(int rt,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R) return t[rt];
		if(R<=mid) return query(ls,l,mid,L,R);
		if(L>mid) return query(rs,mid+1,r,L,R);
		return merge(rt,query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
	}
}T;
ll solve(int l,int r)
{
	if(l>r) return 0;
	l=s[l-1]+1;r=s[r];
	return T.query(1,1,m,l,r).s; 
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n+n;i++) s[i]=1;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),s[a[i]]++;
	for(int i=1;i<=q;i++) 
	{
		scanf("%d%d%d",&op,&x,&y);
		f[i]=make_tuple(op,x,y);
		if(op==1) s[y]++;
	}
	for(int i=1;i<=n+n;i++) s[i]+=s[i-1],t1[i]=t2[i]=s[i];
	for(int i=1;i<=n+n;i++) c[s[i-1]+1]=1,b[s[i-1]+1]=i;
	for(int i=1;i<=n;i++) c[t1[a[i]]]=-1,b[t1[a[i]]]=a[i],t1[a[i]]--;
	m=s[n+n];
	T.build(1,1,m);
	for(int i=1;i<=q;i++)
	{
		tie(op,x,y)=f[i];
		if(op==1)
		{
			u=t2[a[x]]--;
			T.modify(1,1,m,u,0,0);a[x]=y;
			u=t1[a[x]]--;
			T.modify(1,1,m,u,-1,y);
		}
		if(op==2)
		{
			ans=solve(1,n+n)-solve(x+1,n+n)-solve(1,y-1)+solve(x+1,y-1);
			printf("%lld\n",ans);
		}
	}
	return 0;
}