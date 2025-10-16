#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int n=0,f=1,ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		n=n*10+ch-'0';
		ch=getchar();
	}
	return n*f;
}
int fa[100005];
short siz[100005];
int qx[100005],qy[100005],qans[100005];
vector<int>v[100005],xw[100005];
int qz[100005],pos[100005],lsh[100005],dy[100005];
bool bi(int x,int y)
{
	return qz[x]<qz[y];
}
int findf(int n)
{
	
	while(fa[n]!=n)n=fa[n];
	return n;
}
int cs=0;
const int kk=2000;
int n;
void dfs(int x)
{
	
	for(int i=0;i<xw[x].size();i++)
	{
		if(cs==1)
		{
			qx[xw[x][i]]=findf(qx[xw[x][i]]);
		}
		
		if(siz[qx[xw[x][i]]]>=qy[xw[x][i]])qans[xw[x][i]]-=2*n;
		else qy[xw[x][i]]-=siz[qx[xw[x][i]]];
	}
	
	for(int i=0;i<v[x].size();i++)
	{
		if(cs==1)
		{
			
			qx[pos[v[x][i]]]=findf(qx[pos[v[x][i]]]);
			qy[pos[v[x][i]]]=findf(qy[pos[v[x][i]]]);
			if(siz[qx[pos[v[x][i]]]]>siz[qy[pos[v[x][i]]]])
			{
				swap(qx[pos[v[x][i]]],qy[pos[v[x][i]]]);
			}
		}
		
		if(qx[pos[v[x][i]]]!=qy[pos[v[x][i]]])
		{
			fa[qx[pos[v[x][i]]]]=qy[pos[v[x][i]]];
			siz[qy[pos[v[x][i]]]]+=siz[qx[pos[v[x][i]]]];
		}
		dfs(v[x][i]);
		if(qx[pos[v[x][i]]]!=qy[pos[v[x][i]]])
		{
			fa[qx[pos[v[x][i]]]]=qx[pos[v[x][i]]];
			siz[qy[pos[v[x][i]]]]-=siz[qx[pos[v[x][i]]]];
		}
	}
}
int fir[100005],las[100005];
int a[2005],cnt;
void dfs2(int x)
{
	
	for(int i=0;i<xw[x].size();i++)
	{
		int now=fir[qx[xw[x][i]]];
		cnt=0;
		while(now!=0)
		{
			
			a[++cnt]=lsh[now];
			now=qz[now];
		}
		
		
		
		nth_element(a+1,a+qy[xw[x][i]],a+cnt+1);
		qans[xw[x][i]]=a[qy[xw[x][i]]];
		
	}
	for(int i=0;i<v[x].size();i++)
	{
		fa[qx[pos[v[x][i]]]]=qy[pos[v[x][i]]];
		int sth=0;
		if(fir[qx[pos[v[x][i]]]]!=0&&qx[pos[v[x][i]]]!=qy[pos[v[x][i]]])
		{
			qz[las[qx[pos[v[x][i]]]]]=fir[qy[pos[v[x][i]]]];
			sth=fir[qy[pos[v[x][i]]]];
			fir[qy[pos[v[x][i]]]]=fir[qx[pos[v[x][i]]]];
			if(sth==0)las[qy[pos[v[x][i]]]]=las[qx[pos[v[x][i]]]];
		}
		dfs2(v[x][i]);
		fa[qx[pos[v[x][i]]]]=qx[pos[v[x][i]]];
		if(fir[qx[pos[v[x][i]]]]!=0&&qx[pos[v[x][i]]]!=qy[pos[v[x][i]]])
		{
			fir[qy[pos[v[x][i]]]]=sth;
			qz[las[qx[pos[v[x][i]]]]]=0;
			if(sth==0)las[qy[pos[v[x][i]]]]=0;
		}
	}
}
int main()
{
	
	
	int m;
	n=read();
	m=read();
	for(int i=1;i<=n;i++)qz[i]=read()+1,pos[i]=i;
	sort(pos+1,pos+n+1,bi);
	lsh[pos[1]]=1;
	dy[1]=qz[pos[1]];
	for(int i=2;i<=n;i++)
	{
		if(qz[pos[i]]==qz[pos[i-1]])lsh[pos[i]]=lsh[pos[i-1]];
		else
		{
			lsh[pos[i]]=lsh[pos[i-1]]+1;
			dy[lsh[pos[i]]]=qz[pos[i]];
		}
	}
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		siz[i]=1;
	}
	int cnt=0;
	int opt=0;
	for(int i=1;i<=m;i++)
	{
		opt=read();
		if(opt==1)
		{
			qx[i]=read();
			qy[i]=read();
			qz[i]=++cnt;
			pos[cnt]=i;
			v[qz[i-1]].push_back(qz[i]);
		}
		else if(opt==2)
		{
			qx[i]=read();
			qz[i]=qz[qx[i]];
		}
		else
		{
			qx[i]=read();
			qy[i]=read();
			qz[i]=qz[i-1];
			qans[i]=-qz[i]-2;
			xw[qz[i]].push_back(i);
		}
	}
	for(int i=1;i<=(n-1)/kk+1;i++)
	{
		for(int j=1;j<=n;j++)
		{
			fa[j]=j;
			if(lsh[j]>=(i-1)*kk+1&&lsh[j]<=i*kk)siz[j]=1;
			else siz[j]=0;
		}
		cs++;
		dfs(0); 
		for(int j=0;j<=m;j++)xw[j].clear();
		for(int j=1;j<=m;j++)
		{
			if(qans[j]<=-2*n-2)xw[-qans[j]-2*n-2].push_back(j);
		}
		for(int j=1;j<=n;j++)
		{
			fa[j]=j;
			if(lsh[j]>=(i-1)*kk+1&&lsh[j]<=i*kk)
			{
				fir[j]=las[j]=j;
				qz[j]=0;
			}
			else
			{
				fir[j]=las[j]=0;
				qz[j]=0;
			}
		}
		dfs2(0);
		for(int j=0;j<=m;j++)xw[j].clear();
		for(int j=1;j<=m;j++)
		{
			if(qans[j]<=-2)xw[-qans[j]-2].push_back(j);
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(qans[i]==0)continue;
		if(qans[i]<=-2)printf("-1\n");
		else printf("%d\n",dy[qans[i]]-1); 
	}
	return 0;
}