#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
    long long x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
long long n,m,a[100001],sum[100001],x,ans[100001];
bool flag;
int main()
{
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		sum[i]=sum[i-1]+a[i];

	}

	long long maxx=-99999999;
	for(int i=n;i>=1;i--)
	{
		x=-99999999;
		for(int j=1;j+i-1<=n;j++)
		{
			int r=j+i-1;
			x=max(x,sum[r]-sum[j-1]);
		}
		maxx=max(maxx,x);
		ans[i]=maxx;
	}
	while(m--)
	{
		cin>>x;
		cout<<ans[x]<<endl;
	}
	return 0;
}
