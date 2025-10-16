
#include <bits/stdc++.h>
using i64 = long long;

constexpr i64 inf = 1e18;
constexpr int UP = INT_MAX;

int n, m;

std::map<int, i64> mp;
inline void chkmin(i64 &a, const i64 &b)	{if (a > b)	a = b;}

inline void insert(i64 val, int sz) {
	auto it = mp.end();
	it--, it--;
  	while (true) {
		auto p = it;
		int v = ( (sz & it->first) == 0 ? 0 : ((1 << std::__lg(sz & it->first)) - 1) );
		v |= (sz | it->first);
		for (; p->first < v; p++) {
			chkmin(p->second, val + it->second);
		}
		if (p->second > val + it->second)
			mp[v] = val + it->second;
		if (it == mp.begin())
			break;
		else
			it--;
	}
	for (auto p = mp.begin(); std::next(p) != mp.end(); ) {
		if (p->second == std::next(p)->second)
			p = mp.erase(p);
		else
			p++;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> m;
	mp[0] = 0, mp[UP] = inf;
	for (int i = 1; i <= n; i++) {
		i64 v, l;
		std::cin >> v >> l;
		insert(v, l);
	}

	int q;
	std::cin >> q;
	while (q--) {
		int c;
		std::cin >> c;
		auto it = mp.lower_bound(c);
		if (it->second == inf)
			std::cout << "-1\n";
		else
			std::cout << it->second << '\n';
	}
	return 0;
}
