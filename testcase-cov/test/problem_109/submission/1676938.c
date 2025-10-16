#include<stdio.h>
int n = 0, m = 0;
int ans = 0;
int a[8000005] = { 0 };
int par[8000005] = { 0 };

void init()
{
	for (int i = 0; i < 8000005; i++){
		par[i] = i;
		
	}
}
int find(int x)
{
	if(par[x] == x) return x;
	else return par[x] = find(par[x]);
}
void unite(int x,int y)
{
	x = find(x);
	y = find(y);
	if(x != y) 
	{
		par[x] = y;
	}
}
int main()
{
	int yy = 0;
	
	
	scanf("%d %d",&n,&m);
	init();
	for (int  i = 0; i < m; i++)
	{
		int op, u, v;
		
		 
		 
		 scanf("%d %d %d",&op,&u,&v);
		if(op == 0)
		{
			unite( u, v);
		}
		else if(op == 1)
		{
			int ooo = 0;
			if(find(u) == find(v))
			{
				ans *= 2;
				ans++;
				ans %= 998244353;
			}
			else
			{
				ans *= 2;
				ans %= 998244353;
			}
		}
	}

	printf("%d\n",ans);
	return 0;
}