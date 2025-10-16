#include<stdio.h>
long long tree[1000001];
int a[1000001];
int n,q;
int lowbit(int x)
{ 
	return x & (-x); 
}
void modify(int i,int x) 
{ 
	while(i<=n)
	{
		tree[i]+=x;
		i+=lowbit(i);
	}
}
long long qry(int r)
{
	long long res=0;
	while(r>0)
	{
		res+=tree[r];
		r-=lowbit(r);
	}
	return res;
}
int main()
{
	int d,b,c;
	scanf("%d%d",&n,&q);
	int a[n];
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		modify(i,a[i]);
	for(int i=0;i<q;i++)
	{
		scanf("%d%d%d",&d,&b,&c);
		if(d==1)
			modify(b,c);
		else
			printf("%lld\n",qry(c)-qry(b-1));
	}
	return 0;
}