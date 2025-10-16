#include <bits/stdc++.h>
using namespace std;
#pragma comment(linker,"/stack:2147483647")
using ll = long long; 
using i8 = signed char;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
using i128 = __int128_t;
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = __uint128_t;

struct BasicBuffer {
    std::vector<char> s;
    BasicBuffer() : s(1 << 18) {}
    char *p = s.data(), *beg = p, *end = p + s.size();
    inline char getc() {
        if (p == end)
            readAll();

        return *p++;
    }
    inline void putc(char c) {
        if (p == end)
            writeAll();

        *p++ = c;
    }
    inline void puts(const char *x) {
        while (*x != 0)
            putc(*x++);
    }
    void readAll() {
        std::fread(beg, 1, end - beg, stdin);
        p = s.data();
    }
    void writeAll() {
        std::fwrite(beg, 1, p - beg, stdout);
        p = s.data();
    }
};

#define dbg(x) debug(__FILE__, __LINE__, #x, x)

void debug(const std::string &file, i32 line, const std::string &name, const auto &value) {
    std::cerr << file << ":" << line << " | " << name << " = " << value << std::endl;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "[ ";

    for (const T &vi : v) {
        os << vi << ", ";
    }

    return os << "]";
}

struct FastI : BasicBuffer {
    FastI() {
        readAll();
    }
    ll read() {
        ll x = 0;
        char c = getc();
        bool f = true;

        while (!std::isdigit(c))
            f = f && c != '-', c = getc();

        while (std::isdigit(c))
            x = (x << 3) + (x << 1) + c - '0', c = getc();

        return f ? x : -x;
    }
    template <class T>
    FastI &operator>>(T &x) {
        return x = read(), *this;
    }
    FastI &operator>>(char &x) {
        return x = getc(), *this;
    }
};

struct FastO : BasicBuffer {
    std::array<char, 32> u{};
    ~FastO() {
        writeAll();
    }
    void output(ll x) {
        char *i = u.data() + 20;

        if (x < 0)
            putc('-'), x = -x;

        do
            *--i = x % 10 + '0', x /= 10;

        while (x > 0);

        puts(i);
    }
    template <class T>
    FastO &operator<<(const T &x) {
        return output(x), *this;
    }
    FastO &operator<<(char x) {
        return putc(x), *this;
    }
    FastO &operator<<(const char *x) {
        return puts(x), *this;
    }
    FastO &operator<<(const std::string &x) {
        return puts(x.c_str()), *this;
    }
};

FastI fin;
FastO fout;

