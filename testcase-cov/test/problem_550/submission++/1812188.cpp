#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
ll ans;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		ll n,m,x;
		scanf("%lld%lld%lld",&n,&m,&x);
		if(m%2==1)swap(n,m);
		if(m%2==1)
			ans=(n+1)/2*(m/2)*((n+1)/2+m/2)+(n/2)*(m+1)/2*(n/2+(m+1)/2);
		else if(n%2==1)
			ans=(n+1)/2*(m/2)*((n+1)/2+m/2-1)+n/2*(m/2)*(n/2+m/2+1);
		else 
			ans=n/2*(m/2)*(n/2+m/2)*2;
		printf("%lld\n",ans);
	}
	return 0;
}