#include <bits/stdc++.h>
#define int long long

using namespace std;

const int NR = 1e6 + 5;
const int MOD = 998244353;

int n, q, m, type, a[NR], lansx, lansy;

struct Matrix {
	int c11, c12, c21, c22;
	Matrix operator * (const Matrix &rhs) const {
	    Matrix ans;
	    ans.c11 = (c11 * rhs.c11 + c12 * rhs.c21) % MOD;
	    ans.c12 = (c11 * rhs.c12 + c12 * rhs.c22) % MOD;
	    ans.c21 = (c21 * rhs.c11 + c22 * rhs.c21) % MOD;
	    ans.c22 = (c21 * rhs.c12 + c22 * rhs.c22) % MOD;
	    return ans;
	}
} sum[NR << 2], dw;

inline void pushup(int p) {
	sum[p] = sum[p << 1] * sum[p << 1 | 1];
}

inline void modify(int p, int l, int r, int x, int v) {
	if (l == r) {
		sum[p] = (Matrix){v, 1, 1, 0};
		return;
	}
	int mid = l + r >> 1;
	if (x <= mid) modify(p << 1, l, mid, x, v);
	else modify(p << 1 | 1, mid + 1, r, x, v);
	pushup(p);
}

inline Matrix query(int p, int l, int r, int a, int b) {
	if (a > r || b < l) return dw;
	if (a <= l && r <= b) return sum[p];
	int mid = l + r >> 1;
	return query(p << 1, l, mid, a, b) * query(p << 1 | 1, mid + 1, r, a, b);
}

signed main() {
	ios :: sync_with_stdio(false), cin.tie(0);
	dw.c11 = dw.c22 = 1;
	cin >> n >> q >> type, m = n + q;
	for (int i = 1; i <= n; ++i) cin >> a[i], modify(1, 1, m, i, a[i]);
	while (q --) {
		int op, x, l, r; cin >> op; Matrix t;
		if (op == 1) {
			cin >> x;
			if (type) x ^= (lansx ^ lansy);
			n ++, a[n] = x;
			modify(1, 1, m, n, x);
		}
		if (op == 2) {
			cin >> l >> r;
			if (type) l ^= (lansx ^ lansy), r ^= (lansx ^ lansy);
			if (l == r) cout << (lansx = a[r]) << ' ' << (lansy = 1) << '\n';
			else t = query(1, 1, m, l, r - 1), cout << (lansx = (t.c11 * a[r] + t.c12) % MOD) << ' ' << (lansy = (t.c21 * a[r] + t.c22) % MOD) << '\n';
		}
	}
	return 0;
}