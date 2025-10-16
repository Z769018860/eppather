

#include<iostream>
using namespace std;
int fa[4000010];
long long ans=0;
int p=0,temp;
const long long mod=998244353;
int find(int i)
{
	if(fa[i] == i)
		return i;
	else{
		fa[i] = find(fa[i]);
		return fa[i];
}
}
void unionn(int x,int y)
{
	int xx=find(x);
	int yy=find(y);
	if(xx!=yy)
		fa[yy]=xx;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int op,u,v,n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	while(m--)
	{
		cin>>op>>u>>v;
		if(op==0)
			unionn(u,v);
		else if(op==1)
		{
			if(find(u)==find(v))
			{
				ans*=2;
				ans+=1;
				ans%=mod;
			}
			else
			{
			 	ans*=2;
			 	ans%=mod;
			}
		}
	}
	cout<<ans%mod;
	return 0;
}
