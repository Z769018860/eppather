#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#define maxn 1000010
typedef long long i64;
const int mod = 998244353;
int add(int a, int b) { return (a + b >= mod) ? (a + b - mod) : (a + b); }
int mul(int a, int b) { return 1ll * a * b % mod; }
int rd()
{
    int k = 0, f = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            f = 0;
        c = getchar();
    }
    while (isdigit(c))
    {
        k = (k << 1) + (k << 3) + (c ^ 48);
        c = getchar();
    }
    return f ? k : -k;
}
int c[maxn];
int a[maxn];
int n;
int fac, ans;
int lowbit(int c) { return c & (-c); }
void bit_init(int N)
{
    n = N;
    for (int i = 0; i <= n; ++i)
        c[i] = 0;
}
void bit_add(int loc, int v)
{
    while (loc <= n)
        c[loc] += v, loc += lowbit(loc);
}
int bit_sum(int loc)
{
    int ret = 0;
    while (loc)
        ret += c[loc], loc -= lowbit(loc);
    return ret;
}
int bit_query(int l, int r)
{
    if (l > r)
        return 0;
    else
        return bit_sum(r) - bit_sum(l - 1);
}
int main()
{
    n = rd();
    for (int i = 1; i <= n; ++i)
        a[i] = rd();
    fac = ans = 1;
    for (int i = n; i; --i)
    {
        ans = add(ans, mul(fac, bit_query(1, a[i] - 1)));
        fac = mul(fac, n - i + 1);
        bit_add(a[i], 1);
    }
    printf("%d", ans);
}