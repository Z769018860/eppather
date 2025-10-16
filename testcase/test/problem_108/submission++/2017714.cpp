#include <iostream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <string>
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
#include <cstring>

using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using db = double;
using ld = long double;
using pii = std::pair<int, ll>;

constexpr int L = (1 << 22);
constexpr int N = L + 10;
constexpr int g = 3;
constexpr int MOD = 998244353;

int add(const int &a, const int &b) { return a + b < MOD ? a + b : a + b - MOD; }
int dim(const int &a, const int &b) { return a - b > 0 ? a - b : a - b + MOD; }
int mul(const int &a, const int &b) { return (ll)a * b % MOD; }

int qpow(int a, int b)
{
    int res = 1;
    for (; b; b >>= 1, a = mul(a, a))
        if (b & 1) res = mul(res, a);
    return res;
}

int rev[N];

int getrev(const int &n)
{
    int len = 1, t = 0;

    while (len < n)
    {
        len <<= 1;
        t++;
    }

    for (int i = 1; i < len; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (t - 1));
    
    return len;
}

struct poly : std::vector<int>
{
    poly() {}
    poly(const int &n) { resize(n); }
    poly(std::initializer_list<int> I) { assign(I); }

    void NTT(poly &a, const int &n, const int &sgn)
    {
        for (int i = 0; i < n; i++)
            if (i < rev[i]) std::swap(a[i], a[rev[i]]);
        
        for (int len = 1; len < n; len <<= 1)
        {
            int wi = qpow(g, (MOD - 1) / (len << 1));

            if (sgn == -1)
                wi = qpow(wi, MOD - 2);

            for (int l = 0; l < n; l += len * 2)
            {
                for (int i = l, w = 1; i < l + len; i++, w = mul(w, wi))
                {
                    int g = a[i], h = mul(w, a[i + len]);
                    a[i] = add(g, h), a[i + len] = dim(g, h);
                }
            }
        }

        if (sgn == -1)
        {
            int t = qpow(n, MOD - 2);
            for (int i = 0; i < n; i++)
                a[i] = mul(a[i], t);
        }
    }

    poly operator*(poly b)
    {
        poly a = *this, res;

        int n = a.size(), m = b.size();
        int len = getrev(n + m - 1);

        a.resize(len), b.resize(len), res.resize(len);
        NTT(a, len, 1), NTT(b, len, 1);

        for (int i = 0; i < len; i++)
            res[i] = mul(a[i], b[i]);
        
        NTT(res, len, -1);
        res.resize(n + m - 1);

        return res;
    }
} a, b;

int n, m;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;

    a.resize(n + 1), b.resize(m + 1);

    for (int i = 0; i <= n; i++)
        std::cin >> a[i];
    
    for (int i = 0; i <= m; i++)
        std::cin >> b[i];

    poly c = a * b;

    for (auto &&v : c)
        std::cout << v << ' ';

    return 0;
}
