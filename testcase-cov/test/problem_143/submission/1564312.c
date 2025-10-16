#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
typedef __int128 lll;
char eof_flag;
char rd(lll *s)
{
    if (eof_flag)
        return 0;
    lll k = 0, f = 1;
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
lll qpow(lll a, lll b, lll m)
{
    a %= m;
    lll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

int millerRabin(lll n)
{
    if (n < 3 || n % 2 == 0)
        return n == 2;
    lll a = n - 1, b = 0;
    while (!(a & 1))
        a >>= 1, ++b;
    lll i, j;
    for (i = 1; i <= 12; ++i)
    {
        lll x = rand() % (n - 2) + 2;
        lll v = qpow(x, a, n);
        if (v == 1)
            continue;
        for (j = 0; j < b; ++j)
        {
            if (v == n - 1)
                break;
            v = v * v % n;
        }
        if (j >= b)
            return 0;
    }
    return 1;
}
lll n;
int main()
{
    srand(time(NULL));
    while(rd(&n))
    	putchar(millerRabin(n) ? 'Y' : 'N'), putchar('\n');
}