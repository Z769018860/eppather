#include<cstdio>
#include<algorithm>
using namespace std;
long long lib[63];
int n;
int ans[5005];
long long k;

int a[105];
int cnt;
bool ans_flag;
void dfs(int x,long long k)
{
	if(k==1)
	{
		ans_flag=true;
		cnt=x-1;
		return;
	}
	for(int i=62;i>=2;i--)
	{
		if(k%lib[i]==0)
		{
			a[x]=i;
			dfs(x+1,k/lib[i]);
			if(ans_flag)
			{
				break;
			}
		}
	}
}
int main()
{
	for(int i=1;i<=62;i++)
	{
		lib[i]=(1ll<<i)-1;
		
	}
	scanf("%lld",&k);
	ans[++n]=0;
	for(int i=1;k%2==0;i++)
	{
		ans[++n]=i;
		k/=2;
	}
	
	if(k==1)
	{
		ans[++n]=100;
	}
	else
	{
				dfs(1,k);
		if(!ans_flag)
		{
			printf("qnq\n");
			return 0;
		}
		for(int i=1;i<=cnt;i++)
		{
			for(int j=1;j<=a[i];j++)
			{
				ans[++n]=100;
			}
			ans[++n]=1;
		}
	}
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
	{
		printf("%lld ",ans[i]);
	}
	printf("\n");
	return 0;
}
