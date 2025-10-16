#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int S=729,M=700001,N=2e6+10;
const ll mod=(ll)150094635296999121;
int n,m,ans;
ll f[S][S],s[N];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)) {if(c=='-')f=0;c=getchar();}
	while(isdigit(c)) ret=ret*10+(c^48),c=getchar();
	return f?ret:-ret;
}
ll rnd(){return (ll)rand()*rand()%mod;}

struct Hash
{
	int head[M],cnt;
	struct node{ll id,v;int nex;}hs[N];
	ll find(ll x)
	{
		int v=x%M;
		for(int i=head[v];i;i=hs[i].nex) if(hs[i].id==x) return hs[i].v;
		return -1;
	}
	void insert(ll x,ll val)
	{
		int v=x%M;
		hs[++cnt]=(node){x,val,head[v]};head[v]=cnt;
	}
}h1,h2;

ll up(ll x,ll y)
{
	ll res=0,bas=1;
	for(int i=0;i<6;++i)
	{
		res+=f[x%S][y%S]*bas;
		x/=S;y/=S;bas*=S;
	}
	return res;
}

int main()
{
	srand(19260817);
	for(int i=0;i<S;++i) for(int j=0;j<S;++j)
	{
		ll now=0,bas=1,ti=i,tj=j;
		for(int k=0;k<6;++k)
		{
			now+=bas*((ti%3+tj%3)%3);
			ti/=3;tj/=3;bas*=3;
		} 
		f[i][j]=now;
	}
	n=read();m=read();
	for(int i=1;i<=m;++i)
	{
		int u=read()^ans,fa=read()^ans;
		ll v=h1.find(u);
		if(v<0)
		{
			v=rnd();h1.insert(u,v);
			h2.insert(v,u);h2.insert(up(v,v),u);
		}
		s[i]=up(s[fa],v);
		if(!s[i]) ans=-1;
		else if((ans=h2.find(s[i]))>0);
		else ans=-2;
		printf("%d\n",ans);
	}
	return 0;
}