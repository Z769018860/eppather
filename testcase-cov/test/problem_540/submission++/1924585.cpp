#include<bits/stdc++.h>
#define maxn 2000005
#define ll long long
#define mod 998244353
using namespace std;
ll C[505][505];
int dp[maxn],pre[maxn];
void MIN(int &x,int y) {if (x==-1) x=y; x=min(x,y); return;}
ll gx[505];

void init()
{
	C[0][0]=1;
	for (int i=1;i<=500;i++)
		for (int j=0;j<=i;j++)
		{
			if (i==1 || j==0) C[i][j]=1;
			else C[i][j]=(C[i-1][j]+C[i-1][j-1]);
		}
	for (int i=3;i<=500;i++) gx[i]=C[i][3];
} 

int e[505][505];

int main()
{
	init();	
	memset(dp,-1,sizeof(dp));
	dp[0]=0;
	for (int i=0;i<2000000;i++)
	if (dp[i]!=-1)
	{
		for (int j=3;gx[j]<=2000000-i && j<=500-dp[i];j++)
		{
			MIN(dp[i+gx[j]],dp[i]+j);
			if (dp[i+gx[j]]==dp[i]+j) pre[i+gx[j]]=j;
		}
	}
	int n;
	cin>>n;
	int now=0;
	while (n)
	{
		int tt=pre[n];
		n-=gx[tt];
		for (int i=now+1;i<=now+tt;i++)
		for (int j=now+1;j<=now+tt;j++)
			e[i][j]=1;
		now+=tt;
	}
	cout<<now<<endl;
	for (int i=1;i<now;i++)
	{
		for (int j=i+1;j<=now;j++)
			cout<<e[i][j]<<" ";
		cout<<endl;
	}
}