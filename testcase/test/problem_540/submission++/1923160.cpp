#include<iostream>
#include<cstdio>
using namespace std;
#define int long long
const long long inf=20221027;
const long long N=502,M=502;

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

void wt(int x,char ch=0)
{
	if(x<0) putchar('-'),wt(-x);
	else
	{
		if(x>=10) wt(x/10);
		putchar(x%10+'0');
	}
	if(ch) putchar(ch);
	return ;
}

int n;
int val[N];
bool e[N][N];

signed main()
{
	
	
	n=rd();
	for(int i=1;i<=500;i++)
		val[i]=i*(i-1)*(i-2)/6;
	int j=500;
	int l=1;
	while(j>2)
	{
		while(n>=val[j])
		{
			n-=val[j];
			int r=l+j-1;
			for(int u=l;u<=r;u++)
				for(int v=l;v<=r;v++) if(u!=v)
					e[u][v]=1;
			l+=j;
		}
		j--;
	}
	cout<<500<<"\n";
	for(int i=1;i<=500;i++)
	{
		for(int j=1;i+j<=500;j++)
		{
			cout<<e[i][i+j]<<" ";
		}
		cout<<endl;
	}
	fclose(stdin);
	fclose(stdout);
	return (0-0);
}

