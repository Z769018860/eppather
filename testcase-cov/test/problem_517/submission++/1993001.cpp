#include <bits/stdc++.h>

#define ll long long
#define REP(i, l, r) for(int i = l; i <= r; ++i)
#define PER(i, r, l) for(int i = r; i >= l; --i)

using namespace std;

namespace Main {
	const int N = 2e5 + 5, V = 29;
	int n, m, cur;
	int a[N];
	int sum[N][V + 5];
	void getsum(int i) {
		for(int j = V; j >= 0; --j) {
			sum[i][j] = sum[i - 1][j] + (a[i] >> j & 1);
		}
	}
	int a1, a2;
	struct Trie {
		int ch[2];
		int sz;
		int dat[V + 2];
	} t[N * V];
	int tot = 1;
	void insert(int v) {
		int u = 1;
		vector<int> val;
		REP(i, 0, 30)
			if(v >> i & 1) val.emplace_back(i);
		PER(i, V, 0) {
			int c = (v >> i) & 1;
			if(!t[u].ch[c]) t[u].ch[c] = ++tot;
			u = t[u].ch[c];
			++t[u].sz;
			for(int &c: val) {
				++t[u].dat[c];
			}
		}
	}
	int s[V + 5];
	void ask(int p, int o, int k) {
		if (o < 0) return;
		int c = a2 >> o & 1, l = t[p].ch[c], r = t[p].ch[c ^ 1];
		if (t[l].sz <= k) {
			REP(j, 0, V) s[j] += t[l].dat[j];
			if (k > t[l].sz) {
				if (o > 0) ask(r, o - 1, k - t[l].sz);
				else
					REP(j, 0, V) s[j] += t[r].dat[j] / t[r].sz * (k - t[l].sz);
			}
		} else if (o > 0)
			ask(l, o - 1, k);
		else {
			REP(j, 0, V) s[j] += t[l].dat[j] / t[l].sz * k;
		}
	}

	ll query(int x) {
		if(!x) return 0;
		REP(i, 0, V) s[i] = 0;
		ask(1, V, x);
		
		ll res = 0;
		PER(i, V, 0) {
			if(a1 >> i & 1)
				res += (1ll << i) * (x - s[i]);
			else res += (1ll << i) * s[i];
		}
		return res;
	}
	ll sigma(int id) {
		id -= n;
		ll res = 0;
		PER(i, V, 0) {
			if(a1 >> i & 1)
				res += (1ll << i) * (id - sum[id][i]);
			else res += (1ll << i) * sum[id][i];
		}
		return res;
	}
	int main() {
		ios ::sync_with_stdio(false);
		cin.tie(0), cout.tie(0);
		cin >> n;
		for(int i = 1; i <= n; ++i) {
			cin >> a[i];
			getsum(i);
		}
		cur = n;
		n = 0;
		cin >> m;
		for(int ti = 1, op, l, r, x; ti <= m; ++ti) {
			cin >> op;
			if(op == 1) {
				cin >> x;
				a[++cur] = x ^ a1;
				getsum(cur);
			}
			else if(op == 2) {
				cin >> l >> r;
				ll ans = 0;
				if (r > n) ans += sigma(r);

				if (l <= n) ans += query(min(r, n)) - query(l - 1);
				else ans -= sigma(l - 1);

				cout << ans << '\n';
			}
			else if(op == 3) {
				cin >> x;
				a1 ^= x;
			}
			else {
				REP(i, 1, cur) insert(a[i]);
				n += cur, cur = 0, a2 = a1;
			}
		}
		return 0;
	}
}

int main() {
	Main :: main();
	return 0;
}