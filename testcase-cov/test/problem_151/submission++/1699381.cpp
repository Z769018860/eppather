#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int p = 998244353, inv2 = 499122177, g = 3, K = 31596;
const int N = 5.3e5, L = 1 << 19;
namespace Math
{
int inc(int x, int y) { return x + y < p ? x + y : x + y - p; }
int dec(int x, int y) { return x - y < 0 ? x - y + p : x - y; }
int mul(ll x, ll y) { return x * y % p; }
int qpow(int x, int y)
{
    int res = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1) res = mul(res, x);
    return res;
}
} 
using namespace Math;
namespace GetSqrt
{
unordered_map<int, int> mp;
int BSGS(int a)
{
    mp.clear();
    for (int j = 1, prod = a; j <= K; j++) prod = mul(prod, g), mp[prod] = j;
    int t = qpow(g, K);
    for (int i = 1, prod = 1; i <= K; i++)
    {
        prod = mul(prod, t);
        if (mp.count(prod)) return i * K - mp[prod];
    }
    return -1;
}
int calc(int x)
{
    if (!x) return 0;
    int res = qpow(g, BSGS(x) / 2);
    return min(res, p - res);
}
} 
namespace Init
{
int w[N], rev[N], inv[N];
int getrev(int n)
{
    int t = 1, lg = 0;
    while (t < n) t *= 2, lg++;
    for (int i = 0; i < t; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
    return t;
}
void getW()
{
    w[0] = 1, w[1] = qpow(g, (p - 1) / L);
    for (int i = 2; i < N; i++) w[i] = mul(w[i - 1], w[1]);
}
void getinv()
{
    inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = mul(inv[p % i], p - p / i);
}
} 
using namespace Init;
struct poly : public vector<int>
{
    int time() const { return size() - 1; }
    poly(int n = 0, int c = 0)
    {
        resize(n);
        if (c) at(0) = c;
    }
    poly operator+=(const poly &x)
    {
        int n = time(), m = x.time();
        if (n < m) resize(m + 1);
        for (int i = 0; i <= m; i++) at(i) = inc(at(i), x[i]);
        return *this;
    }
    poly operator+(const poly &x)
    {
        poly res = *this;
        res += x;
        return res;
    }
    poly operator-=(const poly &x)
    {
        int n = time(), m = x.time();
        if (n < m) resize(m + 1);
        for (int i = 0; i <= m; i++) at(i) = dec(at(i), x[i]);
        return *this;
    }
    poly operator-(const poly &x)
    {
        poly res = *this;
        res -= x;
        return res;
    }
    void NTT(poly &a, int n, bool I)
    {
        for (int i = 0; i < n; i++)
            if (i < rev[i]) ::swap(a[i], a[rev[i]]);
        for (int len = 1; len * 2 <= n; len *= 2)
            for (int l = 0; l < n; l += len * 2)
            {
                int t = L / len / 2;
                for (int i = l, o = 0; i < l + len; i++, o += t)
                {
                    int c = mul(w[o], a[i + len]);
                    a[i + len] = dec(a[i], c), a[i] = inc(a[i], c);
                }
            }
        if (I)
        {
            reverse(a.begin() + 1, a.end());
            int inv = qpow(n, p - 2);
            for (int i = 0; i < n; i++) a[i] = mul(a[i], inv);
        }
    }
    void multi(poly &res, poly a, poly b)
    {
        int n = a.time(), m = b.time();
        int t = getrev(n + m + 1);
        a.resize(t), b.resize(t), res.resize(t);
        NTT(a, t, 0), NTT(b, t, 0);
        for (int i = 0; i < t; i++) res[i] = mul(a[i], b[i]);
        NTT(res, t, 1);
        res.resize(n + m + 1);
    }
    poly operator*=(const poly &x)
    {
        multi(*this, *this, x);
        return *this;
    }
    poly operator*(const poly &x)
    {
        poly res;
        multi(res, *this, x);
        return res;
    }
    poly operator*=(int x)
    {
        int n = time();
        for (int i = 0; i <= n; i++) at(i) = mul(at(i), x);
        return *this;
    }
    poly operator*(int x)
    {
        poly res = *this;
        res *= x;
        return res;
    }
    poly inv(int n)
    {
        poly res(1, qpow(at(0), p - 2));
        for (int k = 1; k < n; k *= 2)
        {
            int len = min(min(n, k * 2), time() + 1);
            poly a(len);
            copy(begin(), begin() + len, a.begin());
            int t = getrev(a.time() + k * 2 - 1);
            a.resize(t), res.resize(t);
            NTT(a, t, 0), NTT(res, t, 0);
            for (int i = 0; i < t; i++)
                res[i] = dec(mul(2, res[i]), mul(mul(res[i], res[i]), a[i]));
            NTT(res, t, 1);
            res.resize(k * 2);
        }
        res.resize(n);
        return res;
    }
    poly der()
    {
        int n = time();
        poly res(n);
        for (int i = 0; i < n; i++) res[i] = mul(at(i + 1), i + 1);
        return res;
    }
    poly itg()
    {
        int n = size();
        poly res(n + 1);
        for (int i = 0; i < n; i++) res[i + 1] = mul(at(i), Init::inv[i + 1]);
        return res;
    }
    poly ln(int n)
    {
        poly res = (der() * inv(n)).itg();
        res.resize(n);
        return res;
    }
    poly exp(int n)
    {
        poly res(1, 1);
        for (int k = 1; k < n; k *= 2)
        {
            int len = min(min(n, k * 2), time() + 1);
            poly a(len);
            copy(begin(), begin() + len, a.begin());
            res = (poly(1, 1) - res.ln(min(n, k * 2)) + a) * res;
            res.resize(k * 2);
        }
        res.resize(n);
        return res;
    }
    poly sqrt(int n)
    {
        poly res(1, GetSqrt::calc(at(0)));
        for (int k = 1; k < n; k *= 2)
        {
            int len = min(min(n, k * 2), time() + 1);
            poly a(len);
            copy(begin(), begin() + len, a.begin());
            res = (res + a * res.inv(min(n, k * 2))) * inv2;
            res.resize(k * 2);
        }
        res.resize(n);
        return res;
    }
    poly power(int k, int n) { return (ln(n) * k).exp(n); }
};
void exgcd(int a, int b, int &x, int &y)
{
    if (!b) return x = 1, y = 0, void();
    exgcd(b, a % b, y, x);
    y -= x * (a / b);
}
int n, t, inv3;
int solve(int a, int b)
{
    int t = GetSqrt::BSGS(b);
    int x, y;
    exgcd(a, p - 1, x, y);
    x = 1ll * (x % (p - 1) + p - 1) * t % (p - 1);
    return qpow(g, x);
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    getinv(), getW();
    cin >> n;
    n++;
    poly a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    t = qpow(a[0], p - 2);
    for (int i = 1; i < n; i++) a[i] = mul(a[i], t);
    t = a[0], a[0] = 1;
    a = a.power(qpow(3, p - 2), n);
    t = solve(3, t);
    for (int i = 0; i < n; i++) cout << mul(t, a[i]) << ' ';
    return 0;
}