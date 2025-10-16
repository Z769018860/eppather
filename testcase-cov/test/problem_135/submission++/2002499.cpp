#include<iostream>
#define int long long

using namespace std;

const int maxn=5e3;
int n,m;

struct tree
{
	int a[maxn][maxn];
	void update(int x,int y,int p)
	{
		for(int i=x;i<=n;i+=(i&(-i)))
			for(int j=y;j<=m;j+=(j&(-j)))
				a[i][j]+=p;
	}
	int query(int x,int y)
	{
		int ret=0;
		for(int i=x;i;i-=(i&(-i)))
			for(int j=y;j;j-=(j&(-j)))
				ret+=a[i][j];
		return ret;
	}
}a,b,c,d;

void update(int x,int y,int p)
{
	a.update(x,y,p);
	b.update(x,y,p*x);
	c.update(x,y,p*y);
	d.update(x,y,p*x*y);
}

int query(int x,int y)
{
	int ret=0;
	ret+=a.query(x,y)*(x*y+x+y+1);
	ret-=b.query(x,y)*(y+1);
	ret-=c.query(x,y)*(x+1);
	ret+=d.query(x,y);
	return ret;
}

main()
{
	cin>>n>>m;
	int op,x1,x2,y1,y2,k;
	while(cin>>op)
	{
		if(op==1)
		{
			cin>>x1>>y1>>x2>>y2>>k;
			update(x1,y1,k);
			update(x2+1,y2+1,k);
			update(x2+1,y1,-k);
			update(x1,y2+1,-k);
		}
		else
		{
			cin>>x1>>y1>>x2>>y2;
			cout<<query(x2,y2)-query(x2,y1-1)-query(x1-1,y2)+query(x1-1,y1-1)<<"\n";
		}
	}
}










