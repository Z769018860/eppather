#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
#define ll long long
#define _1 first
#define _2 second
#define _mp make_pair
#define _pb push_back
#define MAX_N 1023454

using namespace std;

ll read()
{
    char c = 0, v = 0;
    ll x = 0;
    do
    {
        c = getchar();
        if(c == '-')
            v = 1;
    } while(c < '0' || c > '9');
    do
    {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    } while(c >= '0' && c <= '9');
    if(!v)
        return x;
    return -x;
}

const ll P = 998244353ll;

struct obv
{
    ll a, b, c, d; 
    obv() { ; }
    obv(ll _a, ll _b, ll _c, ll _d) : a(_a), b(_b), c(_c), d(_d) { ; }
    obv(ll t) : a(t), b(1), c(1), d(0) { ; }
    pair<ll, ll> operator () (ll x)
    {
        x = (x % P + P) % P;
        return _mp((a * x + b) % P, (c * x + d) % P);
    }

    obv operator () (obv o)
    {
        obv ans;
        ans.a = (a * o.a + b * o.c) % P;
        ans.b = (a * o.b + b * o.d) % P;
        ans.c = (c * o.a + d * o.c) % P;
        ans.d = (c * o.b + d * o.d) % P;
        return ans;
    }
};

struct node
{
    int l, r;
    obv f;
    node *lc, *rc;
    void pUp() { f = lc->f(rc->f); }
    void update(int x, ll k)
    {
        if(l == r)
        {
            f = obv(k);
            return;
        }
        int mid = (l + r) >> 1;
        if(x <= mid)
            lc->update(x, k);
        else
            rc->update(x, k);
        pUp();
    }

    obv query(int L, int R)
    {
        
        if(l == L && r == R)
            return f;
        int mid = (l + r) >> 1;
        if(R <= mid)
            return lc->query(L, R);
        if(L > mid)
            return rc->query(L, R);
        return (lc->query(L, mid))(rc->query(mid + 1, R));
    }
} _pool[MAX_N * 2], *null = _pool;

int _tot;

node* make(int l, int r)
{
    _pool[++_tot] = (node){l, r, obv(1), null, null};
    return _pool + _tot;
}

node* bT(int l, int r)
{
    node* p = make(l, r);
    if(l == r)
        return p;
    int mid = (l + r) >> 1;
    p->lc = bT(l, mid);
    p->rc = bT(mid + 1, r);
    p->pUp();
    return p;
}

int n, m, k, vegetable;
ll a[MAX_N];
ll ansx, ansy;
node* t;




void opp1(ll x)
{
    a[++k] = x;
    t->update(k, x);
}

pair<ll, ll> opp2(int l, int r)
{
    
    ll v = a[r];
    
    if(l == r)
        return _mp(v, 1);
    
    obv f = t->query(l, r - 1);
    
    return f(v);
}

int main()
{
    
    
    
    n = read();
    m = read();
    vegetable = read();
    t = bT(1, n + m);
    
    for(int i = 1; i <= n; i++)
    {
        ll x = read();
        opp1(x);
    }
    for(int i = 1; i <= m; i++)
    {
        int op = read();
        if(op == 1)
        {
            ll x = read();
            if(vegetable)
                x ^= ansx ^ ansy;
            opp1(x);
        }
        else if(op == 2)
        {
            ll l = read();
            ll r = read();
            if(vegetable)
                l ^= ansx ^ ansy, r ^= ansx ^ ansy;
            pair<ll, ll> ans = opp2(l, r);
            ansx = ans._1, ansy = ans._2;
            printf("%lld %lld\n", ansx, ansy);
        }
    }
    return 0;
}