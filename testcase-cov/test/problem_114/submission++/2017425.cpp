#include <bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

const int N = 55;
int n, m, k;
ll p[N], q[N];

void ins(ll x) {
	for (int i = 50; ~i; i--) {
		if ((x >> i) & 1 ^ 1) continue;
		if (!p[i]) return p[i] = x, void();
		x ^= p[i];
	}
}

void bld() {
	for (int i = 0; i <= 50; i++)
		for (int j = i - 1; ~j; j--)
			if ((p[i] >> j) & 1) p[i] ^= p[j];
	for (int i = 0; i <= 50; i++)
		if (p[i]) q[m++] = p[i];
}

ll qry(ll x) {
	if (m != n) x--;
	if ((1ll << m) <= x) return -1;
	ll res = 0;
	for (int i = 0; i < m; i++)
		if ((x >> i) & 1) res ^= q[i];
	return res;
}

void solve() {
	cin >> n; ll x;
	for (int i = 1; i <= n; i++) cin >> x, ins(x);
	bld(), cin >> k;
	for (int i = 1; i <= k; i++)
		cin >> x, cout << qry(x) << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	#ifdef FILE
		freopen(".in", "r", stdin);
		freopen(".out", "w", stdout);
	#endif
	int T = 1;

	while (T--) solve();
	return 0;
}
