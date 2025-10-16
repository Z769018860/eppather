#include <iostream>

typedef long long ll;
typedef double lf;


struct IO
{
    #define MAXSIZE (1 << 20)
    #define isdigit(x) (x >= '0' && x <= '9')
    char buf[MAXSIZE], *p1, *p2;
    char pbuf[MAXSIZE], *pp;
    #if DEBUG
    #else
    IO() : p1(buf), p2(buf), pp(pbuf) {}
    ~IO() {fwrite(pbuf, 1, pp - pbuf, stdout);}
    #endif
    #define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) ? ' ' : *p1++)
    #define blank(x) (x == ' ' || x == '\n' || x == '\r' || x == '\t')

    template <typename T>
    void Read(T &x)
    {
        #if DEBUG
        std::cin >> x;
        #else
        bool sign = 0; char ch = gc(); x = 0;
        for (; !isdigit(ch); ch = gc())
            if (ch == '-') sign = 1;
        for (; isdigit(ch); ch = gc()) x = x * 10 + (ch ^ 48);
        if (sign) x = -x;
        #endif
    }
    void Read(char *s)
    {
        #if DEBUG
        std::cin >> s;
        #else
        char ch = gc();
        for (; blank(ch); ch = gc());
        for (; !blank(ch); ch = gc()) *s++ = ch;
        *s = 0;
        #endif
    }
    void Read(char &c) {for (c = gc(); blank(c); c = gc());}

    void Push(const char &c)
    {
        #if DEBUG
        putchar(c);
        #else
        if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
        *pp++ = c;
        #endif
    }
    template <typename T>
    void Write(T x)
    {
        if (x < 0) x = -x, Push('-');
        static T sta[35];
        int top = 0;
        do sta[top++] = x % 10, x /= 10; while (x);
        while (top) Push(sta[--top] ^ 48);
    }
    template <typename T>
    void Write(T x, char lst) {Write(x), Push(lst);}
} IO;
#define Read(x) IO.Read(x)
#define Write(x, y) IO.Write(x, y)
#define Put(x) IO.Push(x)

using namespace std;

const int MAXN = 3e5 + 10, mod = 998244353, Inv3 = 332748118;

int n, m, a[MAXN], b[MAXN];
int len, rev[MAXN];

inline ll Qpow(ll x, int y) {ll res = 1; while (y) (y & 1) && (res = res * x % mod), x = x * x % mod, y >>= 1; return res;}
inline void NTT(int *f, bool tp)
{
    for (int i = 0; i < len; i++)
        if (rev[i] < i) swap(f[rev[i]], f[i]);
    for (int l = 1; l < len; l <<= 1)
    {
        ll w = Qpow((tp ? Inv3 : 3), (mod - 1) / l / 2), p, x, y;
        for (int i = 0; i < len; i += l << 1)
        {
            p = 1;
            for (int j = 0; j < l; j++)
            {
                x = f[i | j], y = f[i | j | l] * p % mod;
                f[i | j] = (x + y >= mod ? x + y - mod : x + y), f[i | j | l] = (x - y < 0 ? x - y + mod : x - y);
                p = p * w % mod;
            }
        }
    }
    if (tp)
    {
        ll mul = Qpow(len, mod - 2);
        for (int i = 0; i < len; i++) f[i] = (ll)f[i] * mul % mod;
    }
}

int main()
{
    #if DEBUG
    #else
    ios::sync_with_stdio(0), cin.tie(0);
    #endif
    Read(n), Read(m);
    for (int i = 0; i <= n; i++) Read(a[i]);
    for (int i = 0; i <= m; i++) Read(b[i]);
    len = 1;
    while (len <= n + m) len <<= 1;
    for (int i = 1; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    NTT(a, 0), NTT(b, 0);
    for (int i = 0; i < len; i++) a[i] = (ll)a[i] * b[i] % mod;
    NTT(a, 1);
    for (int i = 0; i <= n + m; i++) cout << a[i] << ' '; cout << '\n';
    return 0;
}