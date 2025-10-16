#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <stdio.h>
#include <assert.h>
#include <tuple>
#include <algorithm>
#include <vector>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
using namespace std;
typedef long long ll;
typedef __uint128_t lll;
lll rd()
{
    lll k = 0;
    char c = getchar();

    while (c < '0' || c > '9')
        c = getchar();

    while (c >= '0' && c <= '9')
    {
        k = (k << 1) + (k << 3) + (c ^ 48);
        c = getchar();
    }

    return k;
}
void wr(lll x)
{
    if (x > 9)
        wr(x / 10);

    putchar(x % 10 + '0');
}


constexpr pair<long long, long long> inv_gcd(long long a, long long b)
{
    a = a % b;
    if (a < 0)
        a += b;
    if (a == 0)
        return make_pair(b, 0);
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;
    while (t)
    {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    if (m0 < 0)
        m0 += b / s;
    return {s, m0};
}

vector<long long> pre_im(vector<long long> m)
{
    vector<long long> ims;
    long long m0 = 1;
    int n = m.size();
    for (int i = 0; i < n; i++)
    {
        long long m1 = m[i];
        if (m0 < m1)
            swap(m0, m1);
        long long _, im;
        tie(_, im) = inv_gcd(m0, m1);
        ims.push_back(im);
        m0 *= m1;
    }
    return ims;
}

pair<long long, long long> crt(const vector<long long> &r,
                               const vector<long long> &m,
                               const vector<long long> &ims)
{
    assert(r.size() == m.size());
    int n = int(r.size());
    long long r0 = 0, m0 = 1;
    for (int i = 0; i < n; i++)
    {
        long long r1 = r[i], m1 = m[i], im = ims[i];
        if (m0 < m1)
            swap(r0, r1), swap(m0, m1);
        long long x = (r1 - r0) * im % m1;
        r0 += x * m0;
        m0 *= m1;
        if (r0 < 0)
            r0 += m0;
    }
    return {r0, m0};
}

#define PRIME_POWER_BINOMIAL_M_MAX ((1LL << 30) - 1)
#define PRIME_POWER_BINOMIAL_N_MAX 20000000

struct prime_power_binomial
{
    int p, q, M;
    vector<int> fac, ifac, inv;
    int delta;

    using i64 = long long;
    using u64 = unsigned long long;
    u64 iM, ip;

    prime_power_binomial(int _p, int _q) : p(_p), q(_q)
    {
        assert(p <= PRIME_POWER_BINOMIAL_M_MAX);
        assert(_q > 0);
        long long m = 1;
        while (_q--)
        {
            m *= p;
            assert(m <= PRIME_POWER_BINOMIAL_M_MAX);
        }
        M = m;
        iM = u64(-1) / M + 1;
        ip = u64(-1) / p + 1;

        enumerate();
        delta = (p == 2 && q >= 3) ? 1 : M - 1;
    }

    inline i64 modulo_M(u64 n)
    {
        u64 x = u64((__uint128_t(n) * iM) >> 64);
        i64 r = i64(n - x * M);
        if (r < 0)
            r += M;
        return r;
    }

    int modpow(int a, long long e)
    {
        int r = 1;
        while (e)
        {
            if (e & 1)
                r = modulo_M(1LL * r * a);
            a = modulo_M(1LL * a * a);
            e >>= 1;
        }
        return r;
    }

    inline i64 divide_p(u64 n)
    {
        u64 x = u64((__uint128_t(n) * ip) >> 64);
        i64 r = i64(n - x * p);
        if (r < 0)
            x--;
        return i64(x);
    }

    inline pair<i64, int> quorem_p(u64 n)
    {
        u64 x = u64((__uint128_t(n) * ip) >> 64);
        i64 r = i64(n - x * p);
        if (r < 0)
            r += M, x--;
        return make_pair(i64(x), r);
    }

    void enumerate()
    {
        int MX = min<int>(M, PRIME_POWER_BINOMIAL_N_MAX + 10);
        fac.resize(MX);
        ifac.resize(MX);
        inv.resize(MX);
        fac[0] = ifac[0] = inv[0] = 1;
        fac[1] = ifac[1] = inv[1] = 1;
        for (int i = 2; i < MX; i++)
        {
            if (i % p == 0)
            {
                fac[i] = fac[i - 1];
                fac[i + 1] = modulo_M(1LL * fac[i - 1] * (i + 1));
                i++;
            }
            else
            {
                fac[i] = modulo_M(1LL * fac[i - 1] * i);
            }
        }
        ifac[MX - 1] = modpow(fac[MX - 1], M / p * (p - 1) - 1);
        for (int i = MX - 2; i > 1; --i)
        {
            if (i % p == 0)
            {
                ifac[i] = modulo_M(1LL * ifac[i + 1] * (i + 1));
                ifac[i - 1] = ifac[i];
                i--;
            }
            else
            {
                ifac[i] = modulo_M(1LL * ifac[i + 1] * (i + 1));
            }
        }
    }

    long long Lucas(long long n, long long m)
    {
        int res = 1;
        while (n)
        {
            int n0, m0;
            tie(n, n0) = quorem_p(n);
            tie(m, m0) = quorem_p(m);
            if (n0 < m0)
                return 0;
            res = modulo_M(1LL * res * fac[n0]);
            res = modulo_M(1LL * res * ifac[m0]);
            res = modulo_M(1LL * res * ifac[n0 - m0]);
        }
        return res;
    }

    long long C(long long n, long long m)
    {
        if (n < m || n < 0 || m < 0)
            return 0;
        if (q == 1)
            return Lucas(n, m);
        long long r = n - m;
        int e0 = 0, eq = 0, i = 0;
        int res = 1;
        while (n)
        {
            res = modulo_M(1LL * res * fac[modulo_M(n)]);
            res = modulo_M(1LL * res * ifac[modulo_M(m)]);
            res = modulo_M(1LL * res * ifac[modulo_M(r)]);
            n = divide_p(n);
            m = divide_p(m);
            r = divide_p(r);
            int eps = n - m - r;
            e0 += eps;
            if (e0 >= q)
                return 0;
            if (++i >= q)
                eq += eps;
        }
        res = modulo_M(1LL * res * modpow(delta, eq));
        res = modulo_M(1LL * res * modpow(p, e0));
        return res;
    }
};



struct arbitrary_mod_binomial
{
    int mod;
    vector<int> M;
    vector<long long> ims;
    vector<prime_power_binomial> cs;

    arbitrary_mod_binomial(long long md) : mod(md)
    {
        assert(1 <= md);
        assert(md <= PRIME_POWER_BINOMIAL_M_MAX);
        for (int i = 2; i * i <= md; i++)
        {
            if (md % i == 0)
            {
                int j = 0, k = 1;
                while (md % i == 0)
                    md /= i, j++, k *= i;
                M.push_back(k);
                cs.emplace_back(i, j);
                assert(M.back() == cs.back().M);
            }
        }
        if (md != 1)
        {
            M.push_back(md);
            cs.emplace_back(md, 1);
        }
        assert(M.size() == cs.size());

        vector<long long> ms;
        for (auto &c : cs)
            ms.push_back(c.M);
        ims = pre_im(ms);
    }

    long long C(long long n, long long m)
    {
        if (mod == 1)
            return 0;
        vector<long long> rem, d;
        for (int i = 0; i < (int)cs.size(); i++)
        {
            rem.push_back(cs[i].C(n, m));
            d.push_back(M[i]);
        }
        return crt(rem, d, ims).first;
    }
};

#undef PRIME_POWER_BINOMIAL_M_MAX
#undef PRIME_POWER_BINOMIAL_N_MAX

lll T, mod;
lll n, m;

int main()
{
    T = rd(), mod = rd();
    arbitrary_mod_binomial C((ll)mod);
    while (T--)
    {
        n = rd(), m = rd();
        wr(C.C(n, m)), putchar('\n');
    }
}