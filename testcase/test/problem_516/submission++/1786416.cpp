
#include <map>
#include <set>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, a[100005], idx, ans = 2147483647;
map<int, int> mp;
set<int> s[100005];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (!mp.count(a[i])) mp[a[i]] = ++idx;
		if (!s[mp[a[i]]].empty()) {
			
			ans = min(ans, i - *s[mp[a[i]]].rbegin());
		}
		s[mp[a[i]]].insert(i);
		
	}
	
	while (m--) {
		int x, y;
		cin >> x >> y;
		if (x == y) {cout << ans << '\n'; continue;}
		if (!mp.count(x)) {cout << ans << '\n'; continue;}
		if (!mp.count(y)) {
			mp[y] = mp[x];
			mp.erase(x);
			cout << ans << '\n';
			continue;
		}
		int fx = mp[x], fy = mp[y];
		if (s[fx].size() > s[fy].size()) swap(fx, fy);
		mp[y] = fy;
		mp.erase(x);
		for (auto i : s[fx]) {
			if (i > *s[fy].begin())
				ans = min(ans, i - *prev(s[fy].upper_bound(i)));
			if (i < *s[fy].rbegin())
				ans = min(ans, *s[fy].upper_bound(i) - i);
			s[fy].insert(i);
		}
		set<int>().swap(s[fx]);
		cout << ans << '\n';
	}
	return 0;
}