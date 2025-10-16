#include<bits/stdc++.h>
#define pb emplace_back
#define ins emplace
using namespace std;
typedef long long ll;
const int N=2e5+10;

int T; ll n;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&n);
		if(n<=3) puts("No\nNo");
		else{
			puts("Yes");
			if(n&1) puts("No");
			else puts("Yes");
		}
	}
	return 0;
}