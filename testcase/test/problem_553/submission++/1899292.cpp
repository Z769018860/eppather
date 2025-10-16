#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define PI pair<ll,ll>
#define fi first
#define se second
#define mp(x,y) make_pair(x,y)
#define MAXN (100005)
using namespace std;
void File()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
}
template<typename type>
void read(type &x)
{
	x=0;char ch=0;bool fff=0;
	while(ch<'0'||ch>'9'){fff|=!(ch^'-');ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	x=fff?-x:x;
}
int n,m,q,top;
PI tmp[MAXN];
vector<PI> f[MAXN];
int calc(int x,int y)
{
	if(!(x&y)) return x|y;
	return x|y|((1<<__lg(x&y))-1);
}
int main()
{
	
	f[0].push_back(mp(0ll,0ll));
	read(n),read(m);
	for(int i=1;i<=n;i++)
	{
		ll v,l;
		read(v),read(l);
        top=0;
		for(auto x:f[i-1])
		{
			tmp[++top]=x;
			tmp[++top]=mp(calc(x.fi,l),x.se+v);
		}
		sort(tmp+1,tmp+top+1);
		for(int j=1;j<=top;j++)
		{
			if(j>1&&(!(tmp[j-1].fi^tmp[j].fi))) continue;
			while((!f[i].empty())&&(f[i][f[i].size()-1].se>=tmp[j].se)) f[i].pop_back();
			f[i].push_back(tmp[j]);
		}
	}
	read(q);
	for(int tq=1;tq<=q;tq++)
	{
		ll c;
		read(c);
		auto it=lower_bound(f[n].begin(),f[n].end(),mp(c,0ll));
		if(it==f[n].end()) printf("-1\n");
		else printf("%lld\n",(*it).se);
	}
}