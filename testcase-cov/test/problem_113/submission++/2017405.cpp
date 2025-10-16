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
int n;
ll p[N];

void ins(ll x) {
	for (int i = 50; ~i; i--) {
		if ((x >> i) & 1 ^ 1) continue;
		if (!p[i]) return p[i] = x, void();
		x ^= p[i];
	}
}

void solve() {
	cin >> n; ll x; 
	for (int i = 1; i <= n; i++) cin >> x, ins(x);
	ll res = 0;
	for (int i = 50; ~i; i--)
		if (!((res >> i) & 1) && p[i]) res ^= p[i];
	cout << res << '\n';
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
