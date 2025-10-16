#include<set>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>
#define pr pair
#define f first
#define s second
#define ll long long
#define mp make_pair
#define pll pr<ll,ll>
#define pii pr<int,int>
#define piii pr<int,pii>
using namespace std;
map<pii,int> p;
int f[5003],c[5003];
int*cl[10004],ov[10004],u;
int tt[100],z;
void nec()
{
	tt[z++]=u;
}
void ch(int*i,int v)
{

	cl[u]=i;
	ov[u++]=*i;
	*i=v;
}
void bak()
{
	z--;

	while(u>tt[z])
	{
		u--;

		*cl[u]=ov[u];
	}
}
struct node
{
	vector<piii> qr;
	int l,r;
} nd[1048600];
void bd(int i,int l,int r)
{
	node&x=nd[i];
	x.l=l;
	x.r=r;
	if(l==r-1) return;
	bd(i*2,l,l+r>>1);
	bd(i*2+1,l+r>>1,r);
}
void add(int i,int l,int r,piii v)
{

	node&x=nd[i];
	if(x.l>=l&&x.r<=r)
	{
		x.qr.push_back(v);
		return;
	}
	int d=x.l+x.r>>1;
	if(l<d) add(i*2,l,r,v);
	if(r>d) add(i*2+1,l,r,v);
}
int ff(int x)
{
	return f[x]==x?x:ff(f[x]);
}
void mg(int a,int b)
{
	a=ff(a);
	b=ff(b);
	if(a==b) return;
	if(c[a]>c[b]) swap(a,b);
	ch(f+a,b);
	ch(c+b,c[b]+c[a]);
}
void dfs(int i)
{
	nec();
	node&x=nd[i];

	reverse(x.qr.begin(),x.qr.end());
	for(piii t:x.qr)
	{

		if(t.f==1)
		{
			mg(t.s.f,t.s.s);
		}
		else
		{
			cout<<(ff(t.s.f)==ff(t.s.s)?"Y\n":"N\n");
		}
	}
	if(x.l<x.r-1) dfs(i*2),dfs(i*2+1);
	bak();
}
int main()
{
	ios_base::sync_with_stdio(0);
	int n,m;
	cin>>n>>m;
	bd(1,0,m);
	for(int i=0;i<n;i++) f[i]=i,c[i]=1;
	int t,a,b;
	for(int i=0;i<m;i++)
	{
		cin>>t>>a>>b;
		a--;
		b--;
		if(a>b) swap(a,b);
		pii e=mp(a,b);
		if(t==2) add(1,i,i+1,mp(t,e));
		if(t==0)
		{
			p[e]=i;
		}
		if(t==1)
		{
			add(1,p[e],i,mp(1,e));
			p[e]=-1;
		}
	}
	for(pr<pii,int> i:p) if(i.s!=-1) add(1,i.s,m,mp(1,i.f));
	dfs(1);
	return 0;
}