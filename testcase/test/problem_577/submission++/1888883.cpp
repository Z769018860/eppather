#include <bits/stdc++.h>
using namespace std;
int n, p, Q, a[55], pw[55][55], g[2][55][2555], V, C[55][55];
void Add(int &x, int y) {
	x += y; if (x >= p) x -= p;
}
long long m, k;
int b[65], c[65], len, f[65][55];
bool vis[65][55];
int dp(int len, int lst) {
	if (!len) return !lst;
	if (vis[len][lst]) return f[len][lst];
	int now = lst * p + c[len];
	int &res = f[len][lst] = 0;
	vis[len][lst] = true;
	for (int i = 0; i <= n; ++i) {
		Add(res, 1ll * g[ n & 1 ][ b[len] ][ now - i ] * dp(len - 1, i) % p);
	}
	return res;
}
int solve() {
	len = 0;
	long long m1 = m, k1 = k;
	while (m1 or k1) {
		++len;
		b[len] = m1 % p, c[len] = k1 % p;
		m1 /= p, k1 /= p;
	}
	for (int i = 1; i <= len; ++i) {
		for (int j = 0; j <= n; ++j) vis[i][j] = false;
	}
	return dp(len, 0);
}
int main() {
	ios :: sync_with_stdio(0), cin.tie(0);
	cin >> n >> p;
	for (int i = 0; i <= n; ++i) cin >> a[i];
	for (int i = 0; i < p; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j) C[i][j] = (C[ i - 1 ][j] + C[ i - 1 ][ j - 1 ]) % p;
	}
	for (int i = 0; i <= n; ++i) {
		pw[i][0] = 1;
		for (int j = 1; j < p; ++j) {
			pw[i][j] = 1ll * pw[i][ j - 1 ] * a[i] % p;
		}
	}
	V = n * p + p, g[1][0][0] = 1;
	for (int i = 0; i <= n; ++i) {
		int t = i & 1;
		for (int k = 0; k < p; ++k) {
			for (int l = 0; l <= V; ++l) g[t][k][l] = 0;
		}
		for (int j = 0; j < p; ++j) {
			for (int k = j; k < p; ++k) {
				int y = i * j;
				for (int l = y; l <= V; ++l) {
					Add(g[t][k][l], 1ll * C[k][j] * g[ t ^ 1 ][ k - j ][ l - y ] % p * pw[i][j] % p);
				}
			}
		}
	}
	cin >> Q;
	while (Q--) {
		cin >> m >> k;
		cout << solve() << '\n';
	}
	return 0;
}