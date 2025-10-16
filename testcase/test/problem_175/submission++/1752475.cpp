#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <algorithm>
#include <vector>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
typedef unsigned u32;
typedef long long i64;
using namespace std;
int rd()
{
    int k = 0;
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
void wr(int x)
{
    if (x > 9)
        wr(x / 10);
    putchar(x % 10 + '0');
}

int trim(int x, int mod) { return (x >= 0) ? (x % mod) : (mod - (((-x) % mod) ? ((-x) % mod) : mod)); }
int add(int a, int b, int mod) { return ((u32)a + b >= mod) ? ((u32)a + b - mod) : (a + b); }
int sub(int a, int b, int mod) { return (a < b) ? (a - b + mod) : (a - b); }
int mul(int a, int b, int mod) { return 1ll * a * b % mod; }
int quick_pow(int x, i64 p, int mod)
{
    int ans = 1;
    while (p)
    {
        if (p & 1)
            ans = mul(ans, x, mod);
        x = mul(x, x, mod);
        p >>= 1;
    }
    return ans;
}
struct tup
{
    int a, b, c;
    tup(int _a = 0, int _b = 0, int _c = 0) : a(_a), b(_b), c(_c) {}
};

tup mul(const tup& x, const tup& y, int key, int mod)
{
    tup ret;
    ret.a = mul(x.a, y.a, mod);
    ret.a = add(ret.a, mul(mul(x.b, y.c, mod), key, mod), mod);
    ret.a = add(ret.a, mul(mul(x.c, y.b, mod), key, mod), mod);

    ret.b = mul(x.a, y.b, mod);
    ret.b = add(ret.b, mul(x.b, y.a, mod), mod);
    ret.b = add(ret.b, mul(mul(x.c, y.c, mod), key, mod), mod);

    ret.c = mul(x.a, y.c, mod);
    ret.c = add(ret.c, mul(x.b, y.b, mod), mod);
    ret.c = add(ret.c, mul(x.c, y.a, mod), mod);
    return ret;
}
tup quick_pow(tup a, i64 p, int key, int mod)
{
    tup ret = tup(1, 0, 0);
    while (p)
    {
        if (p & 1)
            ret = mul(ret, a, key, mod);
        a = mul(a, a, key, mod);
        p >>= 1;
    }
    return ret;
}
int exgcd(int a, int b, int &x, int &y) 
{
    if (!b) 
    {
        x = 1, y = 0;
        return a;
    }
    int q = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return q;
}

vector<int> cbrt_mod(int A, int P)
{
    vector<int> ret;
    if (A == 0)
        ret.push_back(0), ret.push_back(P);
    else if (P == 3)
        ret.push_back(A);
    else if (P % 3 != 1) 
    {
        int x = 0, y = 0;
        exgcd(3, P - 1, x, y);
        x = trim(x, P - 1);
        ret.push_back(quick_pow(A, x, P));
    }
    else if (quick_pow(A, (P - 1) / 3, P) == 1)
    {
        int w = 0;
        for (int i = 2; i < P; i++)
            if ((w = quick_pow(i, (P - 1) / 3, P)) != 1)
                break;
        int w2 = mul(w, w, P);
        int x = 0, key = 0;
        for (x = 2; x < P; ++x)
        {
            key = sub(mul(x, mul(x, x, P), P), A, P);
            if (quick_pow(key, (P - 1) / 3, P) != 1)
                break;
        }
        int ans = quick_pow(tup(x, P - 1, 0), (1ll * P * P + P + 1) / 3, key, P).a;
        ret.push_back(ans), ret.push_back(mul(ans, w, P)), ret.push_back(mul(ans, w2, P));
        sort(ret.begin(), ret.end());
    }
    return ret;
}
int main()
{
    srand(time(0));
    int T = rd();
    while (T--)
    {
        int A = rd(), P = rd();
        vector<int> ans = cbrt_mod(A, P);
        for (int i = 0; i < ans.size(); ++i)
            if (mul(ans[i], mul(ans[i], ans[i], P), P) != A)
                puts("Wrong Answer");
        wr(ans.empty() ? 0 : ans[rand() % ans.size()]), putchar('\n');
    }
}