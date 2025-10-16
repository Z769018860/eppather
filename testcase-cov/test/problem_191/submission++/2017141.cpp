#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 7, M = 2e5 + 7;

struct Graph {
	vector<int> e[N];

	inline void insert(int u, int v) {
		e[u].emplace_back(v);
	}
} G, nG;

int deg[N], cnt[N];

ll ans;
int n, m;

template <class T = int>
inline T read() {
	char c = getchar();
	bool sign = (c == '-');
	
	while (c < '0' || c > '9')
		c = getchar(), sign |= (c == '-');
	
	T x = 0;
	
	while ('0' <= c && c <= '9')
		x = (x << 1) + (x << 3) + (c & 15), c = getchar();
	
	return sign ? (~x + 1) : x;
}

signed main() {
	n = read(), m = read();

	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		G.insert(u, v), G.insert(v, u);
		++deg[u], ++deg[v];
	}

	auto cmp = [](const int &x, const int &y) {
		return deg[x] == deg[y] ? x < y : deg[x] > deg[y];
	};

	for (int u = 1; u <= n; ++u)
		for (int v : G.e[u])
			if (cmp(u, v))
				nG.insert(u, v);

	ll ans = 0;

	for (int a = 1; a <= n; ++a) {
		for (int b : nG.e[a])
			for (int c : G.e[b])
				if (cmp(a, c))
					ans += cnt[c]++;

		for (int b : nG.e[a])
			for (int c : G.e[b])
				if (cmp(a, c))
					--cnt[c];
	}

	printf("%lld", ans);
	return 0;
}