#include<iostream>
using namespace std;
int head[100010],cnt;
long long ans[1000010];
bool vis[1000010];
int m,n,s,t;
struct e 
{
	int to,nxt,val;
}edge[1000010];
void add(int x,int y,int z)
{
	edge[++cnt].to=y;
	edge[cnt].val=z;
	edge[cnt].nxt=head[x];
	head[x]=cnt;
}
int main()
{
	cin>>m>>n>>s>>t;
	for(int i=1;i<=n;i++) ans[i]=2147483647;
	ans[s]=0;
	for(int i=1;i<=n;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c),add(b,a,c);
	}
	int pos=s;
	while(vis[pos]==0)
	{
		long long minn=1e15;
		vis[pos]=1;
		for(int i=head[pos];i!=0;i=edge[i].nxt)
			if(!vis[edge[i].to]&&ans[edge[i].to]>ans[pos]+edge[i].val) 
				ans[edge[i].to]=ans[pos]+edge[i].val;
		for(int i=1;i<=m;i++)
			if(ans[i]<minn&&vis[i]==0) minn=ans[i],pos=i;
	}
	cout<<ans[t]<<endl;
	return 0;
}