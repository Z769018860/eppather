#include <bits/stdc++.h>
using namespace std;






template <class T> int sz(T&& a) { return int(size(forward<T>(a))); }

template <class T> using vc = vector<T>;
template <class T> using vvc = vc<vc<T>>;

using ll = int64_t;
using vi = vc<int>;
using pii = pair<int, int>;
using uint = uint32_t;
using ull = uint64_t;

mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());

template <class S, class M> M scary_prod(S n, S a, S b, S m, M e, M x, M y) { 
	assert(n >= 0); assert(a >= 0); assert(b >= 0); assert(m >= 1); 

	S c = (a * n + b) / m; 
	M p = e, s = e;
	while (true) {
		S u = a / m, v = b / m;
		a %= m, b %= m;
		x = x * y.pow(u);
		p = p * y.pow(v);
		c -= u * n + v;
		if (c == 0) break;

		S d = (m * c - b - 1) / a + 1;
		s = y * x.pow(n - d) * s;
		b = m - b - 1 + a, n = c - 1, c = d;
		swap(a, m), swap(x, y);
	}
	return p * x.pow(n) * s; 
}

template <class T> T pow(T a, ll b) { 
	assert(b >= 0);
	T r = 1;
	while (b) {
		if (b & 1) r *= a;
		a *= a;
		b >>= 1;
	}
	return r;
} 

template <uint mod> struct mint {
	static constexpr uint m = mod; 
	const static mint g;
	uint v;
	mint() : v(0) {}
	mint(ll a) { s(uint(a % m + m)); }
	mint& s(uint a) { v = a < m ? a : a-m; return *this; }
	friend mint inv(const mint& n) { return pow(n, m-2); } 

	mint operator- () const { 
		mint res;
		res.v = v ? m-v : 0;
		return res;
	} 

	friend bool operator == (const mint& a, const mint& b) { return a.v == b.v; } 
	friend bool operator != (const mint& a, const mint& b) { return !(a == b); } 

	mint& operator += (const mint& o) { return s(v + o.v); } 
	mint& operator -= (const mint& o) { return s(v + m - o.v); }
	mint& operator *= (const mint& o) { v = uint(ull(v) * o.v % m); return *this; }
	mint& operator /= (const mint& o) { return *this *= inv(o); } 

	friend mint operator + (const mint& a, const mint& b) { return mint(a) += b; } 
	friend mint operator - (const mint& a, const mint& b) { return mint(a) -= b; }
	friend mint operator * (const mint& a, const mint& b) { return mint(a) *= b; }
	friend mint operator / (const mint& a, const mint& b) { return mint(a) /= b; } 
};

constexpr uint mod = int(1e9) + 7;
using num = mint<mod>;
template<> const num num::g = num(0);

const int MAXK = 11;
num choose[MAXK][MAXK];
void precomp() {
	for (int i = 0; i < MAXK; i++) {
		choose[i][0] = choose[i][i] = 1;
		for (int j = 1; j < i; j++) {
			choose[i][j] = choose[i-1][j-1] + choose[i-1][j];
		}
	}
}

int K1, K2;
struct data_t {
	ll dx{}, dy{};
	array<array<num, MAXK>, MAXK> sum = {};
	data_t() {}

	data_t operator * (const data_t& o) const {
		data_t res = *this;
		res.dx += o.dx;
		res.dy += o.dy;

		static array<array<num, MAXK>, MAXK> buf;
		for (int k1 = 0; k1 <= K1; k1++) {
			for (int k2 = 0; k2 <= K2; k2++) {
				num p = 1;
				num s = 0;
				
				for (int j = 0; j <= k1; j++) {
					s += choose[k1][j] * p * o.at(k1 - j, k2);
					p *= dx;
				}
				buf[k1][k2] = s;
			}
		}

		for (int k1 = 0; k1 <= K1; k1++) {
			for (int k2 = 0; k2 <= K2; k2++) {
				num p = 1;
				num s = 0;
				
				for (int j = 0; j <= k2; j++) {
					s += choose[k2][j] * p * buf[k1][k2 - j];
					p *= dy;
				}
				res.at(k1, k2) += s;
			}
		}

		return res;
	}

	data_t pow(ll e) const {
		assert(e >= 0);
		data_t r, a = *this;
		while (e) {
			if (e & 1) r = r * a;
			a = a * a;
			e >>= 1;
		}
		return r;
	}

	num& at(int k1, int k2) {
		return sum[k1][k2];
	}
	const num& at(int k1, int k2) const {
		return sum[k1][k2];
	}
};

int main() {
	ios_base::sync_with_stdio(false), cin.tie(nullptr);

	precomp();

	int T;
	cin >> T;
	while (T--) {
		ll N, A, B, M;
		cin >> N >> A >> B >> M;
		N++;
		cin >> K1 >> K2;

		data_t dx;
		dx.dx = 1;
		dx.at(0, 0) = 1;

		data_t dy;
		dy.dy = 1;

		cout << scary_prod(N, A, B, M, data_t(), dx, dy).at(K1, K2).v << '\n';
	}

	return 0;
}
