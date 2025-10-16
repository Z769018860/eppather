# include <bits/stdc++.h>
using namespace std;
int a[1010][1010],b[1010][1010],ri[1010][1010],dn[1010][1010];
bitset<1000> e[1010][1010];
struct Node
{
	int l,r;
	Node(int l=0,int r=0):l(l),r(r){}
	bool operator<(Node t)const{return l<t.l;}
}c[1010][1010],d[1010][1010];
int main()
{
	int n,m,ans=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&b[i][j]);
	for(int i=1;i<=n;i++)
	{
		ri[i][m]=m;
		for(int j=m-1;j;j--) ri[i][j]=(a[i][j]?ri[i][j+1]:j);
		for(int j=1;j<=m;j++) c[j][i]=Node(max(i+j-ri[i][j],1),i);
	}
	for(int i=1;i<=m;i++)
	{
		sort(c[i]+1,c[i]+n+1);
		bitset<1000> cur;
		for(int j=1,k=1;j<=n;j++)
		{
			for(;k<=n && c[i][k].l<=j;k++) cur[c[i][k].r-j]=1;
			cur>>=1;e[j][i]=cur;
		}
	}
	for(int i=1;i<=m;i++)
	{
		dn[n][i]=n;
		for(int j=n-1;j;j--) dn[j][i]=(b[j][i]?dn[j+1][i]:j);
		for(int j=1;j<=n;j++) d[j][i]=Node(max(i+j-dn[j][i],1),i);
	}
	for(int i=1;i<=n;i++)
	{
		sort(d[i]+1,d[i]+m+1);
		bitset<1000> cur;
		for(int j=1,k=1;j<=m;j++)
		{
			for(;k<=m && d[i][k].l<=j;k++) cur[d[i][k].r-j]=1;
			cur>>=1;e[i][j]&=cur;
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int k=min(ri[i][j]-j,dn[i][j]-i);
			e[i][j]<<=1000-k;
			ans+=e[i][j].count();
		}
	cout<<ans<<endl;
	return 0;
}