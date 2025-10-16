#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>

using u32 = uint32_t;
using u64 = uint64_t;


u32 mod, minv, r2n;

void setmod(u32 n)
{
    mod = n; minv = n;
    for (int i = 0; i < 4; i++) minv *= (2 - n * minv);
    r2n = -u64(n) % n;
}

u32 redc(u64 x)
{
    u32 ret = (x - u64(u32(x) * minv) * mod) >> 32;
    if (ret >> 31) ret += mod;
    return ret;
}

struct field
{
    u32 x;
    
    field() : x(0) {}
    field(u32 x) : x(redc(u64(x) * r2n)) {}

    field& operator+=(const field& r)
    {
        x += r.x; if (x >= mod) x -= mod;
        return *this;
    }
    field operator+(const field& r) const
    {
        return field(*this) += r;
    }

    field& operator-=(const field& r)
    {
        if (x < r.x) x += mod; x -= r.x;
        return *this;
    }
    field operator-(const field& r) const
    {
        return field(*this) -= r;
    }

    field& operator*=(const field& r)
    {
        x = redc(u64(x) * r.x);
        return *this;
    }
    field operator*(const field& r) const
    {
        return field(*this) *= r;
    }

    u32 lift() const
    {
        return redc(x);
    }
    bool zero() const
    {
        return x == 0;
    }
};

field modexp(field a, u32 k)
{
    field r(1);
    while (k)
    {
        if (k & 1) r *= a;
        a *= a;
        k >>= 1;
    }
    return r;
}

field inv(field a)
{
    return modexp(a, mod - 2);
}

using poly = std::vector<field>;

poly mul(const poly& a, const poly& b)
{
    if (a.empty() || b.empty()) return {};
    int n = a.size() - 1, m = b.size() - 1;
    poly ret(n + m + 1);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            ret[i + j] += a[i] * b[j];
    return ret;
}

std::pair<poly, poly> divmod(const poly& a, const poly& b)
{
    int n = a.size() - 1, m = b.size() - 1;
    if (n < m)
    {
        poly q; return {q, a};
    }
    poly q(n - m + 1), r(a);
    field invt = inv(b.back());
    while (r.size() >= b.size())
    {
        int d = r.size() - b.size();
        field t = r.back() * invt;
        q[d] += t;
        for (int i = 0; i <= m; i++)
            r[i + d] -= b[i] * t;
        while (r.size() && r.back().zero())
            r.pop_back();
    }
    return {q, r};
}

poly div(const poly& a, const poly& b)
{
    return divmod(a, b).first;
}
poly rem(const poly& a, const poly& b)
{
    return divmod(a, b).second;
}

poly modexp(const poly& a, u32 k, const poly& mod)
{
    if (k == 0) return {1};
    poly t = modexp(a, k >> 1, mod);
    t = rem(mul(t, t), mod);
    if (k & 1) t = rem(mul(t, a), mod);
    return t;
}

poly gcd(const poly& a, const poly& b)
{
    poly x(a), y(b);
    while (y.size())
    {
        x = rem(x, y);
        std::swap(x, y);
    }
    return x;
}

std::vector<u32> roots;
std::mt19937 rnd;

void solve(poly f, u32 p)
{
    if (f.size() == 1) return;
    if (f.size() == 2)
    {
        field root = 0; root -= f[0] * inv(f[1]); roots.push_back(root.lift());
        return;
    }
    poly r(f.size() - 1);
    for (auto& a : r) a = rnd();
    r = modexp(r, p >> 1, f);
    r[0] -= field(1);
    while (r.size() && r.back().zero()) r.pop_back();
    if (!r.size()) solve(f, p);
    poly g = gcd(r, f);
    solve(g, p);
    solve(div(f, g), p);
}

int main()
{
    u32 n, p; scanf("%u %u", &n, &p);
    setmod(p);

    poly f;
    for (int i = 0; i <= n; i++)
    {
        u32 a; scanf("%u", &a); f.emplace_back(a);
    }

    poly x{0, 1};
    poly xp = modexp(x, p, f);
    xp.resize(f.size());
    xp[1] -= field(1);
    while (xp.size() && xp.back().zero()) xp.pop_back();
    f = gcd(f, xp);

    solve(f, p);

    std::sort(roots.begin(), roots.end());
    auto end = std::unique(roots.begin(), roots.end());
    printf("%lu\n", std::distance(roots.begin(), end));
    for (auto it = roots.begin(); it != end; it++)
        printf("%u ", *it);
}
