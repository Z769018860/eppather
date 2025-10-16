#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef pair<i64, i64> pi;
const int MAXN = 30005;
const int NO_SOLUTION = 0;
i64 mod;

u128 ctz(u128 x) { return (!x) ? 128 : u64(x) ? __builtin_ctzll(x) : __builtin_ctzll(x >> 64) + 64; }

u128 gcd(u128 a, u128 b)
{
    if (!a || !b)
        return a | b;

    int shift = ctz(a | b);

    for (b >>= ctz(b); a; a -= b)
        if ((a >>= ctz(a)) < b)
            swap(a, b);

    return b << shift;
}

struct mint
{
    i64 val;
    mint() { val = 0; }
    mint(const i64 &v)
    {
        val = (-mod <= v && v < mod) ? v : v % mod;
        if (val < 0)
            val += mod;
    }

    friend ostream &operator<<(ostream &os, const mint &a) { return os << a.val; }
    friend bool operator==(const mint &a, const mint &b) { return a.val == b.val; }
    friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
    friend bool operator<(const mint &a, const mint &b) { return a.val < b.val; }

    mint operator-() const { return mint(-val); }
    mint &operator+=(const mint &m)
    {
        if ((val += m.val) >= mod)
            val -= mod;
        return *this;
    }
    mint &operator-=(const mint &m)
    {
        if ((val -= m.val) < 0)
            val += mod;
        return *this;
    }
    mint &operator*=(const mint &m)
    {
        val = (__int128)val * m.val % mod;
        return *this;
    }
    friend mint ipow(mint a, i64 p)
    {
        mint ans = 1;
        for (; p; p /= 2, a *= a)
            if (p & 1)
                ans *= a;
        return ans;
    }
    friend mint inv(const mint &a)
    {
        assert(a.val);
        return ipow(a, mod - 2);
    }
    mint &operator/=(const mint &m) { return (*this) *= inv(m); }

    friend mint operator+(mint a, const mint &b) { return a += b; }
    friend mint operator-(mint a, const mint &b) { return a -= b; }
    friend mint operator*(mint a, const mint &b) { return a *= b; }
    friend mint operator/(mint a, const mint &b) { return a /= b; }
    operator int64_t() const { return val; }
};

i64 mul(i64 x, i64 y, i64 mod) { return (i128)x * y % mod; }

i64 ipow(i64 x, i64 y, i64 p)
{
    i64 ret = 1, piv = x % p;
    while (y)
    {
        if (y & 1)
            ret = mul(ret, piv, p);
        piv = mul(piv, piv, p);
        y >>= 1;
    }
    return ret;
}

namespace factors
{
    bool miller_rabin(i64 x, i64 a)
    {
        if (x % a == 0)
            return 0;
        i64 d = x - 1;
        while (1)
        {
            i64 tmp = ipow(a, d, x);
            if (d & 1)
                return (tmp != 1 && tmp != x - 1);
            else if (tmp == x - 1)
                return 0;
            d >>= 1;
        }
    }
    bool isprime(i64 x)
    {
        for (auto &i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
        {
            if (x == i)
                return 1;
            if (x > 40 && miller_rabin(x, i))
                return 0;
        }
        if (x <= 40)
            return 0;
        return 1;
    }
    i64 f(i64 x, i64 n, i64 c) { return (c + mul(x, x, n)) % n; }
    void rec(i64 n, vector<i64> &v)
    {
        if (n == 1)
            return;
        if (n % 2 == 0)
        {
            v.push_back(2);
            rec(n / 2, v);
            return;
        }
        if (isprime(n))
        {
            v.push_back(n);
            return;
        }
        i64 a, b, c;
        while (1)
        {
            a = rand() % (n - 2) + 2;
            b = a;
            c = rand() % 20 + 1;
            do
            {
                a = f(a, n, c);
                b = f(f(b, n, c), n, c);
            } while (gcd(abs(a - b), n) == 1);
            if (a != b)
                break;
        }
        i64 x = gcd(abs(a - b), n);
        rec(x, v);
        rec(n / x, v);
    }
    vector<i64> factorize(i64 n)
    {
        vector<i64> ret;
        rec(n, ret);
        sort(ret.begin(), ret.end());
        return ret;
    }
    i64 euler_phi(i64 n)
    {
        auto pf = factorize(n);
        pf.resize(unique(pf.begin(), pf.end()) - pf.begin());
        for (auto &p : pf)
        {
            n -= n / p;
        }
        return n;
    }
};

namespace kth_root_mod
{
    template <typename T>
    struct Memo
    {
        Memo(const T &g, int s, int _period)
        {
            size = 1;
            while (2 * size <= min(s, _period))
                size *= 2;
            mask = size - 1;
            period = _period;
            vs.resize(size);
            os.resize(size + 1);
            T x(1);
            for (int i = 0; i < size; ++i, x *= g)
                os[((i64)x) & mask]++;
            for (int i = 1; i < size; ++i)
                os[i] += os[i - 1];
            x = 1;
            for (int i = 0; i < size; ++i, x *= g)
                vs[--os[((i64)x) & mask]] = {x, i};
            gpow = x;
            os[size] = size;
        }
        int find(T x) const
        {
            for (int t = 0; t < period; t += size, x *= gpow)
            {
                for (int m = (((i64)x) & mask), i = os[m]; i < os[m + 1]; ++i)
                {
                    if (x == vs[i].first)
                    {
                        int ret = vs[i].second - t;
                        return ret < 0 ? ret + period : ret;
                    }
                }
            }
            assert(0);
        }
        T gpow;
        int size, mask, period;
        vector<pair<T, int>> vs;
        vector<int> os;
    };

