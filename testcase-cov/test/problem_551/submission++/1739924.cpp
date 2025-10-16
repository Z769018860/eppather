
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int main() {
	int T; scanf("%d",&T);
	while(T--) {
		ll n; scanf("%lld",&n);
		if(n<=3) puts("No\nNo");
		else {
			if(n&1) puts("Yes\nNo");
			else puts("Yes\nYes");
		}
	}
}