#include<bits/stdc++.h>
#define nn 5010
#define mm 20010
#define ll long long int
using namespace std;
priority_queue<pair<ll,ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > >q;
ll h[nn],d[nn],va[mm],v[mm],ne[mm];
ll n,m,a,b,tot;
bool vi[nn];
void add(ll x,ll y,ll z)
{
	va[++tot]=z;v[tot]=y;ne[tot]=h[x];h[x]=tot;return;
}
void dj()
{
	memset(d,0x3f,sizeof(d));
	memset(vi,0,sizeof(vi));
	d[a]=0;
	q.push(make_pair(0,a));
	while(!q.empty())
	{
		ll x=q.top().second;q.pop();
		if(vi[x])continue;
		vi[x]=true;
		for(int i=h[x];i;i=ne[i])
		{
			ll y=v[i],z=va[i];
			if(d[y]>d[x]+z)
			{
				d[y]=d[x]+z;
				q.push(make_pair(d[y],y));
			}
		}
	}
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie();cout.tie();
	cin>>n>>m>>a>>b;
	ll ta,tb,tc;
	for(int i=1;i<=m;i++)
	{
		cin>>ta>>tb>>tc;
		add(ta,tb,tc);
		add(tb,ta,tc);
	}
	dj();
	cout<<d[b];
	return 0;
}