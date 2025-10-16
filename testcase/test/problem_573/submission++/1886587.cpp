#include <iostream>
#define int long long
using namespace std;
const int N = 1e6 + 10, mod = 998244353;
int n, m, tp, a[N];

struct Matrix {
	int c[3][3];
	Matrix() {
		for(int i = 1; i <= 2; i++)
			for(int j = 1; j <= 2; j++)
				c[i][j] = 0;
	}
	Matrix operator * (const Matrix &T) const {
		Matrix res;
		res.c[1][1] = (c[1][1] * T.c[1][1] + c[1][2] * T.c[2][1]) % mod;
		res.c[1][2] = (c[1][1] * T.c[1][2] + c[1][2] * T.c[2][2]) % mod;
		res.c[2][1] = (c[2][1] * T.c[1][1] + c[2][2] * T.c[2][1]) % mod;
		res.c[2][2] = (c[2][1] * T.c[1][2] + c[2][2] * T.c[2][2]) % mod;
		return res;
	}
} pre[N], inv[N];

Matrix P(int val) {Matrix res; res.c[1][1] = val, res.c[1][2] = 1, res.c[2][1] = 1; return res;}
Matrix Q(int val) {Matrix res; res.c[2][2] = mod - val, res.c[1][2] = 1, res.c[2][1] = 1; return res;}

signed main() {
	ios :: sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> tp;
	for(int i = 1; i <= n; i++) cin >> a[i];
	pre[0].c[1][1] = pre[0].c[2][2] = 1;
	inv[0].c[1][1] = inv[0].c[2][2] = 1;
	for(int i = 1; i <= n; i++) {
		pre[i] = pre[i - 1] * P(a[i]);
		inv[i] = Q(a[i]) * inv[i - 1];
	}
	int ansx = 0, ansy = 0;
	Matrix st;
	st.c[1][1] = 1;
	for(int i = 1, op, x, l, r; i <= m; i++) {
		cin >> op;
		if(op == 1) {
			cin >> x;
			if(tp == 1) x ^= ansx ^ ansy;
			a[++n] = x;
			pre[n] = pre[n - 1] * P(a[n]);
			inv[n] = Q(a[n]) * inv[n - 1];
		}
		else {
			cin >> l >> r;
			if(tp == 1) l ^= ansx ^ ansy, r ^= ansx ^ ansy;
			Matrix ans = inv[l - 1] * pre[r] * st;
			ansx = ans.c[1][1], ansy = ans.c[2][1];
			cout << ansx << ' ' << ansy << '\n';
		}
	}
	return 0;
}