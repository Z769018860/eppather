#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
typedef pair<int, int> PII;
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
__gnu_pbds ::tree<PII, null_type, less<PII>, rb_tree_tag, tree_order_statistics_node_update> tr;
map<int, int> s;
int main() {
	int n; scanf("%d", &n);
	tr.insert({-inf, 1}); tr.insert({inf, 1});
	while(n--) {
		int op, x; scanf("%d%d", &op, &x);
		if(op==0) tr.insert({x, ++s[x]});
		if(op==1) tr.erase({x, s[x]--});
		if(op==2) printf("%d\n", *tr.find_by_order(x));
		if(op==3) printf("%d\n", tr.order_of_key({x, 0})-1);
		if(op==4) {
			auto tp=*--tr.lower_bound({x, 0});
			if(tp.first==-inf) puts("-1"); else printf("%d\n", tp.first);
		}
		if(op==5) {
			auto tp=*tr.upper_bound({x+1, 0});
			if(tp.first==inf) puts("-1"); else printf("%d\n", tp.first);
		}
	}
	return 0;
} 