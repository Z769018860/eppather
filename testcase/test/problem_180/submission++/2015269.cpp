#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

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

const int MAXN = 2e6 + 10;

int n, d;
int to[MAXN], ml[MAXN], mr[MAXN];
int id[MAXN], st[MAXN], top;
bool vis[MAXN];

mt19937 Rand(10395123);

int main()
{
    #if DEBUG
    #else
    ios::sync_with_stdio(0), cin.tie(0);
    #endif
    Read(n), Read(d);
    for (int i = 0; i < n * d; i++) Read(to[i]), to[i]--;
    for (int i = 0; i < n; i++) id[i] = i, mr[i] = -1;
    shuffle(id, id + n, Rand);
    for (int i = 0; i < n; i++)
    {
        top = 0;
        int x = id[i];
        while (~x)
        {
            int y = to[x * d + Rand() % d];
            while (mr[y] == x) y = to[x * d + Rand() % d];
            while (vis[y]) vis[st[top--]] = 0;
            x = mr[y], vis[st[++top] = y] = 1;
        }
        x = id[i];
        for (int j = 1; j <= top; j++) vis[st[j]] = 0, swap(x, mr[st[j]]);
    }
    for (int i = 0; i < n; i++) ml[mr[i]] = i + 1;
    for (int i = 0; i < n; i++) Write(ml[i], ' ');
    return 0;
}