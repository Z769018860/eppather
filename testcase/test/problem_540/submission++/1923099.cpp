#include<bits/stdc++.h>
using namespace std;
int vis[510][510];
int n,cnt;
char buf[1<<21],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
long long rd()
{
	long long res=0,f=1;char ch;
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar())
		if(ch=='-') f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())
		res=(res<<3)+(res<<1)+ch-'0';
	return res*f;
}

int main()
{
	
	
	cin>>n;
	for(int i=500;i;i--)
	{
		if(i*(i-1)*(i-2)/6<=n)
		{
			n-=i*(i-1)*(i-2)/6;
			cnt=i;
			for(int i=1;i<=cnt;i++)
			{
				for(int j=i+1;j<=cnt;j++)
				{
					vis[i][j]=1;
				}
			}
			break;
		}
	}
	
	for(int i=cnt;i>=2;i--)
	{
		while(i*(i-1)/2<=n)
		{
			n-=i*(i-1)/2;
			
			cnt++;
			
			for(int j=1;j<=i;j++)
			{
				vis[j][cnt]=1;
			}
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
	{
		for(int j=i+1;j<=cnt;j++)
		{
			cout<<vis[i][j]<<" ";
		}
		cout<<endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}