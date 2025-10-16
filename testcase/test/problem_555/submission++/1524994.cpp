#include <bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
using namespace std;

typedef pair <long long, long long> pll;

const int mod = 998244353;

void ADD(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod;
}

void SUB(int &x, int y) {
	x -= y;
	if (x < 0) x += mod;
}

long long power(long long a, long long b) {
	long long ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return ans;
}

long long fac[1010], inv[1010];

long long Binom(long long n, long long k) {
	if (k < 0 || k > n) return 0;
	if (n - k < k) k = n - k;
	long long ans = inv[k]; for (int i = 1; i <= k; i++) ans = (n - i + 1) % mod * ans % mod;
	return ans;
}

namespace PolyOp {
	void NTT(int *f, int N, int flag) {
		static const int G = 3;
		static int num[1 << 11], lstN;
		static long long W[1 << 11 | 1], invN;
		if (lstN != N) {
			lstN = N, invN = power(N, mod - 2);
			; for (int i = 0; i < N; i++) num[i] = num[i >> 1] >> 1 | (i & 1 ? N >> 1 : 0);
			W[0] = 1, W[1] = power(G, (mod - 1) / N); for (int i = 2; i <= N; i++) W[i] = W[i - 1] * W[1] % mod;
		}
		; for (int i = 0; i < N; i++) if (i < num[i]) swap(f[i], f[num[i]]);
		for (int len = 2; len <= N; len <<= 1) {
			for (int i = 0; i < N; i += len) {
				int *fl = f + i, *fr = fl + len / 2, step = flag ? -N / len : N / len;
				long long *w = flag ? W + N : W;
				for (int j = 0; j < len / 2; j++) {
					int tmp = *fr * *w % mod;
					SUB(*fr = *fl, tmp), ADD(*fl, tmp);
					fl++, fr++, w += step;
				}
			}
		}
		if (flag) for (int i = 0; i < N; i++) f[i] = f[i] * invN % mod;
	}
	void polymul(int *f, int n, int *g, int m, int *h) {
		int N = 1; while (N < n + m - 1) N <<= 1;
		static int t1[1 << 11], t2[1 << 11]; for (int i = 0; i < N; i++) t1[i] = i < n ? f[i] : 0, t2[i] = i < m ? g[i] : 0;
		NTT(t1, N, 0), NTT(t2, N, 0);
		; for (int i = 0; i < N; i++) t1[i] = 1ll * t1[i] * t2[i] % mod;
		NTT(t1, N, 1);
		; for (int i = 0; i < n + m - 1; i++) h[i] = t1[i];
	}
}

int A, B;
long long N;
int D, M, K;
pll a[60];
int F[1010][1010];
int G[70][1010];
int H[70][1010];



void ciradd(int *f, int *g, int *h) {
	static int tmp[1010]; for (int i = 0; i < D; i++) ADD(tmp[i] = f[i], g[i]);
	memcpy(h, tmp, D << 2);
}

void cirmul(int *f, int *g, int *h) {
	static int tmp[2010]; PolyOp :: polymul(f, D, g, D, tmp);
	memset(h, 0, D << 2); for (int i = 0; i < D + D - 1; i++) ADD(h[i % D], tmp[i]);
}

void Calc(long long lim, int *g, int *h) {
	memset(g, 0, D << 2), memset(h, 0, D << 2), g[0] = 1;
	int it = 0;
	while (lim) {
		if (lim & 1) {
			cirmul(g, G[it], g);
			cirmul(h, G[it], h);
			ciradd(h, H[it], h);
		}
		lim >>= 1, it++;
	}
}

int Solve(long long x, long long y) {
	long long lim = N - x - y + 1; 
	int rem = (x + y) % D;
	rem = (D - rem) % D;
	lim -= rem;
	lim = (lim + D - 1) / D;
	x %= D, y %= D;
	
	static int g[1010], h[1010];
	Calc(lim, g, h);
	cirmul(h, F[rem], h);
	int ans = h[(D - x) % D];
	return ans;
}

int main() {
	fac[0] = 1; for (int i = 1; i <= 1005; i++) fac[i] = fac[i - 1] * i % mod;
	inv[1005] = power(fac[1005], mod - 2); for (int i = 1004; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
	scanf("%d%d", &A, &B);
	scanf("%lld%d%d%d", &N, &D, &M, &K);
	a[0] = mp(0, 0); for (int i = 1; i <= K; i++) scanf("%lld%lld", &a[i].fi, &a[i].se);
	{ 
		F[0][0] = 1;
		for (int i = 0; i < D; i++) {
			for (int j = 0; j < D; j++) {
				ADD(F[i + 1][j], 1ll * F[i][j] * A % mod);
				ADD(F[i + 1][(j + 1) % D], 1ll * F[i][j] * B % mod);
			}
		}
		memcpy(G[0], F[D], D << 2), H[0][0] = 1;
		for (int i = 1; i < 66; i++) {
			cirmul(G[i - 1], G[i - 1], G[i]);
			cirmul(H[i - 1], G[i - 1], H[i]);
			ciradd(H[i], H[i - 1], H[i]);
		}
	}
	int ans = 0;
	{
		static int coef[60];
		sort(a, a + K + 1);
		for (int i = 0; i <= K; i++) {
			coef[i] = Binom(a[i].fi + a[i].se, a[i].fi);
			for (int j = 1; j < i; j++) if (a[j].fi <= a[i].fi && a[j].se <= a[i].se) {
				SUB(coef[i], 1ll * coef[j] * Binom(a[i].fi + a[i].se - a[j].fi - a[j].se, a[i].fi - a[j].fi) % mod);
			}
		}
		; for (int i = 0; i <= K; i++) coef[i] = 1ll * coef[i] * power(B, a[i].fi) % mod * power(A, a[i].se) % mod;
		; for (int i = 0; i <= K; i++) (i == 0 ? ADD : SUB)(ans, 1ll * Solve(a[i].fi, a[i].se) * coef[i] % mod);
	}
	printf("%d\n", ans);
	return 0;
}