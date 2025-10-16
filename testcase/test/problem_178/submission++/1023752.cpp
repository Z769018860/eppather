
#include <bits/stdc++.h>
typedef long long ll;
const int N = 254;
typedef int vec[N], *pvec;
typedef const int *cpvec;
int n, mod;
int ans = 0, root[N];
vec a, f, g, r;
std::mt19937 gen;									
vec Rand, Pow, G, _1;

inline int &reduce(int &x) {
    return x += (x >> 31 & mod);
}
inline int &neg(int &x) {
    return x = (!x - 1) & (mod - x);
}
ll PowerMod(ll a, int n, ll c = 1) {
    for (; n; n >>= 1, a = a * a % mod)
        if (n & 1)
            c = c * a % mod;
    return c;
}
namespace Poly {
	vec B1, B2, B3, B4, B5;
	int canonicity(int n, pvec a) {
	    for (; ~n && !a[n]; --n);
	    ll iv = PowerMod(a[n], mod - 2);
	    for (int i = 0; i <= n; ++i)
	        a[i] = a[i] * iv % mod;
	    return n;
	}
	void Mul(int A, cpvec a, int B, cpvec b, pvec ret) {
	    int i, j;
	    memset(B1, 0, (A + B + 1) << 2);
	    for (i = 0; i <= A; ++i)
	        for (j = 0; j <= B; ++j)
	            B1[i + j] = (B1[i + j] + (ll)a[i] * b[j]) % mod;
	    memcpy(ret, B1, (A + B + 1) << 2);
	}
	void DivMod(int A, cpvec a, int B, cpvec b, pvec q, pvec r) {
	    int i, j;
	    ll t;
	    assert(b[B] == 1);
	    memcpy(B1, a, (A + 1) << 2);
	    for (i = A; i >= B; --i)
	        for (t = mod - B1[i], j = 1; j <= B; ++j)
	            B1[i - j] = (B1[i - j] + t * b[B - j]) % mod;
	    memcpy(q, B1 + B, (A - B + 1) << 2), memcpy(r, B1, B << 2);
	}
	int GCD(int A, cpvec a, int B, cpvec b, pvec ret) {
	    memcpy(B4, a, (A + 1) << 2), memcpy(B5, b, (B + 1) << 2);
	    for (pvec _a = B4, _b = B5; ;) {
	        A = Poly::canonicity(A, _a);
	        B = Poly::canonicity(B, _b);
	        if (A < B)
	            std::swap(A, B), std::swap(_a, _b);
	        if (!~B)
	            return memcpy(ret, _a, (A + 1) << 2), A;
	        DivMod(A, _a, B, _b, B2, B3);
	        A = B - 1, memcpy(_a, B3, (A + 1) << 2);
	    }
	}
	void PowerMod(int deg, cpvec a, int n, cpvec m, pvec ret) {
	    memcpy(B4, a, deg << 2), memset(ret, 0, deg << 2), *ret = 1;
	    for (; n; n >>= 1) {
	        if (n & 1) {
	            Mul(deg - 1, B4, deg - 1, ret, ret);
	            DivMod(2 * deg - 2, ret, deg, m, B2, B3);
	            memcpy(ret, B3, deg << 2);
	        }
	        Mul(deg - 1, B4, deg - 1, B4, B4);
	        DivMod(2 * deg - 2, B4, deg, m, B2, B3);
	        memcpy(B4, B3, deg << 2);
	    }
	}
}
void ed_clash(int n, cpvec a) {
    int i, K;
    for (; n && !a[n]; --n);
    if (!n)
        return;
    if (n == 1) {
        neg(root[ans++] = *a);
        return;
    }
    for (; ;) {
        for (i = 0; i < n; ++i)
            Rand[i] = gen() % mod;
        Poly::PowerMod(n, Rand, mod / 2, a, Pow), reduce(--*Pow);
        K = Poly::GCD(n, a, n - 1, Pow, G);
        if (K && K != n) {
            int P1[K + 1], P2[n - K + 1];
            memcpy(P1, G, (K + 1) << 2);
            Poly::DivMod(n, a, K, G, P2, _1);
            return ed_clash(K, P1), ed_clash(n - K, P2);
        }
    }
}
int main() {
    int i, size;
    char *_ = new char;
    gen.seed(time(NULL) + (unsigned long)_), delete _;
    scanf("%d%d", &n, &mod);
    for (i = 0; i <= n; ++i)
        scanf("%d", a + i);
    Poly::canonicity(n, a);							
    if (!*a) {
        for (root[ans++] = i = 0; i <= n && !a[i]; ++i);
        std::copy(a + i, a + (n + 1), a);
        if (!~(n -= i))
            return puts("1\n0"), 0;
    }
    f[1] = 1, Poly::PowerMod(n, f, mod, a, g), reduce(--g[1]);
    if (size = Poly::GCD(n, a, n - 1, g, r))
        ed_clash(size, r);
    std::sort(root, root + ans);
    printf("%d\n", ans);
    for (i = 0; i < ans; ++i)
        printf("%d%c", root[i], i == ans - 1 ? 10 : 32);
    return 0;
}