namespace __POLY__ {
namespace tdef {
typedef vector<i32>vi32;
typedef vector<u32>vu32;
typedef vector<i64>vi64;
typedef vector<u64>vu64;
} const int N = 3e6 + 10, mod = 998244353, gen = 3;
namespace math {
using namespace tdef;
template<typename T = int>inline T qpow(i64 x, int y, i64 ans = 1) {
    for (y < 0 ? y += mod - 1 : 0; y; y >>= 1, x = x * x % mod)
        y & 1 ? ans = ans * x % mod : 0;

    return ans;
} inline constexpr int lg(u32 x) {
    return x == 0 ? -1 : ((int)sizeof(int) * __CHAR_BIT__ - 1 - __builtin_clz(x));
} inline u32 fst_mul(u32 x, u64 p, u64 q) {
    return x * p - (q * x >> 32) * mod;
} const u32 modm2 = mod + mod;
namespace basic_math {
vu32 __fac({1, 1}), __ifc({1, 1}), __inv({0, 1});
inline void __prep(int n) {
    static int i = 2;

    if (i < n)
        for (__fac.resize(n), __ifc.resize(n), __inv.resize(n); i < n; i++)
            __fac[i] = 1ll * i * __fac[i - 1] % mod, __inv[i] = 1ll * (mod - mod / i) * __inv[mod % i] % mod,
                       __ifc[i] = 1ll * __inv[i] * __ifc[i - 1] % mod;
} inline u32 gfac(u32 x) {
    return __prep(x + 1), __fac[x];
} inline u32 gifc(u32 x) {
    return __prep(x + 1), __ifc[x];
} inline u32 ginv(u32 x) {
    return __prep(x + 1), __inv[x];
}
} namespace cipolla {
u32 I = 0;
struct cpl {
    u32 x, y;
    cpl(u32 _x = 0, u32 _y = 0): x(_x), y(_y) {} 
	inline cpl operator*(const cpl &a)const {
        return cpl((1ull * x * a.x + 1ull * I * y % mod * a.y) % mod, (1ull * x * a.y + 1ull * y * a.x) % mod);
    }
};
inline cpl cplpow(cpl a, int y, cpl b = cpl(1, 0)) {
    for (; y; y >>= 1, a = a * a)
        if (y & 1)
            b = b * a;

    return b;
} inline u32 isqrt(u32 x) {
    static mt19937 rnd(998244353);

    if (mod == 2 || !x || x == 1)
        return x;

    u32 a = 0;

    do {
        a = rnd() % mod;
    } while (qpow((1ull * a * a + mod - x) % mod, mod >> 1) != mod - 1);

    I = (1ll * a * a + mod - x) % mod;
    a = cplpow(cpl(a, 1), (mod + 1) >> 1).x;
    return min(a, mod - a);
} inline u32 cqrt(u32 x) {
	u32 l = 1, r = std::min(x, 1625u), mid;
	while (l < r) {
		mid = l + r + 1 >> 1;
		if (mid * mid * mid <= x) 
			l = mid;
		else
			r = mid - 1;
	}
	return l;
}
} 
using basic_math::gfac;
using basic_math::gifc;
using basic_math::ginv;
using cipolla::isqrt;
using cipolla::cqrt;
} namespace polynormial {
using namespace tdef;
const int maxbit = 23;
using math::lg;
using math::qpow;
using math::gfac;
using math::gifc;
using math::ginv;
namespace fast_number_theory_transform {
using math::modm2;
using math::fst_mul;
template<class T>inline void butterfly(T *p, int bit) {
    for (u32 i = 0, j = 0; i < (1u << bit); i++) {
        if (i > j)
            swap(p[i], p[j]);

        for (u32 l = 1u << (bit - 1); (j ^= l) < l; l >>= 1)
            ;
    }
} u32 *_p0[maxbit + 1], *_p1[maxbit + 1];
inline void prep(int bit) {
    static int k = 0;
    u64 g;

    for (u32 * p, *q, nl; k < bit; k++) {
        nl = 1 << k;
        g = qpow(3, mod >> (k + 1));
        p = _p0[k] = new u32[nl << 1];
        q = p + nl;

        for (int i = p[0] = 1; i < nl; i++)
            p[i] = p[i - 1] * g % mod;

        for (int i = 0; i < nl; i++)
            q[i] = (u64(p[i]) << 32) / mod;

        g = qpow(g, -1);
        p = _p1[k] = new u32[nl << 1];
        q = p + nl;

        for (int i = p[0] = 1; i < nl; i++)
            p[i] = p[i - 1] * g % mod;

        for (int i = 0; i < nl; i++)
            q[i] = (u64(p[i]) << 32) / mod;
    }
} template<class T>inline bool chkzero(const T *p, int bit) {
    int i = 0;

    for (; i + 16 < (1 << bit); i += 16) {
        if (p[i] | p[i ^ 1] | p[i ^ 2] | p[i ^ 3] | p[i ^ 4] | p[i ^ 5] | p[i ^ 6] | p[i ^ 7] | p[i ^ 8] | p[i ^ 9] |
                p[i ^ 10] | p[i ^ 11] | p[i ^ 12] | p[i ^ 13] | p[i ^ 14] | p[i ^ 15])
            return 0;
    }

    for (; i < (1 << bit); i++)
        if (p[i])
            return 0;

    return 1;
} void ntt(u32 *a, int bit, bool f = 0) {
    prep(bit);

    if (chkzero(a, bit))
        return;

    for (int k = bit; k-- > 0;) {
        u32 *_p = _p0[k], *_q = _p + (1 << k), *_a0 = a, *_a1 = a + (1 << k), x, y;

        for (int i = 0; i < 1 << (bit - k - 1); i++, _a0 += 2 << k, _a1 += 2 << k)
            for (int j = 0; j < (1 << k); ++j) {
                x = _a0[j], y = _a1[j];
                _a0[j] = x + y - (x + y >= modm2) * modm2, _a1[j] = fst_mul(x + modm2 - y, _p[j], _q[j]);
            }
    }

    for (int i = 0; i < (1 << bit); i++)
        a[i] -= (a[i] >= modm2) * modm2, a[i] -= (a[i] >= mod) * mod;

    if (f)
        butterfly(a, bit);
} void intt(u32 *a, int bit, bool f = 0) {
    prep(bit);

    if (chkzero(a, bit))
        return;

    if (f)
        butterfly(a, bit);

    for (int k = 0; k < bit; k++) {
        u32 *_p = _p1[k], *_q = _p + (1 << k), *_a0 = a, *_a1 = a + (1 << k), x, y;

        for (int i = 0; i < 1 << (bit - k - 1); i++, _a0 += 2 << k, _a1 += 2 << k)
            for (int j = 0; j < (1 << k); ++j) {
                x = _a0[j] - (_a0[j] >= modm2) * modm2, y = fst_mul(_a1[j], _p[j], _q[j]);
                _a0[j] = x + y, _a1[j] = x + modm2 - y;
            }
    }

    u64 iv = mod;
    iv <<= bit;
    iv = (iv - mod + 1) >> bit;

    for (int i = 0; i < (1 << bit); i++)
        a[i] = a[i] * iv % mod;
}
} using fast_number_theory_transform::ntt;
using fast_number_theory_transform::intt;
struct poly {
    vu32 f;
    poly(u32 x = 0): f(1) {
        f[0] = x;
    } poly(int x): f(1) {
        f[0] = x + ((x >> 31)&mod);
    } poly(const vu32 &_f): f(_f) {} poly(const vi32 &_f) {
        f.resize(f.size());

        for (int i = 0; i < _f.size(); i++) {
            f[i] = _f[i] + ((_f[i] >> 31)&mod);
        }
    } template<typename T>poly(initializer_list<T>_f): poly(vector<T>(_f)) {} template<typename T>poly(T __first,
            T __last): poly(vector<typename iterator_traits<T>::value_type>(__first,
                                __last)) {} inline operator vu32()const {
        return f;
    } inline void swap(poly &_f) {
        f.swap(_f.f);
    } inline int degree()const {
        return f.size() - 1;
    } inline poly &redegree(int x) {
        return f.resize(x + 1), *this;
    } inline void clear() {
        f.resize(1);
        f[0] = 0;
    } inline void shrink() {
        int ndeg = f.size() - 1;

        while (ndeg > 0 && f[ndeg] == 0)
            ndeg--;

        f.resize(ndeg + 1);
    } inline poly slice(int n)const {
        return n <= 0 ? poly(0) : (n < f.size() ? poly(f.begin(), f.begin() + n + 1) : poly(*this).redegree(n));
    } inline u32 &operator[](u32 x) {
        return f[x];
    } inline u32 operator[](u32 x)const {
        return f[x];
    } inline u32 get(u32 x)const {
        return x < f.size() ? f[x] : 0;
    } friend ostream &operator<<(ostream &out, const poly &x) {
        out << x.f[0];

        for (int i = 1; i < x.f.size(); i++)
            out << ' ' << x.f[i];

        return out;
    } inline u32 *data() {
        return f.data();
    } inline const u32 *data()const {
        return f.data();
    } inline poly &operator+=(const poly &a) {
        f.resize(max(f.size(), a.f.size()));

        for (int i = 0; i < a.f.size(); i++)
            f[i] = f[i] + a.f[i] - (f[i] + a.f[i] >= mod) * mod;

        return*this;
    } inline poly &operator-=(const poly &a) {
        f.resize(max(f.size(), a.f.size()));

        for (int i = 0; i < a.f.size(); i++)
            f[i] = f[i] - a.f[i] + (f[i] < a.f[i]) * mod;

        return*this;
    } inline poly operator+(const poly &a)const {
        return (poly(*this) += a);
    } inline poly operator-(const poly &a)const {
        return (poly(*this) -= a);
    } friend inline poly operator+(u32 a, const poly &b) {
        return (poly(b) += a);
    } friend inline poly operator-(u32 a, const poly &b) {
        return (poly(a) -= b);
    } inline poly operator-()const {
        poly _f;
        _f.f.resize(f.size());

        for (int i = 0; i < _f.f.size(); i++)
            _f.f[i] = (f[i] != 0) * mod - f[i];

        return _f;
    } inline poly &pluswith(const poly &a) {
        for (int i = 0, i_up = min(f.size(), a.f.size()); i < i_up; i++)
            f[i] = f[i] + a.f[i] - (f[i] + a.f[i] >= mod) * mod;

        return*this;
    } inline poly plus(const poly &a)const {
        return (poly(*this).pluswith(a));
    } inline poly &minuswith(const poly &a) {
        for (int i = 0, i_up = min(f.size(), a.f.size()); i < i_up; i++)
            f[i] = f[i] - a.f[i] + (f[i] < a.f[i]) * mod;

        return*this;
    } inline poly minus(const poly &a)const {
        return (poly(*this).minuswith(a));
    } inline poly &cornerwith(const poly &a) {
        memcpy(f.data(), a.f.data(), min(a.f.size(), f.size()) * 4);
        return*this;
    } inline poly corner(const poly &a)const {
        return poly(*this).cornerwith(a);
    } inline poly &operator*=(const poly &a) {
        int n = degree(), m = a.degree();

        if (n < 16 || m < 16) {
            f.resize(n + m + 1);

            for (int i = n + m; i >= 0; i--) {
                f[i] = 1ll * f[i] * a.f[0] % mod;

                for (int j = max(1, i - n), j_up = min(m, i); j <= j_up; j++)
                    f[i] = (f[i] + 1ll * f[i - j] * a.f[j]) % mod;
            }

            return*this;
        }

        vu32 _f(a.f);
        int bit = lg(n + m) + 1;
        f.resize(1 << bit);
        _f.resize(1 << bit);
        ntt(f.data(), bit);
        ntt(_f.data(), bit);

        for (int i = 0; i < (1 << bit); i++)
            f[i] = 1ll * f[i] * _f[i] % mod;

        intt(f.data(), bit);
        f.resize(n + m + 1);
        return*this;
    } inline poly operator*(const poly &a)const {
        return (poly(*this) *= a);
    } inline poly &multiplywith(const poly &_a) {
        poly a(_a);
        a.shrink();
        int n = degree(), m = a.degree();

        if (n < 16 || m < 16) {
            for (int i = n; i >= 0; i--) {
                f[i] = 1ll * f[i] * a.f[0] % mod;

                for (int j = max(1, i - n), j_up = min(m, i); j <= j_up; j++)
                    f[i] = (f[i] + 1ll * f[i - j] * a.f[j]) % mod;
            }

            return*this;
        }

        int bit = lg(n + m) + 1;
        f.resize(1 << bit);
        a.f.resize(1 << bit);
        ntt(f.data(), bit);
        ntt(a.f.data(), bit);

        for (int i = 0; i < (1 << bit); i++)
            f[i] = 1ll * f[i] * a.f[i] % mod;

        intt(f.data(), bit);
        f.resize(n + 1);
        return*this;
    } inline poly multiply(const poly &a)const {
        return (poly(*this).multiplywith(a));
    } inline poly &operator<<=(int x) {
        return f.resize(f.size() + x), memmove(f.data() + x, f.data(), 4 * (f.size() - x)), memset(f.data(), 0,
                4 * x), *this;
    } inline poly operator<<(int x)const {
        return (poly(*this) <<= x);
    } inline poly &operator>>=(int x) {
        return x >= f.size() ? (clear(), *this) : (memmove(f.data(), f.data() + x, 4 * (f.size() - x)),
                f.resize(f.size() - x), *this);
    } inline poly operator>>(int x)const {
        return (poly(*this) >>= x);
    } inline poly &shiftindexwith(int x) {
        return x >= f.size() ? (memset(f.data(), 0, 4 * f.size()), *this) : (memmove(f.data(), f.data() + x,
                4 * (f.size() - x)), memset(f.data(), 0, 4 * x), *this);
    } inline poly shiftindex(int x)const {
        return (poly(*this).shiftindexwith(x));
    } inline poly inv()const;
    inline poly quo(const poly &g)const;
    inline poly &quowith(const poly &g) {
        return f.size() == 1 ? (f[0] = qpow(g[0], -1, f[0]), *this) : (*this = quo(g));
    } inline poly deri()const {
        int n = degree();
        poly res;
        res.redegree(n - 1);

        for (int i = 1; i <= n; i++)
            res[i - 1] = 1ll * f[i] * i % mod;

        return res;
    } inline poly intg(u32 C = 0)const {
        int n = degree();
        poly res(C);
        res.redegree(n + 1);

        for (int i = 0; i <= n; i++)
            res[i + 1] = 1ll * ginv(i + 1) * f[i] % mod;

        return res;
    } inline poly ln()const;
    inline poly exp()const;
    inline poly pow(u32 x) {
        return (ln() * x).exp();
    } inline poly pow(u32 x, u32 x0) {
        return x0 != 0 ? ((multiply(qpow(f[0], -1)).ln()) * x).exp() * x0 : poly(0).redegree(degree());
    } inline poly ivsqrt()const {
        int nsize = f.size(), mxb = lg(f.size() - 1) + 1;
        vu32 a(1 << mxb), _f(f);
        _f.resize(1 << mxb);
        a[0] = qpow(math::isqrt(f[0]), mod - 2);

        for (int nb = 0; nb < mxb; nb++) {
            vu32 _a(a.begin(), a.begin() + (1 << nb)), _b(_f.begin(), _f.begin() + (2 << nb));
            _a.resize(4 << nb);
            _b.resize(4 << nb);
            ntt(_a.data(), nb + 2);
            ntt(_b.data(), nb + 2);

            for (int i = 0; i < (4 << nb); i++)
                _a[i] = 1ull * (mod - _a[i]) * _a[i] % mod * _a[i] % mod * _b[i] % mod,
                        _a[i] = (_a[i] + (_a[i] & 1) * mod) >> 1;

            intt(_a.data(), nb + 2);
            memcpy(a.data() + (1 << nb), _a.data() + (1 << nb), 4 << nb);
        }

        return a.resize(nsize), a;
    } inline poly sqrt()const {
        if (f.size() == 1)
            return poly(math::isqrt(f[0]));

        int nsize = f.size(), mxb = lg(nsize - 1) + 1;
        vu32 a(1 << mxb), _f(f), _b;
        _f.resize(1 << mxb);
        a[0] = qpow(math::isqrt(f[0]), mod - 2);

        for (int nb = 0; nb < mxb - 1; nb++) {
            vu32 _a(a.begin(), a.begin() + (1 << nb));
            _b = vu32(_f.begin(), _f.begin() + (2 << nb));
            _a.resize(4 << nb);
            _b.resize(4 << nb);
            ntt(_a.data(), nb + 2);
            ntt(_b.data(), nb + 2);

            for (int i = 0; i < (4 << nb); i++)
                _a[i] = 1ull * (mod - _a[i]) * _a[i] % mod * _a[i] % mod * _b[i] % mod,
                        _a[i] = (_a[i] + (_a[i] & 1) * mod) >> 1;

            intt(_a.data(), nb + 2);
            memcpy(a.data() + (1 << nb), _a.data() + (1 << nb), 4 << nb);
        }

        ntt(a.data(), mxb);
        vu32 _a(a);

        for (int i = 0; i < (1 << mxb); i++)
            a[i] = 1ll * a[i] * _b[i] % mod;

        intt(a.data(), mxb), memset(a.data() + (1 << (mxb - 1)), 0, 2 << mxb);
        vu32 g0(a);
        ntt(a.data(), mxb), ntt(_f.data(), mxb);

        for (int i = 0; i < (1 << mxb); i++)
            a[i] = (1ll * a[i] * a[i] + mod - _f[i]) % mod * (mod - _a[i]) % mod, a[i] = (a[i] + (a[i] & 1) * mod) >> 1;

        intt(a.data(), mxb);
        memcpy(g0.data() + (1 << (mxb - 1)), a.data() + (1 << (mxb - 1)), 2 << mxb);
        return g0;
    }
    inline poly cbrt() const{
		if (f.size() == 1)
			return math::cipolla::cqrt(f[0]);
	}
};
namespace __semiconvol__ {
const int logbr = 4, br = 1 << logbr, maxdep = (maxbit - 1) / logbr + 1, __bf = 7, bf = max(__bf, logbr - 1),
          pbf = 1 << bf;
} inline poly poly::ln()const {
    using namespace __semiconvol__;
    int nsize = f.size(), mxb = lg(nsize - 1) + 1;
    math::basic_math::__prep(mxb);
    vu32 res(1 << mxb), __prentt[maxdep][br], _f(f);

    for (int i = 0, k = mxb; k > bf; k -= logbr, i++) {
        for (int j = 0; j < br - 1; j++) {
            if ((j << (k - logbr)) >= nsize)
                break;

            __prentt[i][j].resize(2 << (k - logbr));
            int nl = (j << (k - logbr)), nr = min(((j + 2) << (k - logbr)), nsize) - nl;
            memcpy(__prentt[i][j].data(), _f.data() + nl, nr * 4);
            ntt(__prentt[i][j].data(), k - logbr + 1);
        }
    }

    function<void(int, int, int)>__div = [&res, &__prentt, &_f, &mxb, &__div](int x, int l, int r) {
        if (r - l <= pbf) {
            for (int i = l; i < r; i++) {
                if (i == 0)
                    res[i] = 0;
                else {
                    res[i] = (1ll * i * _f[i] + mod - res[i]) % mod;

                    if (i + 1 < r) {
                        u64 __tmp = res[i];

                        for (int j = i + 1; j < r; j++)
                            res[j] = (res[j] + __tmp * _f[j - i]) % mod;
                    }
                }
            }

            return;
        }

        int nbit = mxb - logbr * (x + 1), nbr = 0;
        vu32 __tmp[br];

        while (l + (nbr << nbit) < r) {
            __tmp[nbr].resize(2 << nbit);
            nbr++;
        }

        for (int i = 0; i < nbr; i++) {
            if (i != 0) {
                intt(__tmp[i].data(), nbit + 1);

                for (int j = 0; j < (1 << nbit); j++) {
                    u32 &x = res[l + (i << nbit) + j], &y = __tmp[i][j + (1 << nbit)];
                    x = x + y - (x + y >= mod) * mod, y = 0;
                }
            }

            __div(x + 1, l + (i << nbit), min(l + ((i + 1) << nbit), r));

            if (i != nbr - 1) {
                memcpy(__tmp[i].data(), res.data() + l + (i << nbit), 4 << nbit);
                ntt(__tmp[i].data(), nbit + 1);

                for (int j = i + 1; j < nbr; j++)
                    for (int k = 0; k < (2 << nbit); k++)
                        __tmp[j][k] = (__tmp[j][k] + 1ll * __tmp[i][k] * __prentt[x][j - i - 1][k]) % mod;
            }
        }
    };
    __div(0, 0, nsize);
    res.resize(nsize);

    for (int i = nsize - 1; i; i--)
        res[i] = 1ll * math::ginv(i) * res[i] % mod;

    return res;
} inline poly poly::exp()const {
    using namespace __semiconvol__;
    int nsize = f.size(), mxb = lg(nsize - 1) + 1;
    math::basic_math::__prep(mxb);
    vu32 res(1 << mxb), __prentt[maxdep][br], _f(f);

    for (int i = 0; i < nsize; i++)
        _f[i] = 1ll * i * _f[i] % mod;

    for (int i = 0, k = mxb; k > bf; k -= logbr, i++) {
        for (int j = 0; j < br - 1; j++) {
            if ((j << (k - logbr)) >= nsize)
                break;

            __prentt[i][j].resize(2 << (k - logbr));
            int nl = (j << (k - logbr)), nr = min(((j + 2) << (k - logbr)), nsize) - nl;
            memcpy(__prentt[i][j].data(), _f.data() + nl, nr * 4);
            ntt(__prentt[i][j].data(), k - logbr + 1);
        }
    }

    function<void(int, int, int)>__div = [&res, &__prentt, &_f, &mxb, &__div](int x, int l, int r) {
        if (r - l <= pbf) {
            for (int i = l; i < r; i++) {
                res[i] = i == 0 ? 1 : 1ll * math::ginv(i) * res[i] % mod;

                if (i + 1 < r) {
                    u64 __tmp = res[i];

                    for (int j = i + 1; j < r; j++)
                        res[j] = (res[j] + __tmp * _f[j - i]) % mod;
                }
            }

            return;
        }

        int nbit = mxb - logbr * (x + 1), nbr = 0;
        vu32 __tmp[br];

        while (l + (nbr << nbit) < r) {
            __tmp[nbr].resize(2 << nbit);
            nbr++;
        }

        for (int i = 0; i < nbr; i++) {
            if (i != 0) {
                intt(__tmp[i].data(), nbit + 1);

                for (int j = 0; j < (1 << nbit); j++) {
                    u32 &x = res[l + (i << nbit) + j], &y = __tmp[i][j + (1 << nbit)];
                    x = x + y - (x + y >= mod) * mod, y = 0;
                }
            }

            __div(x + 1, l + (i << nbit), min(l + ((i + 1) << nbit), r));

            if (i != nbr - 1) {
                memcpy(__tmp[i].data(), res.data() + l + (i << nbit), 4 << nbit);
                ntt(__tmp[i].data(), nbit + 1);

                for (int j = i + 1; j < nbr; j++)
                    for (int k = 0; k < (2 << nbit); k++)
                        __tmp[j][k] = (__tmp[j][k] + 1ll * __tmp[i][k] * __prentt[x][j - i - 1][k]) % mod;
            }
        }
    };
    __div(0, 0, nsize);
    return res.resize(nsize), res;
} inline poly poly::inv()const {
    using namespace __semiconvol__;
    int nsize = f.size(), mxb = lg(nsize - 1) + 1;
    vu32 res(1 << mxb), __prentt[maxdep][br], _f(f);
    u32 ivf0 = qpow(f[0], -1);
    _f[0] = 0;

    for (int i = 0, k = mxb; k > bf; k -= logbr, i++) {
        for (int j = 0; j < br - 1; j++) {
            if ((j << (k - logbr)) >= nsize)
                break;

            __prentt[i][j].resize(2 << (k - logbr));
            int nl = (j << (k - logbr)), nr = min(((j + 2) << (k - logbr)), nsize) - nl;
            memcpy(__prentt[i][j].data(), _f.data() + nl, nr * 4);
            ntt(__prentt[i][j].data(), k - logbr + 1);
        }
    }

    function<void(int, int, int)>__div = [&res, &__prentt, &_f, &mxb, &__div, &ivf0](int x, int l, int r) {
        if (r - l <= pbf) {
            for (int i = l; i < r; i++) {
                res[i] = i == 0 ? ivf0 : 1ll * ivf0 * (mod - res[i]) % mod;

                if (i + 1 < r) {
                    u64 __tmp = res[i];

                    for (int j = i + 1; j < r; j++)
                        res[j] = (res[j] + __tmp * _f[j - i]) % mod;
                }
            }

            return;
        }

        int nbit = mxb - logbr * (x + 1), nbr = 0;
        vu32 __tmp[br];

        while (l + (nbr << nbit) < r) {
            __tmp[nbr].resize(2 << nbit);
            nbr++;
        }

        for (int i = 0; i < nbr; i++) {
            if (i != 0) {
                intt(__tmp[i].data(), nbit + 1);

                for (int j = 0; j < (1 << nbit); j++) {
                    u32 &x = res[l + (i << nbit) + j], &y = __tmp[i][j + (1 << nbit)];
                    x = x + y - (x + y >= mod) * mod, y = 0;
                }
            }

            __div(x + 1, l + (i << nbit), min(l + ((i + 1) << nbit), r));

            if (i != nbr - 1) {
                memcpy(__tmp[i].data(), res.data() + l + (i << nbit), 4 << nbit);
                ntt(__tmp[i].data(), nbit + 1);

                for (int j = i + 1; j < nbr; j++)
                    for (int k = 0; k < (2 << nbit); k++)
                        __tmp[j][k] = (__tmp[j][k] + 1ll * __tmp[i][k] * __prentt[x][j - i - 1][k]) % mod;
            }
        }
    };
    __div(0, 0, nsize);
    return res.resize(nsize), res;
} inline poly poly::quo(const poly &g)const {
    using namespace __semiconvol__;
    int nsize = f.size(), mxb = lg(nsize - 1) + 1;
    vu32 res(1 << mxb), __prentt[maxdep][br], _f(g.f);
    u32 ivf0 = qpow(_f[0], -1);
    _f[0] = 0;
    _f.resize(nsize);

    for (int i = 0, k = mxb; k > bf; k -= logbr, i++) {
        for (int j = 0; j < br - 1; j++) {
            if ((j << (k - logbr)) >= nsize)
                break;

            __prentt[i][j].resize(2 << (k - logbr));
            int nl = (j << (k - logbr)), nr = min(((j + 2) << (k - logbr)), nsize) - nl;
            memcpy(__prentt[i][j].data(), _f.data() + nl, nr * 4);
            ntt(__prentt[i][j].data(), k - logbr + 1);
        }
    }

    function<void(int, int, int)>__div = [ =, &res, &__prentt, &_f, &mxb, &__div, &ivf0](int x, int l, int r) {
        if (r - l <= pbf) {
            for (int i = l; i < r; i++) {
                res[i] = 1ll * ivf0 * (i == 0 ? f[0] : f[i] + mod - res[i]) % mod;

                if (i + 1 < r) {
                    u64 __tmp = res[i];

                    for (int j = i + 1; j < r; j++)
                        res[j] = (res[j] + __tmp * _f[j - i]) % mod;
                }
            }

            return;
        }

        int nbit = mxb - logbr * (x + 1), nbr = 0;
        vu32 __tmp[br];

        while (l + (nbr << nbit) < r) {
            __tmp[nbr].resize(2 << nbit);
            nbr++;
        }

        for (int i = 0; i < nbr; i++) {
            if (i != 0) {
                intt(__tmp[i].data(), nbit + 1);

                for (int j = 0; j < (1 << nbit); j++) {
                    u32 &x = res[l + (i << nbit) + j], &y = __tmp[i][j + (1 << nbit)];
                    x = x + y - (x + y >= mod) * mod, y = 0;
                }
            }

            __div(x + 1, l + (i << nbit), min(l + ((i + 1) << nbit), r));

            if (i != nbr - 1) {
                memcpy(__tmp[i].data(), res.data() + l + (i << nbit), 4 << nbit);
                ntt(__tmp[i].data(), nbit + 1);

                for (int j = i + 1; j < nbr; j++)
                    for (int k = 0; k < (2 << nbit); k++)
                        __tmp[j][k] = (__tmp[j][k] + 1ll * __tmp[i][k] * __prentt[x][j - i - 1][k]) % mod;
            }
        }
    };
    __div(0, 0, nsize);
    return res.resize(nsize), res;
}
} using math::qpow;
using polynormial::poly;
} using namespace __POLY__;

int n, m;
unsigned a[262144];
int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    fin >> n;
    for (int i = 0; i <= n; i++)
        fin >> a[i];
    poly f(a, a + n + 1);
    int k = (mod + 1) / 3;
	u32 x = f[0], invx = qpow(x, mod - 2);
	u32 c = qpow(x, (2 * mod - 1) / 3);
	n = f.f.size();
	poly g(f);
	for (int i = 0; i < n; i++)
		g[i] = 1ll * g[i] * invx % mod;
	poly h(g.pow(k));
	for (int i = 0; i < n; i++)
		h[i] = 1ll * h[i] * c % mod;
	for (int i = 0; i < n; i++)
		fout << h[i] << ' ';
}