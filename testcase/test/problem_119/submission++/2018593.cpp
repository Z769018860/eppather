#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#define ll long long
#define M 1000010
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;
ll n, m, s, e;
ll tot, head[N];

bool vis[N];

ll d[N];

priority_queue< pair<ll, ll> > q;

struct edge
{
	ll ver, wei, nxt;
}dt[M];
void add(ll x, ll y, ll z)
{
	dt[++tot] = {y, z, head[x]};
	head[x] = tot;
}
void dijkstra(int s)
{
	memset(d, 0x3f, sizeof(d));
	d[s] = 0;
	q.push( make_pair(0, s) );
	while(q.size())
	{
		ll x = q.top().second;
		q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		for(ll i = head[x]; i; i = dt[i].nxt)
		{
			ll y = dt[i].ver, z = dt[i].wei;
			if(d[y] > d[x] + z)
			{
				d[y] = d[x] + z;
				q.push( make_pair(-d[y], y) );
			}
		}
	}
}
int main()
{
	scanf("%lld%lld%lld%lld", &n, &m, &s, &e);
	for(ll i = 1; i <= m; i++)
	{
		ll x, y, z;
		scanf("%lld%lld%lld", &x, &y, &z);
		add(x, y, z);
		add(y, x, z);
	}
	dijkstra(s);
	printf("%d", d[e]);
	return 0;
}