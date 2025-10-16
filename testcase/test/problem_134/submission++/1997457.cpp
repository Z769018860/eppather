#include<iostream>
using namespace std;
typedef long long ll; 
const int N = 4100;
ll dp[N][N];
int n,m;
int lowbit(int x)
{
	return (x&-x);
}
void add(int x,int y,int z)
{
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=m;j+=lowbit(j))
			dp[i][j]+=z;
}
ll query(int x,int y)
{
	ll res=0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j))
			res+=dp[i][j];
	return res;
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    int k,a,b,c,d,type;
    while(cin>>type)
    {
    	if(type==1)
		{
			cin>>a>>b>>c>>d>>k;
			add(a,b,k);
			add(a,d+1,-k);
			add(c+1,b,-k);
			add(c+1,d+1,k);
		} 
		else
		{
			cin>>a>>b;
			cout<<query(a,b)<<endl;
		}
	}
}