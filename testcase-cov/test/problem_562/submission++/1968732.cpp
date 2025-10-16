#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a), en = (b); i <= en; ++i)
#define Rof(i, a, b) for(int i = (a), en = (b); i >= en; --i)
#define Tra(u, i) for(int i = hd[u]; ~i; i = e[i].net)
#define cst const
#define LL long long
#define DD double
#define LD long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define inf 0x3f3f3f3f
#define Inf 0x3f3f3f3f3f3f3f3f
#define eps 1e-12
using namespace std;

template<class T>
T fp(T x, LL y) {
    assert(y >= 0);
    T asi = 1;
    while(y) {
        if(y & 1) asi *= x;
        x *= x;
        y >>= 1;
    }
    return asi;
}

template <class T>
void read(T &x) {
    char ch;
    bool ok;
    for(ok = 0, ch = getchar(); !isdigit(ch); ch = getchar()) if(ch == '-') ok = 1;
    for(x = 0; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
    if(ok) x = -x;
}

template<int P>
struct Mint {
    int x;
    Mint() { x = 0; }
    Mint(int _x) : x{ norm(_x % P) } {}
    int norm(int _x) {
        if(_x < 0) _x += P;
        if(_x >= P) _x -= P;
        return _x;
    }
    Mint inv() { return fp(*this, P - 2); }
    Mint operator - () { return { P - x }; }
    Mint& operator += (Mint _x) & {
        x = norm(x + _x.x);
        return *this;
    }
    Mint& operator -= (Mint _x) & {
        x = norm(x - _x.x);
        return *this;
    }
    Mint& operator *= (Mint _x) & {
        x = 1ll * x * _x.x % P;
        return *this;
    }
    Mint& operator /= (Mint _x) & { return *this *= _x.inv(); }
    friend Mint operator + (Mint _x, Mint _y) { return _x += _y; }
    friend Mint operator - (Mint _x, Mint _y) { return _x -= _y; }
    friend Mint operator * (Mint _x, Mint _y) { return _x *= _y; }
    friend Mint operator / (Mint _x, Mint _y) { return _x /= _y; }
    friend bool operator == (Mint _x, Mint _y) { return _x.x == _y.x; }
};

const int P = 998244353;
using Z = Mint<P>;

int T;
const int a = 917504;
Z Q = fp(Z{ 19190506 }, P - 2);
LL n, m;

#define maxn 2000000
Z ff[maxn + 5], iff[maxn + 5];

Z fac[a + 5], ifac[a + 5];
Z C(LL x, LL y) {
    assert(x >= 0 && y >= 0);
    if(x < y) return 0;
    if(x < a && y < a) return fac[x] * ifac[y] * ifac[x - y];
    if(x / a != y / a + (x - y) / a) return 0;
    
    return C(x % a, y % a) * ff[x / a] * iff[y / a] * iff[x / a - y / a];
}

int main() {
    
    fac[0] = 1;
    For(i, 1, a - 1) fac[i] = fac[i - 1] * (1 - fp(Q, i));
    ifac[a - 1] = fp(fac[a - 1], P - 2);
    Rof(i, a - 2, 0) ifac[i] = ifac[i + 1] * (1 - fp(Q, i + 1));

    ff[0] = 1;
    For(i, 1, maxn) ff[i] = ff[i - 1] * i;
    iff[maxn] = fp(ff[maxn], P - 2);
    Rof(i, maxn - 1, 0) iff[i] = iff[i + 1] * (i + 1);

    read(T);
    while(T--) {
        read(n); read(m);
        LL tem = m % 2 ? (m - 1) / 2 % (P - 1) * (m % (P - 1)) % (P - 1) : m / 2 % (P - 1) * ((m - 1) % (P - 1)) % (P - 1);
        LL mx = m % 2 ? (2 * n - m + 1) / 2 % (P - 1) * (m % (P - 1)) % (P - 1) : m / 2 % (P - 1) * ((2 * n - m + 1) % (P - 1)) % (P - 1);
        
        printf("%d\n", (fp(Q, (tem + m - mx + P - 1) % (P - 1)) * C(n, m)).x);
    }
    return 0;
}
