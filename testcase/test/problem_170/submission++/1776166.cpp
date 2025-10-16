#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <cassert>
#include <climits>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string.h>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>
namespace OY {
#define cin OY::inputHelper<1 << 18, 20>::getInstance()
#define getchar() ({char c=cin.getChar_Checked();cin.next();c; })
#define cout OY::outputHelper<1 << 18>::getInstance()
#define putchar cout.putChar
#define endl '\n'
#define putlog(...) OY::printLog(", ", __VA_ARGS__)
template <uint64_t _BufferSize = 1 << 18, uint64_t _BlockSize = 20>
class inputHelper {
public:
    FILE *m_filePtr;
    char m_buf[_BufferSize], *m_end, *m_cursor;
    bool m_ok;
    void flush() {
        uint64_t a = m_end - m_cursor;
        if (a >= _BlockSize) return;
        memmove(m_buf, m_cursor, a);
        uint64_t b = fread(m_buf + a, 1, _BufferSize - a, m_filePtr);
        m_cursor = m_buf;
        if (a + b < _BufferSize) {
            m_end = m_buf + a + b;
            *m_end = EOF;
        }
    }
public:
    explicit inputHelper(const char *inputFileName) : m_ok(true) {
        if (!*inputFileName) m_filePtr = stdin;
        else m_filePtr = fopen(inputFileName, "rt");
        m_end = m_cursor = m_buf + _BufferSize;
    }
    ~inputHelper() { fclose(m_filePtr); }
    static inputHelper<_BufferSize, _BlockSize> &getInstance() {
        static inputHelper<_BufferSize, _BlockSize> s_obj("");
        return s_obj;
    }
    static constexpr bool isBlank(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
    static constexpr bool isEndline(char c) { return c == '\n' || c == EOF; }
    const char &getChar_Checked() {
        if (m_cursor < m_end) return *m_cursor;
        uint64_t b = fread(m_buf, 1, _BufferSize, m_filePtr);
        m_cursor = m_buf;
        if (b < _BufferSize) {
            m_end = m_buf + b;
            *m_end = EOF;
        }
        return *m_cursor;
    }
    const char &getChar_Unchecked() const { return *m_cursor; }
    void next() { ++m_cursor; }
    void setState(bool _ok) { m_ok = _ok; }
    template <typename _Tp, typename std::enable_if<std::is_signed<_Tp>::value &std::is_integral<_Tp>::value>::type * = nullptr>
    inputHelper<_BufferSize, _BlockSize> &operator>>(_Tp &ret) {
        while (isBlank(getChar_Checked())) next();
        flush();
        if (getChar_Unchecked() == '-') {
            next();
            if (isdigit(getChar_Unchecked())) {
                ret = -(getChar_Unchecked() - '0');
                while (next(), isdigit(getChar_Unchecked())) ret = ret * 10 - (getChar_Unchecked() - '0');
            }
            else m_ok = false;
        }
        else {
            if (isdigit(getChar_Unchecked())) {
                ret = getChar_Unchecked() - '0';
                while (next(), isdigit(getChar_Unchecked())) ret = ret * 10 + (getChar_Unchecked() - '0');
            }
            else m_ok = false;
        }
        return *this;
    }
    template <typename _Tp, typename std::enable_if<std::is_unsigned<_Tp>::value &std::is_integral<_Tp>::value>::type * = nullptr>
    inputHelper<_BufferSize, _BlockSize> &operator>>(_Tp &ret) {
        while (isBlank(getChar_Checked())) next();
        flush();
        if (isdigit(getChar_Unchecked())) {
            ret = getChar_Unchecked() - '0';
            while (next(), isdigit(getChar_Unchecked())) ret = ret * 10 + (getChar_Unchecked() - '0');
        }
        else m_ok = false;
        return *this;
    }
    template <typename _Tp, typename std::enable_if<std::is_floating_point<_Tp>::value>::type * = nullptr>
    inputHelper<_BufferSize, _BlockSize> &operator>>(_Tp &ret) {
        bool neg = false, integer = false, decimal = false;
        while (isBlank(getChar_Checked())) next();
        flush();
        if (getChar_Unchecked() == '-') {
            neg = true;
            next();
        }
        if (!isdigit(getChar_Unchecked()) && getChar_Unchecked() != '.') {
            m_ok = false;
            return *this;
        }
        if (isdigit(getChar_Unchecked())) {
            integer = true;
            ret = getChar_Unchecked() - '0';
            while (next(), isdigit(getChar_Unchecked())) ret = ret * 10 + (getChar_Unchecked() - '0');
        }
        if (getChar_Unchecked() == '.') {
            next();
            if (isdigit(getChar_Unchecked())) {
                if (!integer) ret = 0;
                decimal = true;
                _Tp unit = 0.1;
                ret += unit * (getChar_Unchecked() - '0');
                while (next(), isdigit(getChar_Unchecked())) {
                    unit *= 0.1;
                    ret += unit * (getChar_Unchecked() - '0');
                }
            }
        }
        if (!integer && !decimal) m_ok = false;
        else if (neg) ret = -ret;
        return *this;
    }
    inputHelper<_BufferSize, _BlockSize> &operator>>(char &ret) {
        while (isBlank(getChar_Checked())) next();
        ret = getChar_Checked();
        if (ret == EOF) m_ok = false;
        else next();
        return *this;
    }
    inputHelper<_BufferSize, _BlockSize> &operator>>(std::string &ret) {
        while (isBlank(getChar_Checked())) next();
        if (getChar_Checked() != EOF) {
            ret.clear();
            do {
                ret += getChar_Checked();
                next();
            } while (!isBlank(getChar_Checked()) && getChar_Unchecked() != EOF);
        }
        else m_ok = false;
        return *this;
    }
    explicit operator bool() { return m_ok; }
};
template <uint64_t _BufferSize = 1 << 20>
class outputHelper {
    FILE *m_filePtr = nullptr;
    char m_buf[_BufferSize], *m_end, *m_cursor;
    char m_tempBuf[50], *m_tempBufCursor, *m_tempBufDot;
    uint64_t m_floatReserve, m_floatRatio;
public:
    outputHelper(const char *outputFileName, int prec = 6) : m_end(m_buf + _BufferSize) {
        if (!*outputFileName) m_filePtr = stdout;
        else m_filePtr = fopen(outputFileName, "wt");
        m_cursor = m_buf;
        m_tempBufCursor = m_tempBuf;
        precision(prec);
    }
    static outputHelper<_BufferSize> &getInstance() {
        static outputHelper<_BufferSize> s_obj("");
        return s_obj;
    }
    ~outputHelper() {
        flush();
        fclose(m_filePtr);
    }
    void precision(int prec) {
        m_floatReserve = prec;
        m_floatRatio = pow(10, prec);
        m_tempBufDot = m_tempBuf + prec;
    }
    outputHelper<_BufferSize> &flush() {
        fwrite(m_buf, 1, m_cursor - m_buf, m_filePtr);
        fflush(m_filePtr);
        m_cursor = m_buf;
        return *this;
    }
    void putChar(const char &c) {
        if (m_cursor == m_end) flush();
        *m_cursor++ = c;
    }
    void putS(const char *c) { while (*c) putChar(*c++); }
    template <typename _Tp, typename std::enable_if<std::is_signed<_Tp>::value &std::is_integral<_Tp>::value>::type * = nullptr>
    outputHelper<_BufferSize> &operator<<(const _Tp &ret) {
        _Tp _ret = _Tp(ret);
        if (_ret >= 0) {
            do {
                *m_tempBufCursor++ = '0' + _ret % 10;
                _ret /= 10;
            } while (_ret);
            do putChar(*--m_tempBufCursor);
            while (m_tempBufCursor > m_tempBuf);
        }
        else {
            putChar('-');
            do {
                *m_tempBufCursor++ = '0' - _ret % 10;
                _ret /= 10;
            } while (_ret);
            do putChar(*--m_tempBufCursor);
            while (m_tempBufCursor > m_tempBuf);
        }
        return *this;
    }
    template <typename _Tp, typename std::enable_if<std::is_unsigned<_Tp>::value &std::is_integral<_Tp>::value>::type * = nullptr>
    outputHelper<_BufferSize> &operator<<(const _Tp &ret) {
        _Tp _ret = _Tp(ret);
        do {
            *m_tempBufCursor++ = '0' + _ret % 10;
            _ret /= 10;
        } while (_ret);
        do putChar(*--m_tempBufCursor);
        while (m_tempBufCursor > m_tempBuf);
        return *this;
    }
    template <typename _Tp, typename std::enable_if<std::is_floating_point<_Tp>::value>::type * = nullptr>
    outputHelper<_BufferSize> &operator<<(const _Tp &ret) {
        if (ret < 0) {
            putChar('-');
            return *this << -ret;
        }
        _Tp _ret = ret * m_floatRatio;
        uint64_t integer = _ret;
        if (_ret - integer >= 0.4999999999) integer++;
        do {
            *m_tempBufCursor++ = '0' + integer % 10;
            integer /= 10;
        } while (integer);
        if (m_tempBufCursor > m_tempBufDot) {
            do putChar(*--m_tempBufCursor);
            while (m_tempBufCursor > m_tempBufDot);
            putChar('.');
        }
        else {
            putS("0.");
            for (int i = m_tempBufDot - m_tempBufCursor; i--;) putChar('0');
        }
        do putChar(*--m_tempBufCursor);
        while (m_tempBufCursor > m_tempBuf);
        return *this;
    }
    outputHelper<_BufferSize> &operator<<(const char &ret) {
        putChar(ret);
        return *this;
    }
    outputHelper<_BufferSize> &operator<<(const std::string &ret) {
        putS(ret.data());
        return *this;
    }
};
template <uint64_t _BufferSize, uint64_t _BlockSize>
inputHelper<_BufferSize, _BlockSize> &getline(inputHelper<_BufferSize, _BlockSize> &ih, std::string &ret) {
    ret.clear();
    if (ih.getChar_Checked() == EOF) ih.setState(false);
    else {
        while (!inputHelper<_BufferSize, _BlockSize>::isEndline(ih.getChar_Checked())) {
            ret += ih.getChar_Unchecked();
            ih.next();
        }
        ih.next();
    }
    return ih;
}
template <typename D, typename T, typename... S>
void printLog(D delim, const T &x, S... rest) {
    cout << x;
    if (sizeof...(rest) > 0) {
        cout << delim;
        printLog(delim, rest...);
    }
}
}
using OY::getline;
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
static constexpr int lg_mod = std::__countr_zero(mint::mod() - 1);
constexpr mint g = mint::get_primitive_root_prime();
constexpr mint G = g.pow((mint::mod() - 1) >> lg_mod);
static mint omegas[1 << lg_mod];
unsigned max_omegas_len = 1;
int lg_max_omegas_len = 0;
namespace {
struct __omegas_init_helper__ { __omegas_init_helper__() { omegas[0] = 1; } };
static __omegas_init_helper__ __helper__{};
}
inline void get_rev(unsigned len, int x) {
    if (len == 1 || max_omegas_len >= len) return;
    omegas[1ul << x] = G.pow(1ul << (lg_mod - 2 - x));
    for (int i = x; i > lg_max_omegas_len; i--) omegas[1ul << (i - 1)] = omegas[1ul << i] * omegas[1ul << i];
    for (unsigned i = max_omegas_len | 1u; i < len; i++) omegas[i] = omegas[i & (i - 1)] * omegas[i & ((~i) + 1)];
    max_omegas_len = len;
    lg_max_omegas_len = x + 1;
}
inline void NTT(mint* a, unsigned n) {
    for (unsigned l = n >> 1; l; l >>= 1) {
        mint *k = a;
        for (mint *g = omegas; k < a + n; k += (l << 1), ++g) for (mint *x = k; x < k + l; x++) {
            mint o = x[l] * *g;
            x[l] = *x - o;
            *x += o;
        }
    }
}
inline void INTT(mint* a, unsigned n) {
    for (unsigned l = 1; l < n; l <<= 1) {
        mint *k = a;
        for (mint *g = omegas; k < a + n; k += (l << 1), ++g) for (mint *x = k; x < k + l; x++) {
            mint o = x[l];
            x[l] = *g * (*x - o);
            *x += o;
        }
    }
    mint invn = mint(n).inv();
    for (unsigned i = 0; i < n; i++) a[i] *= invn;
    std::reverse(a + 1, a + n);
}
static mint buf[1 << lg_mod];
constexpr unsigned bf_limit = 10000;
}
using ntt::get_rev;
using ntt::NTT;
using ntt::INTT;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wclass-memaccess"
inline vector<mint> operator*(const vector<mint>& a, const vector<mint>& b) {
    using ntt::buf;
    unsigned anssiz = a.size() + b.size() - 1;
    vector<mint> c(anssiz);
    if (a.size() * b.size() < ntt::bf_limit) {
        for (unsigned i = 0; i < a.size(); i++) for (unsigned j = 0; j < b.size(); j++) c[i + j] += a[i] * b[j];
        return c;
    }
    unsigned len = 1;
    int x = 0;
    while (len < anssiz) len <<= 1, x++;
    get_rev(len, x);
    memcpy(buf, a.data(), a.size() * sizeof(mint));
    memset(buf + a.size(), 0, (len - a.size()) * sizeof(mint));
    memcpy(buf + len, b.data(), b.size() * sizeof(mint));
    memset(buf + len + b.size(), 0, (len - b.size()) * sizeof(mint));
    NTT(buf, len);
    NTT(buf + len, len);
    for (unsigned i = 0; i < len; i++) buf[i] *= buf[i + len];
    INTT(buf, len);
    std::copy_n(buf, anssiz, c.begin());
    return c;
}
inline vector<mint>& operator*=(vector<mint>& a, const vector<mint>& b) {
    using ntt::buf;
    unsigned anssiz = a.size() + b.size() - 1;
    if (a.size() * b.size() < ntt::bf_limit) {
        vector<mint> c(anssiz);
        for (unsigned i = 0; i < a.size(); i++) for (unsigned j = 0; j < b.size(); j++) c[i + j] += a[i] * b[j];
        a.swap(c);
        return a;
    }
    unsigned len = 1;
    int x = -1;
    while (len < anssiz) len <<= 1, x++;
    get_rev(len, x);
    a.resize(len);
    memcpy(buf, b.data(), b.size() * sizeof(mint));
    memset(buf + b.size(), 0, (len - b.size()) * sizeof(mint));
    NTT(a.data(), len);
    NTT(buf, len);
    for (unsigned i = 0; i < len; i++) a[i] *= buf[i];
    INTT(a.data(), len);
    a.resize(anssiz);
    return a;
}
#pragma GCC diagnostic pop
namespace fac_base {
vector<mint> fac, mfac, invfac, minvfac, inv, minv;
static constexpr mint inv2 = (mint::mod() + 1) >> 1;
inline void prepare_fac(unsigned n) {
    unsigned lastlen = fac.size();
    if (lastlen > n) return;
    fac.resize(n + 1);
    invfac.resize(n + 1);
    inv.resize(n + 1);
#if 1
    if (lastlen) {
        for (unsigned i = lastlen; i <= n; i++) fac[i] = fac[i - 1] * i;
        invfac[n] = fac[n].inv();
        for (unsigned i = n; i >= lastlen; i--) {
            invfac[i - 1] = invfac[i] * i;
            inv[i] = fac[i - 1] * invfac[i];
        }
    }
    else
#endif
    {
        fac[0] = 1;
        for (unsigned i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
        invfac[n] = fac[n].inv();
        for (unsigned i = n; i; i--) {
            invfac[i - 1] = invfac[i] * i;
            inv[i] = fac[i - 1] * invfac[i];
        }
    }
}
inline void prepare_lagrange(unsigned n, unsigned n_lsh_1, mint m) {
    unsigned tmp(n_lsh_1 | 1);
    fac.resize(tmp + 1);
    mfac.resize(tmp + 1);
    invfac.resize(tmp + 1);
    minvfac.resize(tmp + 1);
    inv.resize(tmp + 1);
    minv.resize(tmp + 1);
    fac[0] = mfac[0] = 1;
    for (unsigned i = 1; i <= tmp; i++) {
        fac[i] = fac[i - 1] * i;
        mfac[i] = mfac[i - 1] * (m - n + i - 1);
    }
    invfac[tmp] = fac[tmp].inv();
    minvfac[tmp] = mfac[tmp].inv();
    for (unsigned i = tmp; i; i--) {
        invfac[i - 1] = invfac[i] * i;
        minvfac[i - 1] = minvfac[i] * (m - n + i - 1);
        inv[i] = invfac[i] * fac[i - 1];
        minv[i] = minvfac[i] * mfac[i - 1];
    }
    minv[0] = 1;
}
}
using fac_base::prepare_fac;
inline vector<mint> operator+(const vector<mint>& a, const vector<mint>& b) {
    vector<mint> c(a);
    c.resize(std::max(a.size(), b.size()));
    for (size_t i = 0, iend = b.size(); i < iend; i++) c[i] += b[i];
    return c;
}
inline vector<mint>& operator+=(vector<mint>& a, const vector<mint>& b) {
    a.resize(std::max(a.size(), b.size()));
    for (size_t i = 0, iend = b.size(); i < iend; i++) a[i] += b[i];
    return a;
}
inline vector<mint> operator-(const vector<mint>& a, const vector<mint>& b) {
    vector<mint> c(a);
    c.resize(std::max(a.size(), b.size()));
    for (size_t i = 0, iend = b.size(); i < iend; i++) c[i] -= b[i];
    return c;
}
inline vector<mint>& operator-=(vector<mint>& a, const vector<mint>& b) {
    a.resize(std::max(a.size(), b.size()));
    for (size_t i = 0, iend = b.size(); i < iend; i++) a[i] -= b[i];
    return a;
}
inline vector<mint> inverse(const vector<mint>& a, size_t l) {
    static constexpr mint two(2);
    vector<mint> b{a[0].inv()}, c;
    int x = 1;
    for (size_t lim = 4; lim < (l << 2); lim <<= 1, x++) {
        c.resize(lim);
        std::copy_n(a.begin(), std::min<size_t>(lim >> 1, a.size()), c.begin());
        b.resize(lim);
        get_rev(lim, x);
        NTT(c.data(), lim);
        NTT(b.data(), lim);
        for (size_t i = 0; i < lim; i++) b[i] *= two - (b[i] * c[i]);
        INTT(b.data(), lim);
        b.resize(lim >> 1);
    }
    b.resize(l);
    return b;
}
inline vector<mint> inverse(const vector<mint>& a) { return inverse(a, a.size()); }
inline vector<mint> operator%(const vector<mint>& a, const vector<mint>& b) {
    size_t n = a.size(), m = b.size();
    vector<mint> F(a), G(b);
    vector<mint> Q(G);
    std::reverse(F.begin(), F.end());
    std::reverse(Q.begin(), Q.end());
    Q.resize(n - m + 1);
    Q = inverse(Q) * F;
    Q.resize(n - m + 1);
    std::reverse(Q.begin(), Q.end());
    std::reverse(F.begin(), F.end());
    Q *= G;
    Q.resize(m - 1);
    Q = F - Q;
    Q.resize(m - 1);
    return Q;
}
inline vector<mint> operator/(const vector<mint>& a, const vector<mint>& b) {
    size_t n = a.size(), m = b.size();
    vector<mint> F(a), G(b);
    vector<mint> Q(G);
    std::reverse(F.begin(), F.end());
    std::reverse(Q.begin(), Q.end());
    Q.resize(n - m + 1);
    Q = inverse(Q) * F;
    Q.resize(n - m + 1);
    std::reverse(Q.begin(), Q.end());
    std::reverse(F.begin(), F.end());
    return Q;
}
inline vector<mint> derivate(const vector<mint>& a) {
    vector<mint> ans(a.size() - 1);
    for (size_t i = 1; i < a.size(); i++) ans[i - 1] = a[i] * i;
    return ans;
}
inline vector<mint> integrate(const vector<mint>& a) {
    vector<mint> ans(a.size() + 1);
    prepare_fac(a.size());
    for (size_t i = 1; i < a.size(); i++) ans[i] = a[i - 1] * fac_base::inv[i];
    return ans;
}
inline vector<mint> log(const vector<mint>& a) {
    vector<mint> tmp(inverse(a));
    tmp *= derivate(a);
    tmp = integrate(tmp);
    return tmp;
}
inline vector<mint> exp(const vector<mint>& a) {
    const size_t n = a.size();
    vector<mint> ans{1}, tmp;
    ans.reserve(n << 2);
    for (size_t lim = 2; lim <= (n << 1); lim <<= 1) {
        ans.resize(lim);
        tmp.resize(lim);
        std::copy_n(ans.begin(), std::min(lim >> 1, a.size()), tmp.begin());
        tmp = log(tmp);
        tmp.resize(lim);
        for (size_t i = 0, iend = std::min<size_t>(lim, a.size()); i < iend; i++) tmp[i] = a[i] - tmp[i];
        for (size_t i = std::min<size_t>(lim, a.size()); i < lim; i++) tmp[i] = -tmp[i];
        tmp[0]++;
        ans *= tmp;
        ans.resize(lim);
    }
    ans.resize(n);
    return ans;
}
namespace cipolla {
static constexpr mint none(-1);
static constexpr unsigned long long mod = mint::mod();
mint legrende(unsigned long long a) { return mint(a).pow((mod - 1) >> 1); }
mint find_nsqr(unsigned long long n) {
    for (unsigned long long i = 0; i < mod; i++) if (legrende(i * i - n) == none) return mint(i);
    return none;
}
mint a, n;
class cp {
    mint _M_real, _M_imag;
public:
    inline cp(const mint& r = mint(), const mint& i = mint()) : _M_real(r), _M_imag(i) {}
    inline cp(const cp& o) : _M_real(o._M_real), _M_imag(o._M_imag) {}
    inline cp& operator=(const cp& o) = default;
    inline cp& operator=(const mint& o) {
        _M_real = o;
        _M_imag = 0;
        return *this;
    }
    inline ~cp() = default;
    inline cp operator+(const cp& o) const { return cp(_M_real + o._M_real, _M_imag + o._M_imag); }
    inline cp operator*(const cp& o) const { return cp(_M_real * o._M_real + _M_imag * o._M_imag * (a * a - n), _M_real * o._M_imag + _M_imag * o._M_real); }
    friend inline cp operator-(const cp& o) { return cp(-o._M_real, -o._M_imag); }
    inline cp operator-(const cp& o) const { return *this + -o; }
    inline cp& operator+=(const cp& o) { return *this = *this + o; }
    inline cp& operator*=(const cp& o) { return *this = *this * o; }
    inline cp& operator-=(const cp& o) { return *this = *this - o; }
    inline mint& real() { return _M_real; }
    inline mint& imag() { return _M_imag; }
    inline const mint& real() const { return _M_real; }
    inline const mint& imag() const { return _M_imag; }
    inline cp conj() const { return cp(_M_real, -_M_imag); }
};
inline cp qpow(const cp& bs, unsigned long long po) {
    cp ans(1, 0), base(bs);
    while (po) {
        if (po & 1) ans *= base;
        base *= base;
        po >>= 1;
    }
    return ans;
}
inline mint sqrt(const mint& nn) {
    n = nn;
    if (n == mint(0)) return mint(0);
    if (legrende(n.val()) != 1) return none;
    a = find_nsqr(n.val());
    mint tmp = qpow(cp(a, 1), (mod + 1) >> 1).real();
    return tmp.val() < (-tmp).val() ? tmp : -tmp;
}
}
namespace sqr {
inline vector<mint> sqr(const vector<mint>& a) {
    using ntt::buf;
    size_t anssiz = a.size() * 2 - 1;
    vector<mint> c(anssiz);
    size_t len = 1;
    int x = -1;
    while (len < anssiz) len <<= 1, x++;
    get_rev(len, x);
    std::fill_n(std::copy_n(a.begin(), a.size(), buf), len - a.size(), mint(0));
    NTT(buf, len);
    for (size_t i = 0; i < len; i++) buf[i] *= buf[i];
    INTT(buf, len);
    std::copy_n(buf, anssiz, c.begin());
    return c;
}
}
vector<mint> sqrt(const vector<mint>& arr) {
    using cipolla::none;
    using fac_base::inv2;
    mint sqrt_of_first = cipolla::sqrt(arr[0]);
    static constexpr mint one(1);
    if (sqrt_of_first == none && arr[0] != one) return vector<mint>();
    vector<mint> ans{sqrt_of_first};
    const size_t n = arr.size();
    for (size_t lim = 2; lim < (n << 2); lim <<= 1) {
        ans = (sqr::sqr(ans) + arr) * inverse(ans);
        ans.resize(lim);
        for (mint& v : ans) v *= inv2;
    }
    ans.resize(arr.size());
    return ans;
}
namespace sin_cos {
static constexpr mint img = ((mint::mod() & 3) == 1) ? ((mint::mod() - 1) >> 2) : (mint::mod() - 1);
static constexpr mint inv2img = (img * 2).inv();
}
vector<mint> sin(const vector<mint>& arr) {
    vector<mint> tmp(arr);
    for (mint& v : tmp) v *= sin_cos::img;
    tmp = exp(tmp);
    vector<mint> ans(inverse(tmp));
    for (size_t i = 0, iend = arr.size(); i < iend; i++) ans[i] = (tmp[i] - ans[i]) * sin_cos::inv2img;
    return ans;
}
vector<mint> cos(const vector<mint>& arr) {
    using fac_base::inv2;
    vector<mint> tmp(arr);
    for (mint& v : tmp) v *= sin_cos::img;
    tmp = exp(tmp);
    vector<mint> ans(inverse(tmp));
    for (size_t i = 0, iend = arr.size(); i < iend; i++) ans[i] = (ans[i] + tmp[i]) * inv2;
    return ans;
}
vector<mint> asin(const vector<mint>& arr) {
    vector<mint> tmp(sqr::sqr(arr));
    for (mint& v : tmp) v = -v;
    tmp[0]++;
    return integrate(derivate(arr) * inverse(sqrt(tmp)));
}
vector<mint> atan(const vector<mint>& arr) {
    vector<mint> tmp(sqr::sqr(arr));
    tmp[0]++;
    return integrate(derivate(arr) * inverse(tmp));
}
vector<mint> pow(const vector<mint>& arr, size_t power) {
    auto it = std::find_if(arr.begin(), arr.end(), [=](const mint& v) { return v.val() != 0; });
    if (!power) {
        vector<mint> ans(arr.size(), mint(0));
        ans[0] = 1;
        return ans;
    }
    if ((it - arr.begin()) * power >= arr.size()) return vector<mint>(arr.size(), mint(0));
    vector<mint> ans(it, arr.end());
    mint tmp = it->inv();
    for (mint& v : ans) v *= tmp;
    ans = log(ans);
    for (mint& v : ans) v *= power;
    ans = exp(ans);
    tmp = it->pow(power);
    for (mint& v : ans) v *= tmp;
    ans.insert(ans.begin(), std::min<size_t>((it - arr.begin()) * power, arr.size()), mint(0));
    return ans;
}
vector<mint> pow(const vector<mint>& arr, size_t power, size_t __power, size_t __flg_power) {
    auto it = std::find_if(arr.begin(), arr.end(), [=](const mint& v) { return v.val() != 0; });
    if ((it - arr.begin()) * __flg_power >= arr.size() || it == arr.end()) return vector<mint>(arr.size(), mint(0));
    vector<mint> ans(it, arr.end());
    mint tmp = it->inv();
    for (mint& v : ans) v *= tmp;
    ans = log(ans);
    for (mint& v : ans) v *= power;
    ans = exp(ans);
    tmp = it->pow(__power);
    for (mint& v : ans) v *= tmp;
    ans.insert(ans.begin(), std::min<size_t>((it - arr.begin()) * power, arr.size()), mint(0));
    return ans;
}
namespace eval_base {
struct SegTree {
    size_t l, r;
    vector<mint> d, dr;
    SegTree *left, *right;
    inline void pushup_d() { d = right->dr * left->d + left->dr * right->d; }
    inline void pushup_dr() { dr = left->dr * right->dr; }
    inline void pushup() {
        pushup_d();
        pushup_dr();
    }
    void build_eval(const vector<mint>& arr) {
        if (l == r) {
            dr.resize(2);
            dr[0] = mint::mod() - arr[l];
            dr[1] = 1;
            d.resize(1);
            d[0] = arr[l];
            return;
        }
        left->build_eval(arr);
        right->build_eval(arr);
        pushup();
    }
    void build_ffp(const vector<mint>& arr) {
        if (l == r) {
            dr.resize(2);
            dr[0] = mint::mod() - l;
            dr[1] = 1;
            d.resize(1);
            d[0] = arr[l];
            return;
        }
        left->build_ffp(arr);
        right->build_ffp(arr);
        pushup();
    }
    void build_poly(const vector<mint>& arr) {
        if (l == r) {
            dr.resize(2);
            dr[0] = mint::mod() - l;
            dr[1] = 1;
            return;
        }
        left->build_poly(arr);
        right->build_poly(arr);
        pushup_dr();
    }
    void build_inter(const vector<mint>& arr) {
        if (l == r) {
            d.resize(1);
            d[0] = arr[l];
            return;
        }
        left->build_inter(arr);
        right->build_inter(arr);
        pushup_d();
    }
    void init_tree() {
        if (l == r) return;
        size_t mid = l + ((r - l) >> 1);
        left = new SegTree(l, mid);
        right = new SegTree(mid + 1, r);
        left->init_tree();
        right->init_tree();
    }
    SegTree(size_t il = 0, size_t ir = 0,
        const vector<mint>& d_ = vector<mint>(),
        const vector<mint>& dr_ = vector<mint>(),
        SegTree *ls = nullptr, SegTree *rs = nullptr)
        : l(il), r(ir), d(d_), dr(dr_), left(ls), right(rs) {}
};
SegTree *root;
vector<mint> ans;
void cdq(SegTree *cur, const vector<mint>& arr) {
    if (cur->l == cur->r) {
        ans[cur->l] = arr[0];
        return;
    }
    eval_base::cdq(cur->left, arr % cur->left->dr);
    eval_base::cdq(cur->right, arr % cur->right->dr);
}
vector<mint> eval(const vector<mint>& arr, const vector<mint>& point_x) {
    const size_t m = point_x.size();
    ans.resize(m);
    root = new SegTree(0, m);
    root->init_tree();
    root->build_eval(point_x);
    eval_base::cdq(root, arr);
    return ans;
}
}
using eval_base::eval;
namespace interpolation {
using eval_base::root;
using eval_base::SegTree;
using eval_base::ans;
vector<mint> tmparr;
void cdq(SegTree *cur, const vector<mint>& arr) {
    if (cur->r - cur->l < 256) {
        for (size_t i = cur->l; i <= cur->r; i++) {
            mint tmp(0);
            const mint x(tmparr[i]);
            for (size_t j = arr.size() - 1; ~j; j--) tmp = tmp * x + arr[j];
            ans[i] = tmp;
        }
        return;
    }
    interpolation::cdq(cur->left, arr % cur->left->dr);
    interpolation::cdq(cur->right, arr % cur->right->dr);
}
vector<mint> interpolate(const vector<mint>& point_x, const vector<mint>& point_y) {
    const size_t n = point_x.size();
    ans.resize(n);
    tmparr = point_x;
    root = new SegTree(0, n - 1);
    root->init_tree();
    root->build_eval(point_x);
    interpolation::cdq(root, derivate(root->dr));
    for (size_t i = 0; i < n; i++) ans[i] = point_y[i] / ans[i];
    root->build_inter(ans);
    ans = root->d;
    delete root;
    return ans;
}
}
using interpolation::interpolate;
namespace ffp {
using eval_base::root;
using eval_base::SegTree;
using eval_base::ans;
void cdq(SegTree *cur, const vector<mint>& arr) {
    if (cur->l == cur->r) {
        ans[cur->l] = arr[0];
        return;
    }
    ffp::cdq(cur->left, arr % cur->left->dr);
    ffp::cdq(cur->right, arr % cur->right->dr);
}
vector<mint> poly_to_ffp(const vector<mint>& arr) {
    using fac_base::invfac;
    const size_t n = arr.size();
    prepare_fac(n);
    ans.resize(n);
    vector<mint> tmp(n);
    root = new SegTree(0, n - 1);
    root->init_tree();
    root->build_poly(arr);
    ffp::cdq(root, arr);
    for (size_t i = 0; i < n; i++) {
        tmp[i] = i & 1 ? -invfac[i] : invfac[i];
        ans[i] *= invfac[i];
    }
    return ans * tmp;
}
vector<mint> ffp_to_poly(const vector<mint>& arr) {
    using fac_base::invfac;
    const size_t n = arr.size();
    prepare_fac(n);
    vector<mint> tmp = arr * invfac;
    tmp.resize(n + 1);
    for (size_t i = 0; i <= n; i++) {
        tmp[i] *= invfac[n - i];
        if ((n - i) & 1) tmp[i] = -tmp[i];
    }
    root = new SegTree(0, n);
    root->init_tree();
    root->build_ffp(tmp);
    tmp = root->d;
    delete root;
    return tmp;
}
}
using ffp::poly_to_ffp;
using ffp::ffp_to_poly;
inline void LagrangeInterpolation_ex(unsigned n, mint m,
    const vector<mint>& a_in,
    vector<mint>& a_out)
{
    using namespace fac_base;
    const unsigned n_lsh_1(n << 1);
    vector<mint> f, g(n_lsh_1 | 1);
    f.resize(n + 1);
    prepare_lagrange(n, n_lsh_1, m);
    mint tmp;
    for (unsigned i(0); i <= n; i++) {
        tmp = invfac[i] * invfac[n - i];
        f[i] = tmp * a_in[i];
        ((n - i) & 1) && (f[i] = -f[i]);
    }
    memcpy(g.data(), minv.data() + 1, (n_lsh_1 | 1) * sizeof(mint));
    f *= g;
    a_out.resize(n + 1);
    for (unsigned i(n), j(0); i <= n_lsh_1; i++, j++) {
        tmp = mfac[i + 1] * minvfac[j];
        a_out[j] = tmp * f[i];
    }
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
mint getfac(uint64_t v) {
    mint res = 1;
    if (v <= 1) return 1;
    uint64_t iend = v / sval;
    for (uint64_t i = 0; i < iend; i++) res *= mc[i];
    for (uint64_t i = 1ull * iend * sval + 1, iendd = v; i <= iendd; i++) res *= i;
    return res;
}
int main() {
    auto t = std::chrono::steady_clock::now();
	prepare(mint((long long)1e12));
    fprintf(stderr, "%.2lfms", std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - t).count() / 1e6);
    int T;
    scanf("%d", &T);
    unsigned long long v;
    while (T--) {
        scanf("%llu", &v);
        mint res = 1;
        if (v > 1000391835648ull - v) {
            res = getfac(1000391835648ull - v).inv();
            if (!(v & 1)) res = -res;
        }
        else res = getfac(v);
        printf("%llu\n", res.val());
    }
    return 0;
}