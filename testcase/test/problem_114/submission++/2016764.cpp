#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=110;
int n, cnt, d[N], p[N];
void add(int x) {
	for(int i=60;i>=0;i--) 
		if(x>>i&1) {
			if(!d[i]) {d[i]=x; break;}
			else x^=d[i];
		}
}
void rebuild() {
	for(int i=0;i<=60;i++) for(int j=i-1;j>=0;j--) if(d[i]&(1ll<<j)) d[i]^=d[j];
	for(int i=0;i<=60;i++) if(d[i]) p[cnt++]=i;
}
int kth(int k) {
	int ans=0;
	if(cnt<n) k--;
	if(k>=(1ll<<cnt)) return -1;
	for(int j=0;j<cnt;j++) if(k&(1ll<<j)) ans^=d[p[j]];
	return ans;
}
signed main() {
	scanf("%lld", &n);
	for(int i=1;i<=n;i++) {
		int x; scanf("%lld", &x); add(x);
	}
	rebuild();
	int m; scanf("%lld", &m);
	while(m--) {
		int k; scanf("%lld", &k);
		printf("%lld\n", kth(k));
	}
	return 0;
}