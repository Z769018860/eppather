#include<bits/stdc++.h>

using namespace std;

using u64 = unsigned long long;
using Poly = std::vector<int>;

constexpr int N = 1 << 18;

constexpr int mod = 998244353, _g = 3;

constexpr int dilate(int x){return x >> 31 ? x + mod : x;}
constexpr int mul(int x, int y){return u64(x) * y % mod;}
constexpr int qpow(int a, int b, int r = 1){for(; b; b >>= 1, a = mul(a, a)){if(b & 1){r = mul(r, a);}}return r;}
constexpr int bceil(int x){return 2 << std::__lg(x - 1);}
namespace f_n_t_t{
	constexpr int mp2 = __builtin_ctz(mod - 1), G = qpow(_g, (mod - 1) >> mp2), GI = qpow(G, mod - 2);
	void init_(int* w, int l, int g){
		int t = std::__lg(l - 1); l = 1 << t, w[0] = 1;
        for(int i = 0; i < t; ++i){w[1 << i] = qpow(g, 1 << (mp2 - 2 - i));}
		for(int i = 1; i < l; ++i){w[i] = mul(w[i & (i - 1)], w[i & -i]);}
	}
	int w[N], wI[N];
	void init(int l){init_(w, l, G), init_(wI, l, GI);}
	void dif(int *f, int lim){
		for(int l = lim >> 1, r = lim; l; l >>= 1, r >>= 1){
			for(int *j = f, *o = w; j != f + lim; j += r, ++o){
				for(int* k = j; k != j + l; ++k){
					int x = dilate(*k - mod), y = mul(*o, k[l]);
					k[l] = x - y + mod, *k = x + y;
				}
			}
		}
	}
	void dit(int *f, int lim){
		for(int l = 1, r = 2; l < lim; l <<= 1, r <<= 1){
			for(int *j = f, *o = wI; j != f + lim; j += r, ++o){
				for(int* k = j; k != j + l; ++k){
					int x = *k, y = mod - k[l];
					*k = dilate(x - y), k[l] = mul(x + y, *o);
				}
			}
		}
	}
}

int A[N << 1], B[N << 1];
int mfac[N << 1], mifac[N << 1];
Poly Larg(const Poly &f, int m){
	int n = f.size(), d = n - 1, l = n + d, lim = bceil(n << 1);
	f_n_t_t::init(lim);
	{
		int *ifac = A + n;
		ifac[0] = 1;
		for(int i = 1; i < n; ++i){ifac[i] = mul(ifac[i - 1], i);}
		ifac[d] = qpow(ifac[d], mod - 2);
		for(int i = d; i; --i){ifac[i - 1] = mul(ifac[i], i);}
		for(int i = 0; i < n; ++i){
			A[i] = mul(f[i], ((n - i) & 1) ? (mul(ifac[i], ifac[d - i])) : (mod - mul(ifac[i], ifac[d - i])));
		}
		std::fill(A + n, A + lim, 0);
	}
	{
		mfac[0] = 1;
		for(int i = 1; i <= l; ++i){mfac[i] = mul(mfac[i - 1], i + (m - n));}
		mifac[l] = qpow(mfac[l], mod - 2);
		for(int i = l; i; --i){
        	mifac[i - 1] = mul(mifac[i], i + (m - n)), B[i - 1] = mul(mfac[i - 1], mifac[i]);
    	}
		std::fill(B + l, B + lim, 0);
	}
	f_n_t_t::dif(A, lim), f_n_t_t::dif(B, lim);
	for(int i = 0; i < lim; ++i){A[i] = mul(A[i], B[i]);}
	f_n_t_t::dit(A, lim);
	for(int i = d, iv = (mod - ((mod - 1) / lim)); i < l; ++i){
		A[i] = mul(mul(mfac[i + 1], mifac[i - d]), mul(A[i], iv));
	}
	return Poly(A + d, A + l);
}

void solve(){
	int n, m;
	std::cin >> n >> m;
	Poly F(n + 1);
	for(auto &x : F){
		std::cin >> x;
	}
	for(auto x : Larg(F, m)){
		std::cout << x << ' ';
	}
}

int main(){
	ios::sync_with_stdio(false), cin.tie(nullptr);
	solve();
	return 0;
}