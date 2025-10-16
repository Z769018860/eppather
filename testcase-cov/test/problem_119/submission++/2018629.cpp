#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>

using namespace std;
#define ll long long
const int N=2510;

int n,m,s,t;
int u,v;
ll w;
ll f[N];
struct h{
	int u;
	ll w;
	bool operator <(const h &b)
	const {return w>b.w;}
};
vector<h> e[N];
priority_queue<h> q;
bool vis[N];

void add(int u,int v,ll w)
{
	e[u].push_back((h){v,w});
	e[v].push_back((h){u,w});
}

void dij(int k)
{
	q.push((h){k,f[k]=0});
	while(q.size())
	{
		int u=q.top().u;q.pop();
		if(vis[u]) continue;
		for(int i=0;i<e[u].size();i++)
		{
			v=e[u][i].u,w=e[u][i].w;
			if(f[v]>f[u]+w) q.push((h){v,f[v]=f[u]+w});
		}
	}
}

int main()
{
	memset(f,0x3f,sizeof f);
	scanf("%d%d%d%d",&n,&m,&s,&t);
	while(m--)
	{
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,w);
	}
	
	dij(s);
	
	printf("%lld",f[t]);
	return 0;
}