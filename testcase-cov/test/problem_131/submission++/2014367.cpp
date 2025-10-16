#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n, q, a[N], c[N];
int lowbit(int x) {return x&-x;}
void add(int x, int v) {while(x<=n) c[x]+=v, x+=lowbit(x);}
int sum(int x){int s=0; while(x>0) s+=c[x], x-=lowbit(x); return s;}
signed main() {
	scanf("%d%d", &n, &q);
	for(int i=1;i<=n;i++) scanf("%lld", &a[i]), add(i, a[i]-a[i-1]);
	while(q--) {
		int op, l, r, x; 
		scanf("%lld", &op);
		if(op==1) scanf("%lld%lld%lld", &l, &r, &x), add(l, x), add(r+1, -x);
		else scanf("%lld", &x), printf("%lld\n", sum(x));
	}
	return 0;
}  