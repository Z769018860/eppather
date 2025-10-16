#include<bits/stdc++.h>
using namespace std;
int main(){


	int t;cin>>t;
	while(t--){
		int N,K;cin>>N>>K;
		int x,y,z;for(int i=1;i<=K;++i)cin>>x>>y>>z;
		if((N*N-K)%2==0)puts("NO");else puts("YES");
	}
	return 0;
} 