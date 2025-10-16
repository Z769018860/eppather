#include<iostream>
#define int long long

using namespace std;

const int maxn=5e3;
int a[maxn][maxn],n,m;

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
			cin>>x1>>y1;
			cout<<query(x1,y1)<<"\n";
		}
	}
}










