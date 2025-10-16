#include <stdio.h>
#define N ((1 << 12) | 5)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
typedef long long i64;
char eof_flag;
char rd(int *s)
{
    if (eof_flag)
        return 0;
    int k = 0, f = 1;
    char c = getchar();
    while (c != '-' && (c < '0' || c > '9'))
    {
        if (c == EOF)
        {
            eof_flag = 1;
            return 0;
        }
        c = getchar();
    }
    f = (c == '-') ? -1 : 1;
    k = (c == '-') ? 0 : (c ^ 48);
    c = getchar();
    while (c >= '0' && c <= '9')
        k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
    if (c == EOF)
        eof_flag = 1;
    (*s) = f > 0 ? k : -k;
    return 1;
}
void wr(i64 x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        wr(x / 10);
    putchar(x % 10 + '0');
}
i64 bit2d[N][N];
int n, m;
int op, x_1, y_1, x_2, y_2, k;
int lowbit(int x) { return x & -x; }
void _modify(i64 x, i64 y, i64 z)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= m; j += lowbit(j))
            bit2d[i][j] += z;      
}
void modify(int x_1, int y_1, int x_2, int y_2, i64 val)
{
    _modify(x_1, y_1, val), _modify(x_2 + 1, y_2 + 1, val);
    _modify(x_2 + 1, y_1, -val), _modify(x_1, y_2 + 1, -val);
}
i64 sum(i64 x, i64 y)
{
    i64 ret = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            ret += bit2d[i][j];
    return ret;
}
int main()
{
    rd(&n), rd(&m);
    while (rd(&op))
    {
        rd(&x_1), rd(&y_1);
        if (op & 1)
            rd(&x_2), rd(&y_2), rd(&k), modify(x_1, y_1, x_2, y_2, k);
        else
            wr(sum(x_1, y_1)), putchar('\n');
    }
}