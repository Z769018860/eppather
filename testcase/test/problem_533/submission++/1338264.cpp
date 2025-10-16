#ifdef xay5421
#define D(...) fprintf(stderr,__VA_ARGS__)
#else
#define D(...) ((void)0)

#endif
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int n;
long long dp[2000];
int main(){
	for(int i=1;;++i){
		dp[i]=i-1;
		rep(j,1,i-1){
			dp[i]=max(dp[i],dp[i-j-1]*j);
		}
		if(dp[i]>1e18){n=i;break;}
	}
	
	int T;
	scanf("%d",&T);
	while(T--){
		long long k;
		scanf("%lld",&k);
		printf("%d\n",(int)(lower_bound(dp+1,dp+n+1,k)-dp)*2);
	}
	return 0;
}