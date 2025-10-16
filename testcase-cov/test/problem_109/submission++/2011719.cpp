#include<iostream>
using namespace std;
const int N=8e6+10;
int fa[N];
int find(int n)
{
	if(fa[n]==n)
	{
		return n;
	}
	else
	{
		fa[n]=find(fa[n]);
		return fa[n];
	}

}
void add(int i,int j)
{
	int fi=find(i);
	int fj=find(j);
	if(fj!=fi)
	{
		fa[fi]=fj;
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		fa[i]=i;
	}
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		cin>>a>>b>>c;
		if(a==0)
		{
			add(b,c);
		}
		else
		{
			int x=find(b);
			int y=find(c);
			if(x==y)
			{
				ans=ans*2+1;
			}
			else
			{
				ans*=2;
			}
			ans=ans%998244353;
		}
	}
	
	cout<<ans<<endl;
}