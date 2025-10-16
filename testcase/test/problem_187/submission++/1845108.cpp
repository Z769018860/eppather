#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define MOD 1000000007
#define mod 998244353
#define F first
#define S second
#define ll long long
#define N 110
using namespace std;
ll n,k,m,f[N][1028];
vector<pair<ll,ll> > vt[N];
int main(){
	ll i,j,l,x,y,w;
	memset(f,63,sizeof(f));
	scanf("%lld%lld%lld",&n,&m,&k);
	for(i=0;i<m;i++)
	{
		scanf("%lld%lld%lld",&x,&y,&w);
		x--,y--;
		vt[x].push_back(make_pair(y,w));
		vt[y].push_back(make_pair(x,w));
	}
	for(i=0;i<k;i++)
	{
		scanf("%lld",&x);
		x--;
		f[x][1<<i]=0;
	}
	for(i=1;i<(1<<k);i++)
	{
		priority_queue<pair<ll,ll> > pq;
		for(j=0;j<n;j++)
		{
			for(l=(i-1)&i;l;l=(l-1)&i)
			{
				f[j][i]=min(f[j][i],f[j][l]+f[j][i^l]);
			}
			if(f[j][i]<LINF)
			{
				pq.push(make_pair(-f[j][i],j));
			}
		}
		while(!pq.empty())
		{
			x=pq.top().S,w=-pq.top().F;
			pq.pop();
			if(w!=f[x][i])
			{
				continue;
			}
			for(j=0;j<vt[x].size();j++)
			{
				if(f[vt[x][j].F][i]>f[x][i]+vt[x][j].S)
				{
					f[vt[x][j].F][i]=f[x][i]+vt[x][j].S;
					pq.push(make_pair(-f[vt[x][j].F][i],vt[x][j].F));
				}
			}
		}
	}
	ll ans=LINF;
	for(i=0;i<n;i++)
	{
		ans=min(ans,f[i][(1<<k)-1]);
	}
	printf("%lld\n",ans);
	return 0;
}