







#include <bits/stdc++.h>
#define pb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

const int P = 998244353;
const int i2 = (P + 1) / 2;
const int i6 = (P + 1) / 6;

int s0(int x) { return x; }
int s1(int x) { return 1ll * x * (x + 1) % P * i2 % P; }
int s2(int x) { return 1ll * x * (x + 1) % P * (2 * x + 1) % P * i6 % P; }

int calc(int n, int op) {
	int res = 0;
	for (int l = 1, r, w; l <= n; l = r + 1) {
		r = n / (n / l);
		if (!op) w = r - l + 1;
		else if (op == 1) w = (s1(r) - s1(l - 1) + P) % P;
		else w = (s2(r) - s2(l - 1) + P) % P;
		(res += 1ll * w * (n / l) % P) %= P;
	}
	return res;
}

void solve() {
	int n; cin >> n;
	cout << (2ll * calc(n, 2) + 3ll * calc(n, 1) + 5ll * calc(n, 0)) % P << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}