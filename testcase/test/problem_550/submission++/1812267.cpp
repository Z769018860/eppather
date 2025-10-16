#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int T,n,m,k;
int main()
{
	cin>>T;
	while(T--)
	{
		scanf("%d%d%d",&n,&m,&k);
		printf("%lld\n",1ll*(n-n/2)*(n/2)*m+1ll*(m-m/2)*(m/2)*n);
		
	}
	
	return 0;
 } 