#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const int P = 998244353;
template<class T>
inline T power(T a, i64 b) {
	T res = 1;
	for (; b; b >>= 1, a *= a)
		if (b & 1) res *= a;
	return res;
}

struct Z {
	int x;
	Z(int _x = 0) : x(_x) {}
	inline Z operator-() const {
		if (!x) return 0;
		return Z(P - x);
	}
	inline Z &operator+=(const Z &rhs) {
		x += rhs.x;
		if (x > P) x -= P;
		return *this;
	}
	inline Z &operator-=(const Z &rhs) {
		x -= rhs.x;
		if (x < 0) x += P;
		return *this;
	}
	inline Z &operator*=(const Z &rhs) {
		x = 1ull * x * rhs.x % P;
		return *this;
	}
	inline Z inv() const {
		return power(*this, P - 2);
	}
	inline Z &operator/=(const Z &rhs) {
		*this *= rhs.inv();
		return *this;
	}
	inline Z operator+(const Z &rhs) const {
		Z res = *this;
		return res += rhs;
	}
	inline Z operator-(const Z &rhs) const {
		Z res = *this;
		return res -= rhs;
	}
	inline Z operator*(const Z &rhs) const {
		Z res = *this;
		return res *= rhs;
	}
	inline Z operator/(const Z &rhs) const {
		Z res = *this;
		return res /= rhs;
	}
};

vector<int> rev;
vector<Z> roots{0, 1};
using poly = vector<Z>; 
void dft(poly &a) {
	int n = a.size();
	if (int(rev.size()) != n) {
		rev.resize(n);
		int k = __builtin_ctz(n) - 1;
		for (int i = 0; i < n; ++i) 
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k);
	}
	for (int i = 0; i < n; ++i)
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	if (int(roots.size()) < n) {
		int k = __builtin_ctz(roots.size());
		roots.resize(n);
		for (; (1 << k) < n; ++k) {
			Z e = power(Z(3), (P - 1) >> (k + 1));
			for (int i = 1 << (k - 1); i < (1 << k); ++i) {
				roots[i * 2] = roots[i];
				roots[i * 2 + 1] = roots[i] * e;
			}
		}
	}
	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += k * 2) {
			for (int j = 0; j < k; ++j) {
				Z x = a[i + j];
				Z y = a[i + j + k] * roots[k + j];
				a[i + j] = x + y;
				a[i + j + k] = x - y;
			}			
		}
	}
}
void idft(poly &a) {
	reverse(a.begin() + 1, a.end());
	dft(a);
	int n = a.size();
	Z inv = Z(n).inv();
	for (int i = 0; i < n; ++i)
		a[i] *= inv;
}
inline int extend(int len) {
	int n = 1;
	while (n < len) 
		n <<= 1;
	return n;
}
poly operator*(poly a, poly b) {
    int k = a.size();
    assert((int) b.size() == k);
    int len = 2 * k - 1;
	int n = extend(len);
	a.resize(n), dft(a);
	b.resize(n), dft(b);
	for (int i = 0; i < n; ++i)
		a[i] *= b[i];
	idft(a);
    for (int i = k; i < len; ++i) 
        a[i - k] += a[i]; 
    a.resize(k);
	return a;
}
void operator*=(poly &a, const poly &b) { 
    a = a * b;
}
poly polyPower(poly a, int b) {
    poly res(a.size(), 0);
    res[0] = 1;
    for (; b; b >>= 1, a *= a) 
        if (b & 1) res *= a;
    return res;
}

int main() {
    
    
    ios::sync_with_stdio(0), cin.tie(0);

    int a, b, d, m, k;
    i64 n;
    cin >> a >> b >> n >> d >> m >> k;

    vector<Z> fac(m + 1), ifac(m + 1);
	fac[0] = 1;
	for (int i = 1; i <= m; ++i)
		fac[i] = fac[i - 1] * i;
	ifac[m] = power(fac[m], P - 2);
	for (int i = m - 1; ~i; --i)
		ifac[i] = ifac[i + 1] * (i + 1);

    vector<pair<i64, i64>> p(k + 1);
    for (int i = 0; i < k; ++i) 
        cin >> p[i].first >> p[i].second;
    sort(p.begin(), p.end());

    poly f(d);
    f[0] = a, f[1 % d] += b;
    auto g = polyPower(f, d);

    auto solve = [&](i64 n, int x, int y) {
        y = (y + x) % d;
        if (n - y < 0) return Z(0);
        auto cur = polyPower(f, y);
        n = (n - y) / d;
        Z ans = cur[x];
        auto s0 = g, s1 = g;
        for (; n; n >>= 1) {
            if (n & 1) {
                ans += (cur * s1)[x];
                cur *= s0;
            }
            auto tmp = s0 * s1;
            for (int i = 0; i < d; ++i)
                s1[i] += tmp[i];
            s0 *= s0;
        }
        return ans;
    };
    
    Z ans = 0;
    vector<Z> dp(k + 1);
    dp[0] = 1;
    for (int i = 0; i <= k; ++i) {
        for (int j = i + 1; j <= k; ++j) {
            if (p[i].second > p[j].second) continue;
            i64 u = p[j].first - p[i].first + p[j].second - p[i].second;
            int v = p[j].first - p[i].first;
            auto coef = power(Z(a), u - v) * power(Z(b), v);
            coef *= ifac[v];
            for (int i = 0; i < v; ++i) 
                coef *= Z((u - i) % P);
            dp[j] -= dp[i] * coef;
        }
        i64 m = n - p[i].first - p[i].second;
        ans += dp[i] * solve(m, (d - p[i].first % d) % d, (d - p[i].second % d) % d);
    }
    cout << ans.x << "\n";

    return 0;
}