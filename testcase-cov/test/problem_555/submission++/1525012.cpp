#include <bits/stdc++.h>

#define eprintf(args...) fprintf(stderr, args)
#define rep(i, n) for (int i = 0; i < (int)(n); ++ i)

using i64 = long long;
const int mod = 998244353;

inline int qpow(int x, i64 n) {
	int ans = 1;
	for (; n; n >>= 1, x = 1LL * x * x % mod)
		if (n & 1) ans = 1LL * ans * x % mod;
	return ans;
}

inline int comb(i64 n, i64 m) {
	if (m < 0 || m > n) return 0;
	if (m > n - m) m = n - m;
	int P = 1, Q = 1;
	for (i64 i = 0; i < m; ++ i) {
		P = 1LL * P * ((n - i) % mod) % mod;
		Q = 1LL * Q * ((m - i) % mod) % mod;
	}
	return 1LL * P * qpow(Q, mod - 2) % mod;
}

int pA, pB, D;

namespace fft {
;

const int mxn = 2048;
int N, r[mxn], w[mxn];
inline void init(int n) {
	if (N == n) return ;
	N = n;
	for (int i = 1; i < n - 1; ++ i)
		r[i] = r[i >> 1] >> 1 | (i & 1 ? n >> 1 : 0);
	for (int h = 1; h < n; h <<= 1) {
		int t = qpow(3, (mod - 1) / (h << 1));
		rep(i, h) w[h + i] = i ? 1LL * t * w[h + i - 1] % mod : 1;
	}
}
inline void dft(int a[], int n) {
	init(n);
	for (int i = 1; i < n - 1; ++ i)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int h = 1; h < n; h <<= 1)
		for (int i = 0; i < n; i += h << 1)
			for (int j = 0; j < h; ++ j) {
				int v = 1LL * a[i + h + j] * w[h + j] % mod;
				a[i + h + j] = a[i + j] - v >= 0 ? a[i + j] - v : a[i + j] + mod - v;
				a[i + j] = a[i + j] + v < mod ? a[i + j] + v : a[i + j] + v - mod;
			}
}
inline void idft(int a[], int n) {
	dft(a, n);
	std::reverse(a + 1, a + n);
	int iv = qpow(n, mod - 2);
	rep(i, n) a[i] = 1LL * a[i] * iv % mod;
}

} 

struct poly {
	int va[1005];
	poly() { memset(va, 0, sizeof(va)); }
	inline int &operator [] (int x) { return va[x]; }
	inline const int &operator [] (int x) const { return va[x]; }
	friend inline poly operator + (const poly &a, const poly &b) {
		poly c;
		rep(i, D) c[i] = (a[i] + b[i]) % mod;
		return c;
	}
	friend inline poly operator * (const poly &a, const poly &b) {
		int sz = 1;
		for (; sz < D + D - 1; sz <<= 1);
		static int A[fft::mxn], B[fft::mxn];
		rep(i, sz) A[i] = i < D ? a[i] : 0;
		rep(i, sz) B[i] = i < D ? b[i] : 0;
		fft::dft(A, sz); fft::dft(B, sz);
		rep(i, sz) A[i] = 1LL * A[i] * B[i] % mod;
		fft::idft(A, sz);
		poly c;
		rep(i, sz) c[i % D] = (c[i % D] + A[i]) % mod;
		return c;
	}
};

struct item {
	poly pow, sum;
};

inline item solve(poly f, i64 n) {
	if (n == 0) { item s; s.pow[0] = 1; return s; }
	if (n & 1) {
		item s = solve(f, n - 1);
		return {s.pow * f, s.sum + s.pow};
	}
	item s = solve(f, n >> 1);
	return {s.pow * s.pow, s.sum + s.sum * s.pow};
}

inline int F(int x, int y, i64 n) {
	poly F;
	F[0 % D] = (F[0 % D] + pA) % mod;
	F[1 % D] = (F[1 % D] + pB) % mod;
	poly G = solve(F, D).pow;
	int ans = 0;
	int z = (D - x + D - y) % D;
	if (n <= z) ans = 0;
	else {
		poly P = solve(G, (n - z + D - 1) / D).sum;
		poly Q = solve(F, z).pow;
		poly res = Q * P;
		ans = res[(D - y) % D];
	}
	
	return ans;
}

int main() {
	scanf("%d %d", &pA, &pB);
	std::swap(pA, pB);
	i64 n;
	int m, K;
	scanf("%lld %d %d %d", &n, &D, &m, &K);
	static int X[55];
	static i64 Y[55];
	rep(i, K) scanf("%d %lld", &X[i], &Y[i]);
	X[K] = Y[K] = 0, ++ K;
	std::vector <int> id(K);
	std::iota(id.begin(), id.end(), 0);
	std::sort(id.begin(), id.end(), [&] (int i, int j) {
		return X[i] != X[j] ? X[i] > X[j] : Y[i] > Y[j];
	});
	static int f[55];
	for (int i : id) {
		f[i] = (mod - F(X[i] % D, Y[i] % D, n - (X[i] + Y[i]) + 1)) % mod;
		for (int j : id) {
			if (i == j) break;
			if (X[i] <= X[j] && Y[i] <= Y[j]) {
				int prob = 1LL * qpow(pA, X[j] - X[i]) * qpow(pB, Y[j] - Y[i]) % mod;
				prob = 1LL * prob * comb(X[j] - X[i] + Y[j] - Y[i], X[j] - X[i]) % mod;
				f[i] = (f[i] + mod - 1LL * prob * f[j] % mod) % mod;
			}
		}
	}
	int ans = (mod - f[K - 1]) % mod;
	printf("%d\n", ans);
	return 0;
}
