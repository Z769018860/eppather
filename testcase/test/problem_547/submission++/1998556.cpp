
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using db = double;
using PII = pair<ll, ll>;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ '0');
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
ll n, m;

namespace Poly
{
    const int mod = 65537;
    const int MAXN_POLY = 3e6 + 10;
    int rev[MAXN_POLY];
    int lim, len;
    ll Qmi_In_Poly(ll a, ll k, ll p)
    {
        ll res = 1;
        while(k)
        {
            if(k & 1) res = res * a % p;
            a = a * a % p;
            k >>= 1;
        }
        return res;
    }

    const ll inv2 = Qmi_In_Poly(2, mod - 2, mod);
    using ll = long long;
    using PII = pair<ll, ll>;

    ll my_read_in_poly()
    {
        ll x = 0, f = 1;
        char ch = getchar();
        while(ch < '0' || ch > '9')
        {
            if(ch == '-') f = -1;
            ch = getchar();
        }
        while(ch >= '0' && ch <= '9')
        {
            x = (x << 3) + (x << 1) + (ch ^ '0');
            ch = getchar();
        }
        return x * f;
    }
    struct poly
    {
        vector<ll> a;
        
        ll & operator [] (int x) {return a[x]; }
        
        int deg() {return int(a.size()) - 1; }
        
        void set_deg(int _deg) {a.resize(_deg + 1); }
        
        poly() {a.clear(); }

        poly(ll x) {this -> set_deg(0); a[0] = x; }
    };

    void read(poly& x, int deg)
    {
        x.set_deg(deg);
        for(int i = 0; i <= deg; i ++ ) x[i] = my_read_in_poly();
    }

    poly operator + (poly a, poly b)
    {
        if(a.deg() < b.deg()) swap(a, b);
        for(int i = 0; i <= b.deg(); i ++ ) a[i] = (a[i] + b[i]) % mod;
        return a;
    }

    poly operator - (poly a, poly b)
    {
        a.set_deg(max(a.deg(), b.deg()));
        for(int i = 0; i <= b.deg(); i ++ ) a[i] = (a[i] - b[i] + mod) % mod;
        return a;
    }

