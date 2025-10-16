#include <bits/stdc++.h>
#define IL inline
#define LL long long
#define eb emplace_back
#define L(i, j, k) for (int i = (j); i <= (k); ++i)
#define R(i, j, k) for (int i = (j); i >= (k); --i)
using namespace std;

constexpr int mod = 998244353;
constexpr int G = 3;


using uLL = unsigned long long;

IL int ksm (int b, int k) {
	int r = 1;
	for (; k; k >>= 1, b = (uLL)b * b % mod) if (k & 1) r = (uLL)r * b % mod;
	return r;
}

template<class T>
IL T nor (const T &x) {
	return x + ((x >> 31) & mod);
}

template<class T>
IL void qm (T &x) {
	x += (x >> 31) & mod;
}


namespace internal {
	constexpr int N = 1 << 21;
	
	int pos[N], n, lg;
	
	void init (int z) {
		n = 1, lg = 0;
		while (n <= z) {
			n <<= 1;
			++lg;
		}
		L (i, 0, n - 1) {
			pos[i] = pos[i >> 1] >> 1 | ((i & 1) << (lg - 1));
		}
	}
	
	void NTT (int *a, bool o) {
		L (i, 0, n - 1) {
			if (i < pos[i]) {
				swap(a[i], a[pos[i]]);
			}
		}
		for (int l = 2; l <= n; l <<= 1) {
			int m = l >> 1;
			int wn = ksm(o ? G : (mod + 1) / G, (mod - 1) / l);
			for (int i = 0; i < n; i += l) {
				for (int j = 0, w = 1; j < m; j++, w = (uLL)w * wn % mod) {
					int t = (uLL)w * a[i + j + m] % mod;
					qm(a[i + j + m] = a[i + j] - t);
					qm(a[i + j] += t - mod);
				}
			}
		}
		if (o == 0) {
			int iv = mod - (mod - 1) / n;
			L (i, 0, n - 1) {
				a[i] = (uLL)a[i] * iv % mod;
			}
		}
	}
}

constexpr int N = 1e6 + 9;

int n, m, a[N], b[N];

int main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	++n, ++m;
	L (i, 0, n - 1) cin >> a[i];
	L (i, 0, m - 1) cin >> b[i];
	internal::init(n + m);
	internal::NTT(a, 1);
	internal::NTT(b, 1);
	L (i, 0, internal::n - 1) {
		a[i] = (uLL)a[i] * b[i] % mod;
	}
	internal::NTT(a, 0);
	L (i, 0, n + m - 2) {
		cout << a[i] << ' ';
	}
}
