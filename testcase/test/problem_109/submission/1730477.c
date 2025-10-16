#include<stdio.h>
int f[8000005] = { 0 };
int n,m;
int find(int x)
{
	if(f[x] == x) return x;
	else return f[x] = find(f[x]);
}
int unite(int x,int y)
{
	x = find(x);
	y = find(y);
	if(x != y) 
	{
		f[x] = y;
	}
}
int main()
{
	scanf("%d %d",&n,&m);
	int ans = 0;
	for (int i = 0; i < 8000005; i++)
	 f[i] = i;
	for (int i = 1; i <= m ;i++)
	{
		int o,u,v;
		scanf("%d %d %d",&o,&u,&v);
		if(o == 0)
		{
			unite(u,v);
		}
		else if(o == 1)
		{
			ans *= 2;
			if(find(u) == find(v)) ans ++;
			ans = ans % 998244353;
		}
	}
	printf("%d\n",ans);
	
	return 0;
}