
#include<cstdio>
#include<algorithm>
#define F(i,l,r) for(int i=(l),i##_end=(r);i<i##_end;++i)
using namespace std;
template<typename T>void readmain(T &x)
{
	bool neg=false;
	unsigned int c=getchar();
	for(;(c^48)>9;c=getchar())if(c=='-')neg=true;
	for(x=0;(c^48)<10;c=getchar())x=(x<<3)+(x<<1)+(c^48);
	if(neg)x=-x;
}
template<typename T>T &read(T &x){readmain(x);return x;}
template<typename T,typename ...Tr>void read(T &x,Tr &...r){readmain(x);read(r...);}
constexpr int N=1e5+5,INF=0x3f3f3f3f;
namespace flow
{
	constexpr int N=::N,M=3*::N;
	struct edge
	{
		int next,to,cap;
	}e[2*M];
	int n,s,t,hd[N],cnt,cur[N],dis[N],q[N],qf,qr;
	void init(int n_,int s_,int t_){n=n_;s=s_;t=t_;F(i,0,n)hd[i]=-1;}
	void addedge(int u,int v,int w)
	{
		e[cnt].to=v;
		e[cnt].cap=w;
		e[cnt].next=hd[u];
		hd[u]=cnt++;
	}
	void addedge2(int u,int v,int w){addedge(u,v,w);addedge(v,u,0);}
	bool bfs()
	{
		F(i,0,n)cur[i]=hd[i],dis[i]=-1;
		qf=qr=0;
		dis[q[qr++]=s]=0;
		while(qf<qr)
		{
			int u=q[qf++];
			for(int i=hd[u];~i;i=e[i].next)if(e[i].cap)
			{
				int v=e[i].to;
				if(!~dis[v])dis[q[qr++]=v]=dis[u]+1;
			}
		}
		return ~dis[t];
	}
	int dfs(int u,int flow)
	{
		if(u==t)return flow;
		int ans=0;
		for(int &i=cur[u];~i;i=e[i].next)if(e[i].cap&&dis[e[i].to]==dis[u]+1)
		{
			int newflow=min(flow,e[i].cap);
			newflow=dfs(e[i].to,newflow);
			ans+=newflow;flow-=newflow;
			e[i].cap-=newflow;e[i^1].cap+=newflow;
			if(!flow)break;
		}
		return ans;
	}
	int dinic()
	{
		int ans=0;
		while(bfs())ans+=dfs(s,INF);
		return ans;
	}
}
int n,m,ans;
char s[N];
int main()
{
	read(n,m);
	F(i,0,n)scanf("%s",s+i*m);
	F(i,0,n*m)if(s[i]=='2')s[i]='*',++ans;
	flow::init(n*m+2,n*m,n*m+1);
	F(i,0,n*m)
	{
		int p=((i/m)^(i%m))&1;
		if(p)flow::addedge2(i,flow::t,1);
		else flow::addedge2(flow::s,i,1);
		if(i%m&&(s[i]^s[i-1])==2)
		{
			if(p)flow::addedge2(i-1,i,1);
			else flow::addedge2(i,i-1,1);
		}
		if(i>=m&&(s[i]^s[i-m])==2)
		{
			if(p)flow::addedge2(i-m,i,1);
			else flow::addedge2(i,i-m,1);
		}
	}
	ans+=flow::dinic();
	printf("%d\n",ans);
	return 0;
}