    void Clac_For_The_Rev(int _lim = lim, int _len = len)
    {
        for(int i = 0; i < _lim; i ++ )
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (_len - 1));
    }

    void Init_For_the_Poly_Mul(int up)
    {
        lim = 1, len = 0;
        while(lim <= up) lim <<= 1, len ++;
        Clac_For_The_Rev();
    }

    void NTT(poly &a, int opt, int _lim = lim)
    {
        for(int i = 0; i < _lim; i ++ )
            if(i < rev[i])
                swap(a[i], a[rev[i]]);
        int up = log2(_lim);
        for(int dep = 1; dep <= up; dep ++ )
        {
            int m = 1 << dep;
            ll gn = Qmi_In_Poly(opt == 1 ? 3 : Qmi_In_Poly(3, mod - 2, mod), (mod - 1) / m, mod);
            for(int k = 0; k < _lim; k += m)
            {
                ll g = 1;
                for(int j = 0; j < m / 2; j ++ )
                {
                    ll u = a[j + k];
                    ll t = a[j + k + m / 2] * g % mod;
                    a[j + k] = (u + t) % mod;
                    a[j + k + m / 2] = (u - t + mod) % mod;
                    g = g * gn % mod;
                }
            }
        }
        if(opt == -1)
        {
            ll inv = Qmi_In_Poly(_lim, mod - 2, mod);
            for(int i = 0; i < _lim; i ++ ) a[i] = a[i] * inv % mod;
        }
    }

    poly operator * (poly a, poly b)
    {
        int n = a.deg(), m = b.deg();
        Init_For_the_Poly_Mul(n + m);

        a.set_deg(lim), b.set_deg(lim);
        NTT(a, 1), NTT(b, 1);
        for(int i = 0; i < lim; i ++ ) a[i] = a[i] * b[i] % mod;
        NTT(a, -1);

        a.set_deg(n + m);
        return a;
    }

    poly operator * (poly a, ll b)
    {
        for(int i = 0; i <= a.deg(); i ++ ) a[i] = a[i] * b % mod;
        return a;
    }

    poly operator * (ll b, poly a)
    {
        return a * b;
    }

    poly Inv(poly x, int n = -1)
    {
        if(n == -1) n = x.deg() + 1;
        if(n == 1)
        {
            poly res(Qmi_In_Poly(x[0], mod - 2, mod));
            return res;
        }
        auto b = Inv(x, (n + 1) >> 1);
        
        Init_For_the_Poly_Mul(n << 1);

        static poly h;
        h.set_deg(lim);
        b.set_deg(lim);
        for(int i = 0; i < lim; i ++ ) h[i] = (i < n) ? x[i] : 0;
        
        NTT(h, 1), NTT(b, 1);
        for(int i = 0; i < lim; i ++ ) 
            b[i] = (2 * b[i] % mod - h[i] * b[i] % mod * b[i] % mod + mod) % mod;
        NTT(b, -1);

        b.set_deg(n - 1);
        return b;
    }

    poly Inte(poly x)
    {
        x.set_deg(x.deg() + 1);
        for(int i = x.deg(); i >= 1; i -- ) 
            x[i] = x[i - 1] * Qmi_In_Poly(i, mod - 2, mod) % mod;
        x[0] = 0;
        return x;
    }

    poly Deri(poly x)
    {
        for(int i = 0; i < x.deg(); i ++ )
            x[i] = x[i + 1] * (i + 1) % mod;
        x[x.deg()] = 0;
        x.set_deg(x.deg() - 1);
        return x;
    }

    poly ln(poly x)
    {
        auto res = Inte(Deri(x) * Inv(x));
        res.set_deg(x.deg());
        return res;
    }

    void exp_cdq(int l, int r, poly &f, poly &g)
    {
        if(l == r - 1)
        {
            if(l) f[l] = f[l] * Qmi_In_Poly(l, mod - 2, mod) % mod;
            else f[l] = 1;
            return;
        }

        int mid = l + r >> 1;
        exp_cdq(l, mid, f, g);

        Init_For_the_Poly_Mul((r - l));

        static poly a, b;
        a.set_deg(lim), b.set_deg(lim);
        for(int i = l; i < mid; i ++ ) a[i - l] = f[i];
        for(int i = mid - l; i < lim; i ++ ) a[i] = 0;
        for(int i = 0; i < r - l; i ++ ) b[i] = g[i];
        for(int i = r - l; i < lim; i ++ ) b[i] = 0;

        NTT(a, 1), NTT(b, 1);
        for(int i = 0; i < lim; i ++ ) a[i] = a[i] * b[i] % mod;
        NTT(a, -1);

        for(int i = mid; i < r; i ++ )
            f[i] = (f[i] + a[i - l]) % mod;
        
        exp_cdq(mid, r, f, g);
    }

    poly exp(poly x)
    {
        for(int i = 0; i <= x.deg(); i ++ ) x[i] = x[i] * i % mod;
        poly res;
        res.set_deg(x.deg());
        exp_cdq(0, x.deg() + 1, res, x);
        return res;
    }

    poly pow(poly x, ll k, ll k2 = 0)
    {
        int up = 0;
        while(!x[up]) up ++;
        if(up * k2 > x.deg())
        {
            for(int i = 0; i <= x.deg(); i ++ ) x[i] = 0;
            return x;
        }

        poly b;
        b.set_deg(x.deg() - up);
        ll C = x[up];
        ll invC = Qmi_In_Poly(C, mod - 2, mod);
        for(int i = up; i <= x.deg(); i ++ ) 
            b[i - up] = x[i] * invC % mod;

        b = exp(ln(b) * k);

        up = up * k;
        invC = Qmi_In_Poly(C, k2, mod);
        for(int i = 0; i <= x.deg(); i ++ ) x[i] = 0;
        for(int i = up; i <= x.deg(); i ++ ) 
            x[i] = b[i - up] * invC % mod;

        return x;
    }

    poly sqrt(poly x, int n = -1)
    {
        if(n == -1) n = x.deg() + 1;
        if(n == 1)
        {
            return poly(1);
        }
        auto b = sqrt(x, (n + 1) >> 1);
        
        static poly h;
        b.set_deg(n - 1);
        auto inv = Inv(b);

        Init_For_the_Poly_Mul(n << 1);
        h.set_deg(lim);
        inv.set_deg(lim);
        b.set_deg(lim);
        for(int i = 0; i < lim; i ++ )
            h[i] = (i < n) ? x[i] : 0;
        
        NTT(inv, 1), NTT(b, 1), NTT(h, 1);
        for(int i = 0; i < lim; i ++ )
            b[i] = inv2 * (b[i] + h[i] * inv[i] % mod) % mod;
        NTT(b, -1);
        
        b.set_deg(n - 1);
        return b;
    }

    poly div(poly a, poly b, poly &r)
    {
        int n = a.deg(), m = b.deg();
        poly q;
        
        static poly br;
        q.set_deg(n), br.set_deg(m);
        for(int i = 0; i <= n; i ++ ) q[i] = a[n - i];
        for(int i = 0; i <= m; i ++ ) br[i] = b[m - i];
        br.set_deg(n - m);

        auto inv = Inv(br);

        Init_For_the_Poly_Mul(n << 1);
        q.set_deg(lim), inv.set_deg(lim);
        NTT(q, 1), NTT(inv, 1);
        for(int i = 0; i < lim; i ++ ) q[i] = q[i] * inv[i] % mod;
        NTT(q, -1);

        reverse(q.a.begin(), q.a.begin() + n - m + 1);
        q.set_deg(n - m);

        r = q;
        r.set_deg(lim), b.set_deg(lim);
        NTT(r, 1), NTT(b, 1);
        for(int i = 0; i < lim; i ++ ) r[i] = r[i] * b[i] % mod;
        NTT(r, -1);

        for(int i = 0; i < m; i ++ )
            r[i] = (a[i] - r[i] + mod) % mod;
        
        r.set_deg(m - 1);
        return q;
    }

    poly operator / (poly a, poly b)
    {
        int n = a.deg(), m = b.deg();
        poly q;
        
        static poly br;
        q.set_deg(n), br.set_deg(m);
        for(int i = 0; i <= n; i ++ ) q[i] = a[n - i];
        for(int i = 0; i <= m; i ++ ) br[i] = b[m - i];
        br.set_deg(n - m);

        auto inv = Inv(br);

        Init_For_the_Poly_Mul(n << 1);
        q.set_deg(lim), inv.set_deg(lim);
        NTT(q, 1), NTT(inv, 1);
        for(int i = 0; i < lim; i ++ ) q[i] = q[i] * inv[i] % mod;
        NTT(q, -1);

        reverse(q.a.begin(), q.a.begin() + n - m + 1);
        q.set_deg(n - m);
        return q;
    }

    poly operator % (poly a, poly b)
    {
        poly r;
        div(a, b, r);
        return r;
    }

    
    ll div_at(poly F, poly G, ll k)
    {
        int i;
        for(; k; k >>= 1)
        {
            
            poly R = G;
            for(i = 1; i <= G.deg(); i += 2) R[i] = mod - R[i];
            F = F * R;
            G = G * R;
            for(i = k & 1; i <= F.deg(); i += 2) F[i / 2] = F[i];
            F.set_deg(i / 2 - 1);
            for(i = 0; i <= G.deg(); i += 2) G[i / 2] = G[i];
            G.set_deg(i / 2 - 1);
        }
        return F.deg() >= 0 ? F[0] * Qmi_In_Poly(G[0], mod - 2, mod) % mod : 
                            0ll;
    }

    
    ll Bostan_Mori(poly f, poly a, ll n, ll k)
    {
        f = 1 - f;
        poly g = a * f;
        g.set_deg(k - 1);
        return div_at(g, f, n);
    }
}

