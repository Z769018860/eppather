#include<iostream>
using namespace std;
int father[4000010];
long long ans=0;
int p=0,temp;
const long long mod=998244353;
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*f;
}
int find(int k)
{
	if(father[k]!=k) 
		father[k]=find(father[k]);
	return father[k];
}
 
void _union(int x,int y)
{
	if(x>y) temp=x,x=y,y=temp;
	x=find(x);
	y=find(y);
	if(x!=y)
		father[y]=x;
} 
 
int main()
{
	int op,u,v,n,m;n=read();m=read();
	for(int i=1;i<=n;i++)
		father[i]=i;
	while(m--)
	{
		op=read();u=read();v=read();
		if(op==0)
			_union(u,v);
		else if(op==1)
		{
			if(find(u)==find(v))
			{
				ans*=2;
				ans+=1;
				ans%=mod;
				p++;
			}
			else if(p!=0)
			{
			 	ans*=2;
			 	ans%=mod;
			}
		}
	}
	cout<<ans;
	return 0;
} 