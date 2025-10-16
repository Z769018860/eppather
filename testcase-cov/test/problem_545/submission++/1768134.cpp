#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10,M=20000,inf=1e9;
int n,m,k;
int a[N],b[N],s,t,ss,cnt[M],ans;
int h[M],e[2*M],ne[2*M],w[2*M],cost[2*M],idx;
int last[M],dis[M],inq[M],flow[M];
int lowbit(int x)
{
	return x&-x;
}
void add(int a,int b,int c,int d)
{
	e[idx]=b;
	w[idx]=c;
	cost[idx]=d;
	ne[idx]=h[a];
	h[a]=idx++;
	e[idx]=a;
	w[idx]=0;
	cost[idx]=-d;
	ne[idx]=h[b];
	h[b]=idx++;
}
bool spfa()
{
	queue<int>q;
	q.push(ss);
	memset(flow,0,sizeof flow);
	memset(dis,-0x3f,sizeof dis);
	flow[ss]=inf;

	dis[ss]=0;
	memset(inq,0,sizeof inq);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int i=h[u];i!=-1;i=ne[i])
		{
			int v=e[i],w2=w[i];
			if(w2>0&&dis[v]<dis[u]+cost[i])
			{
				dis[v]=dis[u]+cost[i];
				last[v]=i;
				flow[v]=min(flow[u],w2);
				if(!inq[v])
				{
					q.push(v);
					inq[v]=1;
				}
			}
		}
	}
	return dis[t]>0;
}
void MCMF()
{
	while(spfa())
	{
		ans-=flow[t]*dis[t];

		for(int i=t;i!=ss;i=e[last[i]^1])
		{
			w[last[i]]-=flow[t];
			w[last[i]^1]+=flow[t];
		}
	}
}
int calc(int x)
{
	int sum=0;
	while(x>1)x/=2,sum++;
	return sum;
}
signed main()
{
	memset(h,-1,sizeof h);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),ans+=lowbit(a[i]);
	scanf("%lld",&m);
	for(int i=1;i<=m;i++)
		scanf("%lld",&b[i]);
	scanf("%lld",&k);
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	s=1,t=2,ss=100;add(ss,s,k,0);
	int tot=0;
	for(int i=0;i<=30;i++)
	{
		int sum=0;
		for(int j=1;j<=n;j++)
			if((a[j]&((1<<(i+1))-1))==(1<<i))
				sum++;
		add(s,i+3,sum,0);
		sum=0;
		for(int j=1;j<=m;j++)
			if((b[j]&((1<<(i+1))-1))==(1<<i))
				sum++;
		add(i+34,t,sum,0);
	}
	for(int i=1;i<=30;i++)
		for(int j=0;j<i;j++)
			add(i+3,j+34,inf,(1<<i)-(1<<j));
	for(int i=1,j=1;j<=m&&i<=n;i++)
	{
		while(b[j]<a[i]&&j<m)j++;
		if(a[i]==b[j])
		{
			cnt[calc(lowbit(a[i]))]++;
			j++;
		}
	}
	for(int i=0;i<=30;i++)	
		if(cnt[i])
			add(i+3,i+34,cnt[i],(1<<i));
	MCMF();
	printf("%lld",ans);
	return 0;
}