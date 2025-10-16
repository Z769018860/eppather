#include<stdio.h>
int inf=99999999;
int dis[2505],book[2505],e[2505][2505];
int main()
{
	int n,m,s,t,i,j,t1,t2,t3,u,v,min;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i==j)
			e[i][j]=0;
			else
			e[i][j]=inf;
		}
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&t1,&t2,&t3);
		e[t1][t2]=e[t2][t1]=t3;
	}
	for(i=1;i<=n;i++)
		dis[i]=e[s][i];
	book[s]=1;
	
	for(i=1;i<=n-1;i++)
	{
		
		min=inf;
		for(j=1;j<=n;j++)
		{
			if(book[j]==0&&dis[j]<min)
			{
				min=dis[j];
				u=j;
			}
		}
		book[u]=1;
		for(v=1;v<=n;v++)
		{
			if(e[u][v]<inf)
			{
				if(dis[v]>dis[u]+e[u][v])
				dis[v]=dis[u]+e[u][v];
			}
		}
	}
	printf("%d",dis[t]);
}