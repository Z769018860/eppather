#include<bits/stdc++.h>
using u64 = unsigned long long;
int mod;
int mul(int x, int y){
    return u64(x) * y % mod;
}
int dilate(int x){
    return x >> 31 ? x + mod : x;
}
int qpow(int a, int b, int r = 1){
    for(; b; b >>= 1, a = mul(a, a)){
        if(b & 1){
            r = mul(r, a);
        }
    }
    return r;
}
using f64 = double;
using cpx = std::complex<f64>;
using Poly = std::vector<int>;



constexpr int N = 1 << 18;
constexpr int bceil(int x){return 2 << std::__lg(x - 1);}

namespace f_f_t{
const f64 Pi_2 = acos(-1.0) / 2;
cpx w[N >> 1];
int init_l = 0;
void init(int l){
    if(l > init_l){
        int t = std::__lg(l - 1); l = 1 << t, *w = cpx(1.0, 0.0), init_l = l << 1;
        for(int i = 1; i < l; i <<= 1){w[i] = std::polar(1.0, Pi_2 / i);}
        for(int i = 1; i < l; ++i){w[i] = w[i & (i - 1)] * w[i & -i];}
    }
}
void dif(cpx *f, int L){
    for(int l = L >> 1, r = L; l; l >>= 1, r >>= 1){
		for(cpx *j = f, *o = w; j != f + L; j += r, ++o){
			for(cpx *k = j; k != j + l; ++k){
	    		cpx x = *k, y = k[l] * *o;
				*k = x + y, k[l] = x - y;
			}
		}
	}    
}
void dit(cpx *f, int L){
	for(int l = 1, r = 2; l < L; l <<= 1, r <<= 1){
		for(cpx *j = f, *o = w; j != f + L; j += r, ++o){
			for(cpx *k = j; k != j + l; ++k){
				cpx x = *k, y = k[l];
				*k = x + y, k[l] = (x - y) * std::conj(*o);
			}
		}
	}
}
}

namespace MTT{
void prep(const Poly &a, cpx *f, int l){
    int n = a.size();
    for(int i = 0; i < n; ++i){f[i] = cpx(a[i] >> 15, a[i] & 32767);}
    std::fill(f + n, f + l, 0), f_f_t::dif(f, l);
}
cpx f0[N], f1[N];
Poly Conv(const Poly &a, const Poly &b){
    int n = a.size(), m = b.size(), u = n + m - 1, l = bceil(u);
    prep(a, f0, l), prep(b, f1, l);
    f64 fx = 0.5 / l;
    for(int i = 0; i < std::min<int>(2, l); ++i){
        cpx p = f0[i], r = f1[i] * fx;
        f0[i] = (p + std::conj(p)) * r, f1[i] = (std::conj(p) - p) * r;
    }
    for (int k = 2, m = 3; k < l; k <<= 1, m <<= 1){
        for (int i = k, j = (k << 1) - 1; i < m; ++i, --j){
            cpx p = f0[i], q = f0[j], r = f1[i] * fx, s = f1[j] * fx;
            f0[i] = (p + std::conj(q)) * r, f1[i] = (std::conj(q) - p) * r;
            f0[j] = (q + std::conj(p)) * s, f1[j] = (std::conj(p) - q) * s;
        }
    }
    f_f_t::dit(f0, l), f_f_t::dit(f1, l);
    Poly c(u);
    for(int i = 0; i < u; ++i){
        c[i] = (((u64(f0[i].real() + 0.5) % mod) << 30) + (u64((f0[i].imag() - f1[i].imag()) + 0.5) << 15) + u64(f1[i].real() + 0.5)) % mod;
    }
    return c;
}
}

Poly calc(auto bg, auto ed){
    int len = ed - bg;
    if(len == 1){
        return *bg;
    }
    return MTT::Conv(calc(bg, bg + (len >> 1)), calc(bg + (len >> 1), ed));
}

int f[100005], sum[100005], A[100005];
void solve(){
    int k;
    std::cin >> k, mod = k;
	if(k == 1){
		std::cout << "-1\n";
		return ;
	}
    f_f_t::init(k + 1);
    std::vector<Poly> all;  
    for(int i = 0; i < k; ++i){
        all.push_back({i, 1});
    }
    auto res = calc(all.begin(), all.end());
	std::cout << res.size() - 1 << '\n';
	for(auto x : res){
		std::cout << x << ' ';
	}
}  
int main(){
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    solve();
    return 0;
}