#include <iostream>
#include<cstring>
using namespace std;

const int inf = 1e9;
const int N = 210, M = 21000;
int n,m,s,t;

int A[N],q[N],l[M],d[N];
int h[N],ne[M],e[M],idx,f[M],cur[N];

void add(int a,int b,int c)
{
	e[idx] = b,ne[idx] = h[a],f[idx] = c,h[a] = idx ++;
	e[idx] = a,ne[idx] = h[b],f[idx] = 0,h[b] = idx ++;
}


bool bfs()
{
	memset(d,-1,sizeof d);
	q[0] = s;
	d[s] = 0;
	cur[s] = h[s];
	int tt = 1,hh = 0;
	
	while(hh < tt)
	{
		int u = q[hh ++];
		for(int i = h[u]; ~i ;i = ne[i])
		{
			int v = e[i];
			if(d[v] == -1 && f[i])
			{
				d[v] = d[u] + 1;
				cur[v] = h[v];
				if(v == t) return true;
				q[tt ++] = v;
			}
		}
	}
	return false;
}

int find(int u,int limit)
{
	if(u == t) return limit;
	int sum = 0;
	for(int i = cur[u];~i && sum < limit;i = ne[i])
	{
		cur[u] = i;
		int v = e[i];
		if(d[v] == d[u] + 1 && f[i])
		{
			int t = find(v,min(f[i],limit - sum));
			f[i] -= t,f[i^1] += t,sum += t;
			if(!t) d[v] = -1;
		}
	}
	return sum;
}
int dinic()
{
	int res = 0,flow = 0;
	while(bfs()) while(flow = find(s,inf)) res += flow;
	return res;
}

int main()
{
	scanf("%d%d",&n,&m);
	s = 0,t = n + 1;
	memset(h,-1,sizeof h);
	
	int a,b,c,d;
	for(int i = 1;i <= m;++i) 
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		l[idx] = c;
		add(a,b,d - c);
		A[a] -= c,A[b] += c;
	}
	
	int sum = 0;
	for(int i = 1;i <= n;++i)
		if(A[i] > 0) add(s,i,A[i]),sum += A[i];
		else if(A[i] < 0) add(i,t,-A[i]);
	

		
	if(dinic() < sum) puts("NO");
	else
	{
		puts("YES");
		for(int i = 0;i < 2*m;i += 2)
			printf("%d\n",f[i^1] + l[i]);
	}
} 