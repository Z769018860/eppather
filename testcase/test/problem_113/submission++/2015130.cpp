#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL d[60];
void add(LL x) {
	for(int i=60;i>=0;i--) 
		if(x>>i&1) {
			if(!d[i]) {d[i]=x; break;}
			else x^=d[i];
		}
}
LL getmax() {
	LL ans=0;
	for(int i=60;i>=0;i--) 
		if((ans^d[i])>ans) ans^=d[i];
	return ans;
}
int main() {
	LL n; scanf("%lld", &n);
	for(int i=1;i<=n;i++) {
		LL x; scanf("%lld", &x); add(x);
	}
	printf("%lld", getmax());
	return 0;
}