#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int T;
int main(){
	scanf("%d",&T);
	while(T--){
		int n,K;
		scanf("%d%d",&n,&K);
		rep(i,1,K)scanf("%*d%*d%*d");
		puts((n+K)&1?"YES":"NO");
	}
	return 0;
}