#include<stdio.h>
int t[55][505][55],size[64];
int r[55][55][55];
int ok[55][55];
int st[64];
int num=0;
int n,m;
int a[128];
int b[128];
int tmp[128];
bool query(int now)
{
	if(now==num)
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=i)
			{
				return false;
			}
		}
		return true;
	}
	int wz=a[st[now]];
	if(!ok[now][wz])
	{
		return false;
	}
	for(int i=1;i<=n;i++)
	{
		b[r[now][wz][i]]=i;
	}
	for(int i=1;i<=n;i++)
	{
		tmp[i]=b[a[i]];
	}
	for(int i=1;i<=n;i++)
	{
		a[i]=tmp[i];
	}
	return query(now+1);
}
int tp[55][55];
bool vis[64];
int val[55][55];
void dfs(int now,int u)
{
	vis[u]=true;
	for(int i=1;i<=n;i++)
	{
		if(vis[i])
		{
			continue;
		}
		if(!tp[u][i])
		{
			continue;
		}
		for(int j=1;j<=n;j++)
		{
			val[i][j]=t[now][tp[u][i]][val[u][j]];
		}
		dfs(now,i);
	}
}
void add(int now)
{
	size[now]++;
	for(int i=1;i<=n;i++)
	{
		t[now][size[now]][i]=a[i];
	}
	if(now==num)
	{
		num++;
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=i)
			{
				st[now]=i;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		vis[i]=false;
		for(int j=1;j<=n;j++)
		{
			tp[i][j]=0;
		}
	}
	for(int i=1;i<=size[now];i++)
	{
		for(int j=1;j<=n;j++)
		{
			tp[j][t[now][i][j]]=i;
		}
	}
	for(int i=1;i<=n;i++)
	{
		val[st[now]][i]=i;
	}
	vis[st[now]]=true;
	dfs(now,st[now]);
	for(int i=1;i<=n;i++)
	{
		if(vis[i]&&(!ok[now][i]))
		{
			ok[now][i]=2;
			for(int j=1;j<=n;j++)
			{
				r[now][i][j]=val[i][j];
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(!ok[now][i])
		{
			continue;
		}
		int j=size[now];
		if(ok[now][i]==2)
		{
			ok[now][i]=1;
			j=1;
		}
		for(;j<=size[now];j++)
		{
			for(int k=1;k<=n;k++)
			{
				a[k]=t[now][j][r[now][i][k]];
			}
			int wz=a[st[now]];
			while(!ok[now][wz])
			{
				printf("failed\n");
			}
			for(int k=1;k<=n;k++)
			{
				b[r[now][wz][k]]=k;
			}
			for(int k=1;k<=n;k++)
			{
				tmp[k]=b[a[k]];
			}
			for(int k=1;k<=n;k++)
			{
				a[k]=tmp[k];
			}
			if(!query(now+1))
			{
				add(now+1);
			}
		}
	}
}
int answer[1048576],len;
void mul(int x)
{
	for(int i=0;i<len;i++)
	{
		answer[i]*=x;
	}
	for(int i=0;i<len;i++)
	{
		answer[i+1]+=answer[i]/10;
		answer[i]%=10;
		if(answer[len])
		{
			len++;
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	while(m--)
	{
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		if(!query(0))
		{
			add(0);
		}
	}
	answer[0]=1;
	len=1;
	for(int i=0;i<num;i++)
	{
		int cnt=0;
		for(int j=1;j<=n;j++)
		{
			if(ok[i][j])
			{
				cnt++;
			}
		}
		mul(cnt);
	}
	for(int i=len-1;i>=0;i--)
	{
		putchar(answer[i]+'0');
	}
	putchar('\n');
	return 0;
}