using namespace Poly;
ll fact[N], invfact[N];

ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
}

ll C(int n, int m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    return fact[n] * invfact[m] % mod * invfact[n - m] % mod;
}

ll lucas(ll n, ll m)
{
    if(n < mod && m < mod) return C(n, m);
    return lucas(n / mod, m / mod) * C(n % mod, m % mod) % mod;
}

void solve1()
{
    poly f, a;
    f.set_deg(m + 1);
    a.set_deg(m);
    a[0] = 1;
    for(int i = 1; i <= m; i ++ ) a[i] = 2 * a[i - 1] % mod;
    f[1] = 2, f[m + 1] = mod - 1;
    printf("%lld\n", (Bostan_Mori(f, a, n, m + 1) - Bostan_Mori(f, a, n - m, m + 1) + mod) % mod);
}

ll solve2(ll n)
{
    ll res = 0;
    for(int i = 0; i <= n / (m + 1); i ++ )
    {
        res = (res + ((i & 1) ? mod - 1 : 1) * 
            qmi(2, n - i * (m + 1), mod) % mod * 
            lucas(n - i * m, i) % mod) % mod;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("/home/crimson000/OI/in_and_out/in.in", "r", stdin);
        freopen("/home/crimson000/OI/in_and_out/out.out", "w", stdout);
    #endif

    n = read(), m = read();
    if(n < m)
    {
        cout << qmi(2, n, mod) << endl;
        return 0;
    }
    init(mod - 1);

    if(m < (1 << 15)) solve1();
    else 
        cout << (solve2(n) - solve2(n - m) + mod) % mod << endl;

    return 0;
}


