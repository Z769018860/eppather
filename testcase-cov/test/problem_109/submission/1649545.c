#include<stdio.h>
int fa[8000010];
int h[8000010];
const int long long mod=998244353;
long long ksm(int b)
{
	long long ans=1;
	long long a=2;
	while(b!=0)
	{
		if(b%2==1)
		{
			ans=ans*a%mod; 
			b--;
		}
		else
		{
			a=a*a%mod;
			b=b/2;		
		}
	}
	return ans%mod;
}
int find (int x)
{
	if(fa[x]==x)
	{
		return x;
	}
	else
	{
		return fa[x]=find(fa[x]);
	}
}
void lianjie(int x,int y)
{
	int p=find(x);
	int q=find(y);
	if(p!=q)
	{
		fa[p]=q;
	}
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)
	{
		fa[i]=i;
	}
	 int k=0;
     for(int i=1;i<=m;i++)
     {
	 	 int a,b,c;
		 scanf("%d%d%d",&a,&b,&c);
		 if(a==0)
		 {
		 	lianjie(b,c);
		 } 
		 else if(a==1)
		 {
		 	int f=find(b);
		 	int g=find(c);
		 	if(f!=g)
		 	{
			 	h[k]=0;
			 	k=k+1; 
			 }
			 else
			 {
			 	h[k]=1;
		
			 	k=k+1;
			 }
		 }
	}




 
     long long sum=0;
     for(int i=0;i<k;i++)
     {
	 	if(h[i]==1)
	 	{
		  
		  int p=k-1-i;
		  sum=(sum%mod+ksm(p)%mod)%mod;


		 }
	 }
	 printf("%lld\n",sum);
	 return 0;
}