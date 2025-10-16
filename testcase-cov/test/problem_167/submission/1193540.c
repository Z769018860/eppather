#include <ctype.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef long long I;
typedef char C;
typedef double F;

#define MN 1000000



#define IO 10000
C _ibuf[IO], _obuf[IO];
C *_i = _ibuf, *_o = _obuf;

FILE *_is, *_os;
#define IS stdin
#define OS stdout

void init_IO(void)
{
    fread(_ibuf, IO, sizeof(C), IS);
}

void end_IO(void)
{
    fwrite(_obuf, _o - _obuf, sizeof(C), OS);
}

C getC(void)
{
    if (_i == _ibuf + IO)
    {
        memset(_ibuf, 0, sizeof(_ibuf));
        fread(_ibuf, IO, sizeof(C), IS);
        _i = _ibuf;
    }

    return *_i++;
}

void putC(C ch)
{
    if (_o == _obuf + IO)
    {
        fwrite(_obuf, IO, sizeof(C), OS);
        _o = _obuf;
    }

    *_o++ = ch;
}

I getI(void)
{
    I num = 0, fac = 1;
    C ch = getC();

    while (!isdigit(ch))
    {
        if (ch == '-')
            fac = -1;
        ch = getC();
    }

    while (isdigit(ch))
    {
        num = num * 10 + ch - '0';
        ch = getC();
    }

    return num * fac;
}

void putI(I num)
{
    if (num < 0)
    {
        putC('-');
        num = -num;
    }

    if (num < 10)
    {
        putC(num + '0');
        return;
    }

    putI(num / 10);
    putC(num % 10 + '0');
}

void readS(C *str)
{
    C ch = getC();
    
    while (!isgraph(ch))
        ch = getC();

    while (isgraph(ch))
    {
        *str++ = ch;
        ch = getC();
    }
}

void putS(C *str)
{
    while (*str != '\0')
    {
        putC(*str++);
    }
}



#define RN (MN + 5)
I n;
I ai[RN];

void input(void)
{
    n = getI();

    for (I i = 1; i <= n; i++)
    {
        ai[i] = getI();
    }
}



#define LOWBIT(i) ((i) & -(i))

I bit[RN];
I size;

void init_bit(I s)
{
    size = s;
    
    for (I i = 1; i <= size; i++)
    {
        bit[i] = LOWBIT(i);
    }
}

void add_bit(I pos, I val)
{
    for (I i = pos; i <= size; i += LOWBIT(i))
    {
        bit[i] += val;
    }
}

I get_bit(I pos)
{
    I ret = 0;

    for (I i = pos; i; i -= LOWBIT(i))
    {
        ret += bit[i];
    }

    return ret;
}



#define MOD 998244353
I fac[RN];

void solve(void)
{
    fac[0] = 1;
    for (I i = 1; i <= n; i++)
    {
        fac[i] = fac[i - 1] * i % MOD;
    }

    init_bit(n);
    I ans = 1;
    for (I i = 1; i <= n; i++)
    {
        ans += get_bit(ai[i] - 1) * fac[n - i];
        ans %= MOD;
        add_bit(ai[i], -1);
    }

    putI(ans);
}



int main(void)
{
    init_IO();

    input();

    solve();

    end_IO();

    return 0;
}

#ifdef __cplusplus
}
#endif 