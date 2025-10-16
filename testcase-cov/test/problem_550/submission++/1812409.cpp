#include <bits/stdc++.h>
using namespace std;
int t,n,m,k;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&m,&k);
		printf("%lld\n",1ll*((n+1)/2)*(n/2)*m+1ll*((m+1)/2)*(m/2)*n);
	}
	return 0;
}