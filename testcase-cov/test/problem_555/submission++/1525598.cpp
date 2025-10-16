#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define per(i, r, l) for(int i = (r); i >= (l); i--)
#define mem(a, b) memset(a, b, sizeof a)
#define For(i, l, r) for(int i = (l), i##e = (r); i < i##e; i++)
#define pb push_back
#define eb emplace_back

using namespace std;
using ll = long long;

const int N = 2048, P = 998244353;

ll n, A, B;
int d, m, K, f[55];
int a[N], b[N], fac[N], ifac[N];
pair<int, ll> c[55];
int lim, sw[N], isw[N], F[60][2][N];

inline int add(int a, int b) { return (a += b) < P ? a : a - P; }
inline int sub(int a, int b) { return (a -= b) < 0 ? a + P : a; }
inline void inc(int& a, int b) { if((a += b) >= P) a -= P; }
ll Pow(ll a, ll n, ll r = 1) {
	for(; n; n >>= 1, a = a * a % P)
	if(n & 1) r = r * a % P;
	return r;
}
void prework() {
	ll es[22], ies[22], w[22], iw[22];
	ll e = 15311432, ie = 469870224;
	for(int i = 21; i >= 0; i--)
		es[i] = e, ies[i] = ie, e = e * e % P, ie = ie * ie % P;
	ll now = 1, inow = 1;
	for(int i = 0; i <= 21; i++) {
		w[i] = es[i] * now % P, iw[i] = ies[i] * inow % P;
		(now *= ies[i]) %= P, (inow *= es[i]) %= P;
	}
	sw[0] = isw[0] = 1;
	rep(i, 0, (lim >> 1) - 2) {
		sw[i + 1] = (ll)sw[i] * w[__builtin_ctz(~i)] % P;
		isw[i + 1] = (ll)isw[i] * iw[__builtin_ctz(~i)] % P;
	}
}
void DIF(int a[]) {
	for(int i = lim >> 1, l = 1; i; i >>= 1, l <<= 1)
		for(int j = 0; j < l; j++) {
			ll now = sw[j];
			int pos = j * i * 2;
			for(int k = pos; k < pos + i; k++) {
				int x = a[k], y = a[k + i] * now % P;
				a[k] = add(x, y), a[k + i] = sub(x, y);
			}
		}
}
void IDIF(int a[]) {
	for(int i = 1, l = lim >> 1; l; i <<= 1, l >>= 1)
		for(int j = 0; j < l; j++) {
			ll now = isw[j];
			int pos = j * i * 2;
			for(int k = pos; k < pos + i; k++) {
				int x = a[k], y = a[k + i];
				a[k] = add(x, y), a[k + i] = (x - y + P) * now % P;
			}
		}
	ll inv = Pow(lim, P - 2);
	For(i, 0, lim) a[i] = a[i] * inv % P;
}
ll Cll(int n, ll m) {
	ll res = a[n] * Pow(B, m) % P * ifac[n] % P;
	m %= P;
	rep(i, 1, n) res = res * (m + i) % P;
	return res;
}
int C(int n, int m) {
	return ((ll)fac[n] * ifac[m] % P * ifac[n - m] % P) * ((ll)a[m] * b[n - m] % P) % P;
}
ll calc(ll x, ll y) {
	ll cx = (x + d - 1) / d * d, cy = (y + d - 1) / d * d;
	x = cx - x, y = cy - y + x;
	ll n = ::n - cx - cy;
	if(n < 0) return 0;
	n = n / d + 1;
	static int a[2048], b[2048];
	memset(a, 0, lim << 2), memset(b, 0, lim << 2);
	rep(i, 0, y) inc(a[i < d ? i : i - d], C(y, i));
	DIF(a);
	rep(k, 0, 59) if(n >> k & 1) {
		For(i, 0, lim) {
			b[i] = (b[i] + (ll)a[i] * F[k][1][i]) % P;
			a[i] = (ll)a[i] * F[k][0][i] % P;
		}
		IDIF(a);
		For(i, d, d << 1) inc(a[i - d], a[i]), a[i] = 0;
		DIF(a);
	}
	IDIF(b);
	return add(b[x], b[x + d]);
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> B >> A;
	cin >> n >> d >> m >> K, m = max(m, d << 1);
	rep(i, 1, K) cin >> c[i].first >> c[i].second;
	sort(c + 1, c + K + 1);
	fac[0] = a[0] = b[0] = 1;
	rep(i, 1, m) {
		fac[i] = (ll)fac[i - 1] * i % P;
		a[i] = (ll)a[i - 1] * A % P;
		b[i] = (ll)b[i - 1] * B % P;
	}
	ifac[m] = Pow(fac[m], P - 2);
	per(i, m, 1) ifac[i - 1] = (ll)ifac[i] * i % P;
	for(lim = 1; lim < d << 1; lim <<= 1);
	prework();
	For(i, 0, d) F[0][0][i] = C(d, i);
	inc(F[0][0][0], C(d, d));
	DIF(F[0][0]);
	For(i, 0, lim) F[0][1][i] = 1;
	For(k, 0, __lg(n / d + 1)) {
		auto src = F[k], dst = F[k + 1];
		For(i, 0, lim) {
			dst[0][i] = (ll)src[0][i] * src[0][i] % P;
			dst[1][i] = (1LL + src[0][i]) * src[1][i] % P;
		}
		IDIF(dst[0]), IDIF(dst[1]);
		For(i, d, d << 1) {
			inc(dst[0][i - d], dst[0][i]), dst[0][i] = 0;
			inc(dst[1][i - d], dst[1][i]), dst[1][i] = 0;
		}
		DIF(dst[0]), DIF(dst[1]);
	}
	ll ans = calc(0, 0);
	rep(i, 1, K) {
		int x = c[i].first; ll y = c[i].second;
		f[i] = Cll(x, y);
		rep(j, 1, i - 1) {
			int x2 = c[j].first; ll y2 = c[j].second;
			if(y2 <= y) f[i] = (f[i] + (P - f[j]) * Cll(x - x2, y - y2)) % P;
		}
		(ans += (P - f[i]) * calc(x, y)) %= P;
	}
	cout << ans;
}