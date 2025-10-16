#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <type_traits>
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#   if !defined(_MSC_VER) || _MSC_VER>1400
#       define NOMINMAX 1
#       include <windows.h>
#   else
#       define WORD unsigned short
#       include <unistd.h>
#   endif
#   include <io.h>
#   define ON_WINDOWS
#else
#   define WORD unsigned short
#endif
void set_text_color(
#if !(defined(ON_WINDOWS) && (!defined(_MSC_VER) || _MSC_VER>1400)) && defined(__GNUC__)
    __attribute__((unused)) 
#endif
    WORD color
)
{
#if defined(ON_WINDOWS) && (!defined(_MSC_VER) || _MSC_VER>1400)
    static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
#endif
#if !defined(ON_WINDOWS) && defined(__CNUC__)
    if (isatty(2))
    {
        switch (color)
        {
        case 0x0c:
            fprintf(stderr, "\033[1;31m");
            break;
        case 0x0b:
            fprintf(stderr, "\033[1;36m");
            break;
        case 0x0a:
            fprintf(stderr, "\033[1;32m");
            break;
        case 0x0e:
            fprintf(stderr, "\033[1;33m");
            break;
        case 0x07:
        default:
            fprintf(stderr, "\033[0m");
        }
    }
#endif
}
namespace OY {
template <uint64_t __mod, bool s_isPrime = true>
class LongMontgomeryModInt {
public:
    using u32 = uint32_t;
    using i64 = int64_t;
    using u64 = uint64_t;
    using m64 = LongMontgomeryModInt;
    using value_type = u64;
    static constexpr u64 mod() { return __mod; }
    static constexpr u64 get_primitive_root_prime() {
        u64 tmp[64] = {};
        int cnt = 0;
        const u64 phi = __mod - 1;
        u64 m = phi;
        for (u64 i = 2; i * i <= m; ++i) {
            if (m % i == 0) {
                tmp[cnt++] = i;
                do m /= i;
                while (m % i == 0);
            }
        }
        if (m != 1) tmp[cnt++] = m;
        for (m64 res = 2;; res += 1) {
            bool f = true;
            for (int i = 0; i < cnt && f; ++i) f &= res.pow(phi / tmp[i]) != 1;
            if (f) return u32(res);
        }
    }
    constexpr LongMontgomeryModInt() : v_() {}
    ~LongMontgomeryModInt() = default;
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
    constexpr LongMontgomeryModInt(T v) : v_(reduce(mul(norm(v % i64(__mod)), r2))) {}
    constexpr LongMontgomeryModInt(const m64 &) = default;
    constexpr u64 val() const { return reduce({0, v_}); }
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
    explicit constexpr operator T() const { return T(val()); }
    constexpr m64 operator-() const {
        m64 res;
        res.v_ = (__mod & -(v_ != 0)) - v_;
        return res;
    }
    constexpr m64 inv_exgcd() const {
        i64 x1 = 1, x3 = 0, a = val(), b = __mod;
        while (b != 0) {
            i64 q = a / b, x1_old = x1, a_old = a;
            x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
        }
        return m64(x1);
    }
    constexpr m64 inv_fermat() const { return pow(__mod - 2); }
    constexpr m64 inv() const { return s_isPrime ? inv_fermat() : inv_exgcd(); }
    constexpr m64 &operator=(const m64 &) = default;
    constexpr m64 &operator+=(const m64 &rhs) {
        v_ += rhs.v_ - __mod;
        v_ += __mod & -(v_ >> 63);
        return *this;
    }
    constexpr m64 &operator-=(const m64 &rhs) {
        v_ -= rhs.v_;
        v_ += __mod & -(v_ >> 63);
        return *this;
    }
    constexpr m64 &operator*=(const m64 &rhs) {
        v_ = reduce(mul(v_, rhs.v_));
        return *this;
    }
    constexpr m64 &operator/=(const m64 &rhs) { return operator*=(rhs.inv()); }
    constexpr m64 operator++() { return operator+=(1); }
    constexpr m64 operator--() { return operator-=(1); }
    constexpr m64 operator++(int) {
    	m64 tmp(*this);
    	++*this;
    	return tmp;
    }
    constexpr m64 operator--(int) {
    	m64 tmp(*this);
    	--*this;
    	return tmp;
    }
    friend constexpr m64 operator+(const m64 &lhs, const m64 &rhs) { return m64(lhs) += rhs; }
    friend constexpr m64 operator-(const m64 &lhs, const m64 &rhs) { return m64(lhs) -= rhs; }
    friend constexpr m64 operator*(const m64 &lhs, const m64 &rhs) { return m64(lhs) *= rhs; }
    friend constexpr m64 operator/(const m64 &lhs, const m64 &rhs) { return m64(lhs) /= rhs; }
    friend constexpr bool operator==(const m64 &lhs, const m64 &rhs) { return lhs.v_ == rhs.v_; }
    friend constexpr bool operator!=(const m64 &lhs, const m64 &rhs) { return lhs.v_ != rhs.v_; }
    template <typename _Istream>
    friend _Istream &operator>>(_Istream &is, m64 &rhs) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
        i64 x;
#pragma GCC diagnostic pop
        is >> x;
        rhs = m64(x);
        return is;
    }
    template <typename _Ostream>
    friend _Ostream &operator<<(_Ostream &os, const m64 &rhs) { return os << rhs.val(); }
    constexpr m64 pow(u64 y) const {
        m64 res(1), x(*this);
        for (; y != 0; y >>= 1, x *= x) if (y & 1) res *= x;
        return res;
    }
private:
    static constexpr std::pair<u64, u64> mul(u64 x, u64 y) {
#ifdef __GNUC__
        unsigned __int128 res = (unsigned __int128)x * y;
        return {u64(res >> 64), u64(res)};
#elif defined(_MSC_VER)
        u64 h, l = _umul128(x, y, &h);
        return {h, l};
#else
        u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b * c;
        return {a * c + (ad >> 32) + (bc >> 32) + (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32), x * y};
#endif
    }
    static constexpr u64 mulh(u64 x, u64 y) {
#ifdef __GNUC__
        return u64((unsigned __int128)x * y >> 64);
#elif defined(_MSC_VER)
        return __umulh(x, y);
#else
        u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b * c;
        return a * c + (ad >> 32) + (bc >> 32) + (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32);
#endif
    }
    static constexpr u64 get_r() {
        u64 two = 2, iv = __mod * (two - __mod * __mod);
        iv *= two - __mod * iv;
        iv *= two - __mod * iv;
        iv *= two - __mod * iv;
        return iv * (two - __mod * iv);
    }
    static constexpr u64 get_r2() {
        u64 iv = -u64(__mod) % __mod;
        for (int i = 0; i != 64; ++i) ((iv <<= 1) >= __mod) && (iv -= __mod);
        return iv;
    }
    static constexpr u64 reduce(const std::pair<u64, u64> &x) {
        u64 res = x.first - mulh(x.second * r, __mod);
        return res + (__mod & -(res >> 63));
    }
    static constexpr u64 norm(i64 x) { return x + (__mod & -(x < 0)); }
    u64 v_;
    static constexpr u64 r = get_r();
    static constexpr u64 r2 = get_r2();
    static_assert((__mod & 1) == 1, "mod % 2 == 0\n");
    static_assert(r * __mod == 1, "???\n");
    static_assert((__mod & (1ULL << 63)) == 0, "mod >= (1ULL << 63)\n");
    static_assert(__mod != 1, "mod == 1\n");
};
}
using mint = OY::LongMontgomeryModInt<1000391835649, true>;
using std::vector;
namespace ntt {
static size_t rev[1 << 23];
static mint omegas[1 << 23];
size_t max_omega_count = 1, max_omega_count_lsh_1 = 2;
static constexpr mint G = mint::get_primitive_root_prime();
inline void get_rev(size_t len, int x) {
    if (len == 1 || rev[len + 1]) return;
    for (size_t i = 0; i < len; i++) rev[len | i] = rev[len | (i >> 1)] >> 1 | (i & 1) << x;
    if (max_omega_count == 1) {
        omegas[1] = mint(1);
        max_omega_count++;
        max_omega_count_lsh_1 = 4;
    }
    while (max_omega_count < len) {
        const mint gn = G.pow((mint::mod() - 1) / max_omega_count_lsh_1);
        for (size_t i = max_omega_count; i < max_omega_count_lsh_1; i++) {
            omegas[i] = omegas[i >> 1];
            omegas[i | 1] = omegas[i >> 1] * gn;
        }
        max_omega_count <<= 1;
        max_omega_count_lsh_1 <<= 1;
    }
}
inline void NTT(mint* a, size_t n) {
    for (size_t i = 1ull; i < n; ++i) if (size_t j = rev[n | i]; i < j) std::swap(a[i], a[j]);
    for (size_t i = 2, i_rsh_1 = 1; i <= n; i <<= 1, i_rsh_1 <<= 1) for (size_t j = 0; j < n; j += i) for (size_t k = j, now = k + i_rsh_1, kend = j + i_rsh_1; k < kend; k++, now++) {
        mint x = a[k], y = a[now] * omegas[now - j];
        a[k] += y;
        a[now] = x - y;
    }
}
inline void INTT(mint* a, size_t n) {
    for (size_t i = 1ull; i < n; ++i) if (size_t j = rev[n | i]; i < j) std::swap(a[i], a[j]);
    for (size_t i = 2, i_rsh_1 = 1; i <= n; i <<= 1, i_rsh_1 <<= 1) for (size_t j = 0; j < n; j += i) for (size_t k = j, now = k + i_rsh_1, kend = j + i_rsh_1; k < kend; k++, now++) {
        mint x = a[k], y = a[now] * omegas[now - j];
        a[k] += y;
        a[now] = x - y;
    }
    std::reverse(a + 1, a + n);
    mint invn = mint(n).inv();
    for (size_t i = 0; i < n; i++) a[i] *= invn;
}
static mint buf[1 << 23];
}
using ntt::get_rev;
using ntt::NTT;
using ntt::INTT;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wclass-memaccess"
inline vector<mint> operator*(const vector<mint>& a, const vector<mint>& b) {
    using ntt::buf;
    size_t anssiz = a.size() + b.size() - 1;
    vector<mint> c(anssiz);
    size_t len = 1;
    int x = -1;
    while (len < anssiz) len <<= 1, x++;
    get_rev(len, x);
    memcpy(buf, a.data(), a.size() * sizeof(mint));
    memset(buf + a.size(), 0, (len - a.size()) * sizeof(mint));
    memcpy(buf + len, b.data(), b.size() * sizeof(mint));
    memset(buf + len + b.size(), 0, (len - b.size()) * sizeof(mint));
    NTT(buf, len);
    NTT(buf + len, len);
    for (size_t i = 0; i < len; i++) buf[i] *= buf[i + len];
    INTT(buf, len);
    std::copy_n(buf, anssiz, c.begin());
    return c;
}
inline vector<mint>& operator*=(vector<mint>& a, const vector<mint>& b) {
    using ntt::buf;
    size_t anssiz = a.size() + b.size() - 1;
    size_t len = 1;
    int x = -1;
    while (len < anssiz) len <<= 1, x++;
    get_rev(len, x);
    a.resize(len);
    memcpy(buf, b.data(), b.size() * sizeof(mint));
    memset(buf + b.size(), 0, (len - b.size()) * sizeof(mint));
    NTT(a.data(), len);
    NTT(buf, len);
    for (size_t i = 0; i < len; i++) a[i] *= buf[i];
    INTT(a.data(), len);
    a.resize(anssiz);
    return a;
}
#pragma GCC diagnostic pop
static vector<mint> fac, mfac, invfac, minvfac, inv, minv;
inline void init(size_t n, mint m) {
    size_t tmp = (n << 1) | 1;
    fac.resize(tmp + 1);
    mfac.resize(tmp + 1);
    invfac.resize(tmp + 1);
    minvfac.resize(tmp + 1);
    inv.resize(tmp + 1);
    minv.resize(tmp + 1);
    fac[0] = mfac[0] = 1;
    for (size_t i = 1; i <= tmp; i++) {
        fac[i] = fac[i - 1] * mint(i);
        mfac[i] = mfac[i - 1] * mint(m - n + i - 1);
    }
    invfac[tmp] = fac[tmp].inv();
    minvfac[tmp] = mfac[tmp].inv();
    for (size_t i = tmp; i; i--) {
        invfac[i - 1] = invfac[i] * mint(i);
        minvfac[i - 1] = minvfac[i] * mint(m - n + i - 1);
        inv[i] = invfac[i] * fac[i - 1];
        minv[i] = minvfac[i] * mfac[i - 1];
    }
    minv[0] = 1;
}
inline void LagrangeInterpolation_ex(size_t n, mint m, const vector<mint>& a, vector<mint> &b) {
    vector<mint> f(n + 1), g(n << 1 | 1);
    init(n, m);
    for (size_t i = 0; i <= n; i++) {
        f[i] = invfac[i] * invfac[n - i] * a[i];
        ((n - i) & 1) && (f[i] = -f[i]);
    }
    std::copy_n(minv.begin() + 1, n << 1 | 1, g.begin());
    f *= g;
	b.resize(n + 1);
    for (size_t i = n; i <= (n << 1); i++) b[i - n] = mfac[i + 1] * minvfac[i - n] * f[i];
}
static vector<mint> mc;
size_t sval;
inline void prepare(mint n) {
    static vector<mint> md;
    size_t pos = 0;
    sval = sqrt(n.val()) + 1e-6;
    mint s(sval);
    mc.reserve(sval);
    md.reserve(sval);
    mint invs = s.inv();
    static vector<size_t> st;
    st.resize(log2(sval) + 5);
    for (size_t i = sval; i > 1ull; i >>= 1ull) st[++pos] = i;
    mc.resize(2ull);
    md.resize(2ull);
    mc[0] = 1ull;
    mc[1] = s + 1ull;
    for (size_t l = st[pos]; pos; l = st[--pos]) {
        LagrangeInterpolation_ex(l >> 1ull, mint((l >> 1ull) + 1ull), mc, md);
        mc.resize(mc.size() << 1ull);
        std::copy(md.begin(), md.end(), mc.begin() + md.size());
        LagrangeInterpolation_ex(mc.size() - 1ull, invs * (l >> 1ull), mc, md);
        for (size_t i = 0ull, iend = mc.size(); i < iend; i++) mc[i] *= md[i];
        if (l & 1ull) for (size_t i = 0; i <= l; i++) mc[i] *= s * i + l;
		else mc.resize(l + 1ull);
    }
}
template <typename _Clock, typename = std::void_t<typename _Clock::rep, typename _Clock::period, typename _Clock::duration,
        										  typename _Clock::time_point, decltype(_Clock::is_steady), decltype(_Clock::now())>>
struct __check_time_helper {
    typename _Clock::time_point t;
    double used;
    void start() { t = _Clock::now(); }
    void stop() { used += std::chrono::duration_cast<std::chrono::nanoseconds>
        (_Clock::now() - t).count() / 1e6; }
    ~__check_time_helper() {
    	set_text_color(0x0c);
		fprintf(stderr, "time used: %.2lfms\n", used);
		set_text_color(0x07);
	}
};
int main() {
    {
        __check_time_helper<std::chrono::steady_clock> _Helper;
        _Helper.start();
	    prepare(mint((long long)1e12));
        _Helper.stop();
    }
    int T;
    scanf("%d", &T);
    unsigned long long v;
    while (T--) {
        scanf("%llu", &v);
        mint res = 1;
        unsigned long long iend = v / sval;
        for (unsigned long long i = 0; i < iend; i++) res *= mc[i];
        for (unsigned long long i = 1ull * iend * sval + 1, iendd = v; i <= iendd; i++) res *= i;
        printf("%lu\n", (unsigned long)(res.val()));
    }
    return 0;
}