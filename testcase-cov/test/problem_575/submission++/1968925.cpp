#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long; 

const int N = (1 << 17), P = 998244353;

namespace ModInt {
	inline int add(int x, int y) {return x + y >= P ? x + y - P : x + y;}
	inline int sub(int x, int y) {return x < y ? x - y + P : x - y;}
	inline int mul(int x, int y) {return 1ll * x * y % P;}
	inline int Pow(int x, int y) {int r = 1; for (; y; y >>= 1, x = mul(x, x)) if (y & 1) r = mul(r, x); return r;}
	inline int inv(int x) { return Pow(x, P - 2);}
}
using namespace ModInt;

namespace POLY {
	using Poly = vector<int>;
	int r[N], len;
	void Init(int n) {
		len = 1; while (len < n) len <<= 1;
		for (int i = 1; i < len; ++i) {
			r[i] = r[i >> 1] >> 1; 
			if (i & 1) r[i] |= (len >> 1);
		}
	}
	int G[17][N];
	void Prework() {
		for (int i = 0; i < 17; ++i) {
			int *Gi = G[i]; Gi[0] = 1;
			const int t = Pow(3, P >> i + 1);
			for (int j = 1; j < (1 << i); ++j) Gi[j] = mul(Gi[j - 1], t);
		}		
	}
	void Dft(Poly &a, int type = 1, int n = len) {
		for (int i = 0; i < n; ++i) if (i < r[i]) swap(a[i], a[r[i]]);
		for (int i = 1, o = 0; i < n; i <<= 1, ++o) {
			const int *Go = G[o];
			for (int j = 0; j < n; j += (i << 1)) {
				for (int k = 0; k < i; ++k) {
					int tx = a[j + k], ty = mul(Go[k], a[i + j + k]);
	                a[j + k] = add(tx, ty), a[i + j + k] = sub(tx, ty);
				}
			}
		}
		if (type == -1) {
			reverse(a.begin() + 1, a.end());
			const int t = inv(n);
			for (int i = 0; i < n; ++i) a[i] = mul(a[i], t);
		}
	}
};
using namespace POLY;

int n;
string s;

int phi[N], g[N];
int f[N];

ull tmp[N >> 3];
int x[16][N >> 3], y[16][N >> 3];
void solve(int l, int r) {
	if (r - l + 1 <= 128) {
		for (int i = l; i <= r; ++i) {
			__int128 t = 0;
			for (int j = l; j < i; ++j) t += 1ll * f[j] * g[i - j];
			f[i] = phi[i] * (f[i] + t) % P;
		}
		return;
	}
	
	int B = 1;
	while ((B << 4) < r - l + 1) B <<= 1;
	int c = (r - l) / B + 1;
	Init(B << 1);
	
	vector<Poly> x(c), y(c);
	for (int i = l, id = 0; i <= r; i += B, ++id) {
		for (int j = 0; j < len; ++j) tmp[j] = 0;
		for (int j = 0; j < id; ++j) {
			for (int k = 0; k < len; ++k) {
				tmp[k] += 1ll * x[j][k] * y[id - j - 1][k];
			}
		}
		x[id].resize(len);
		for (int j = 0; j < len; ++j) x[id][j] = tmp[j] % P;
		Dft(x[id], -1);
		for (int j = 0; j < B && i + j <= r; ++j) f[i + j] = add(f[i + j], x[id][j + B]);
		solve(i, min(i + B - 1, r));
		if (i + B <= r) {
			Init(B << 1); y[id].resize(len);
			for (int j = 0; j < len; ++j) x[id][j] = 0; 
			for (int j = 0; j < B; ++j) x[id][j] = f[i + j];
			for (int j = 0; j < (B << 1); ++j) y[id][j] = g[id * B + j];
			Dft(x[id]), Dft(y[id]);
		}
	}
}

int fac[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s;
	n = s.size();
	
	fac[0] = 1;
	for (int i = 1; i <= n + 1; ++i) fac[i] = mul(fac[i - 1], i);
	g[n + 1] = inv(fac[n + 1]);
	for (int i = n + 1; i; --i) g[i - 1] = mul(g[i], i);
	
	phi[0] = 1;
	for (int i = 1; i <= n; ++i) {
		if (s[i - 1] == '<') phi[i] = 0;
		else phi[i] = P - 1;
	}
	
	Prework();
	f[0] = 1, solve(0, n);
	
	__int128 t = 0;
	for (int i = 0; i <= n; ++i) t += 1ll * f[i] * g[n + 1 - i];
	
	int ans = t % P;
	for (int i = 0; i < n; ++i) if (s[i] == '>') ans = P - ans;
	cout << mul(ans, fac[n + 1]) << '\n';
	
	return 0;
}