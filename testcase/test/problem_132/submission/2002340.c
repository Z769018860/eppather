
#include <stdio.h>
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
typedef long long i64;
#define N 1000010
i64 rd()
{
    i64 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = 0;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + (ch ^ '0');
        ch = getchar();
    }
    return f ? x : -x;
}
void wr(i64 x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        wr(x / 10);
    putchar((x % 10) ^ '0');
}
int n, q;
int op, l, r, val;
int lc(int x) { return x << 1; }
int rc(int x) { return (x << 1) | 1; }
struct node
{
    i64 sum, tag_add;
} tr[N << 2];
void build(int u, int l, int r)
{
    if (l == r)
        tr[u].sum = rd();
    else
    {
        int m = (l + r) >> 1;
        build(lc(u), l, m), build(rc(u), m + 1, r);
        tr[u].sum = tr[lc(u)].sum + tr[rc(u)].sum;
    }
}
void add(int u, int l, int r, int L, int R, int val)
{
    if (L > r || R < l)
        return;
    if (l <= L && R <= r)
    {
        tr[u].sum += 1ll * (R - L + 1) * val;
        tr[u].tag_add += val;
        return;
    }
    int M = (L + R) >> 1;
    add(lc(u), l, r, L, M, val), add(rc(u), l, r, M + 1, R, val);
    tr[u].sum = tr[lc(u)].sum + tr[rc(u)].sum + tr[u].tag_add * (R - L + 1);
}
i64 sum(int u, int l, int r, int L, int R)
{
    if (L > r || R < l)
        return 0;
    if (l <= L && R <= r)
        return tr[u].sum;
    int M = (L + R) >> 1;
    return tr[u].tag_add * (min(R, r) - max(L, l) + 1) + sum(lc(u), l, r, L, M) + sum(rc(u), l, r, M + 1, R);
}
int main()
{
    n = rd(), q = rd();
    build(1, 1, n);
    while (q--)
    {
        op = rd(), l = rd(), r = rd();
        if (op & 1)
            val = rd(), add(1, l, r, 1, n, val);
        else
            wr(sum(1, l, r, 1, n)), putchar('\n');
    }
}