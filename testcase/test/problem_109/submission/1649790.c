#include<stdio.h>

int f[4000001];

int find(int x)
{
	if(f[x]!=x)f[x]=find(f[x]);
	return f[x];
}

void link(int x,int y)
{
	int xf=find(x);
	int yf=find(y);
	if(xf!=yf)f[yf]=xf;
}

int read()
{
	char b=getchar();
	int sum=0;
	while(b<'0'||b>'9')
		b=getchar();
	while(b>='0'&&b<='9')
	{
		sum=sum*10+b-'0';
		b=getchar();
	}
	return sum;
}

int main()
{
	int n,m,i,op,x,y;
	long long ans=0,a;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++)
		f[i]=i;	
	for(i=0;i<m;i++)
	{
		op=read();
		x=read();
		y=read();
		if(op==0)link(x,y);
		else
		{
			if(find(x)==find(y))a=1;
			else a=0;
			ans=((ans<<1)+a)%998244353;
		}
	}
	printf("%lld",ans);
	return 0;	
}