    i64 inv(i64 a, i64 p)
    {
        i64 b = p, x = 1, y = 0;
        while (a)
        {
            i64 q = b / a;
            swap(a, b %= a);
            swap(x, y -= q * x);
        }
        assert(b == 1);
        return y < 0 ? y + p : y;
    }

    mint pe_root(i64 c, i64 pi, i64 ei, i64 p)
    {
        i64 s = p - 1, t = 0;
        while (s % pi == 0)
            s /= pi, ++t;
        i64 pe = 1;
        for (i64 _ = 0; _ < ei; ++_)
            pe *= pi;

        i64 u = inv(pe - s % pe, pe);
        mint mc = c, one = 1;
        mint z = ipow(mc, (s * u + 1) / pe);
        mint zpe = ipow(mc, s * u);
        if (zpe == one)
            return z;

        mint vs;
        {
            i64 ptm1 = 1;
            for (i64 _ = 0; _ < t - 1; ++_)
                ptm1 *= pi;
            for (mint v = 2;; v += one)
            {
                vs = ipow(v, s);
                if (ipow(vs, ptm1) != one)
                    break;
            }
        }

        mint vspe = ipow(vs, pe);
        i64 vs_e = ei;
        mint base = vspe;
        for (i64 _ = 0; _ < t - ei - 1; _++)
            base = ipow(base, pi);
        Memo<mint> memo(base, (i64)(sqrt(t - ei) * sqrt(pi)) + 1, pi);

        while (zpe != one)
        {
            mint tmp = zpe;
            i64 td = 0;
            while (tmp != one)
                ++td, tmp = ipow(tmp, pi);
            i64 e = t - td;
            while (vs_e != e)
            {
                vs = ipow(vs, pi);
                vspe = ipow(vspe, pi);
                ++vs_e;
            }

            
            mint base_zpe = mint(1) / zpe;
            for (i64 _ = 0; _ < td - 1; _++)
                base_zpe = ipow(base_zpe, pi);
            i64 bsgs = memo.find(base_zpe);

            z *= ipow(vs, bsgs);
            zpe *= ipow(vspe, bsgs);
        }
        return z;
    }

    i64 kth_root(i64 a, i64 k, i64 p)
    {
        mod = p;
        a %= p;
        if (k == 0)
            return a == 1 ? a : NO_SOLUTION;
        if (a <= 1 || k <= 1)
            return a;

        assert(p > 2);
        i64 g = gcd(p - 1, k);
        if (ipow(mint(a), (p - 1) / g) != mint(1))
            return NO_SOLUTION;
        a = (i64)ipow(mint(a), inv(k / g, (p - 1) / g));
        unordered_map<i64, int> fac;
        for (auto &f : factors::factorize(g))
            fac[f]++;
        for (auto pp : fac)
            a = pe_root(a, pp.first, pp.second, p);
        return a;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        int k, y, p;
        k = 3;
        cin >> y >> p;
        cout << kth_root_mod::kth_root(y, k, p) << "\n";
    }
}
