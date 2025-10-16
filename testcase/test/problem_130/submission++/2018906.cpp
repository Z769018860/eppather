#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<numeric>
using namespace std;
using ll = long long;
struct BIT {
	int n; vector<ll> C;
	BIT(int _) : n(_), C(_ + 2, 0) {};
	inline int lowbit(int x) { return x & -x; }
	void add(int x, ll v) {
		while (x <= n) C[x] += v, x += lowbit(x);
	}
	ll sum(int a) {
		ll cnt = 0;
		while (a) cnt += C[a], a -= lowbit(a);
		return cnt;
	}
};

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q; cin >> n >> q;
	BIT B(n);
	for (int i = 1, x; i <= n; ++i) cin >> x, B.add(i, x);
	for (int i = 0, a, b, c; i < q; ++i) {
		cin >> a >> b >> c;
		if (a == 1) B.add(b, c);
		else printf("%lld\n", B.sum(c) - B.sum(b - 1));
	}

	return 0;
};