#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
typedef __uint128_t u128;
char eof_flag;
char rd(u128 *s)
{
    if (eof_flag)
        return 0;
    u128 k = 0; 
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
    
    k = (c == '-') ? 0 : (c ^ 48);
    c = getchar();
    while (c >= '0' && c <= '9')
        k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
    if (c == EOF)
        eof_flag = 1;
    (*s) = k;
    
    return 1;
}
u128 rd_from_str(const char *s)
{
    int len = strlen(s);
    u128 k = 0;
    for (int i = 0; i < len; ++i)
        k = (k << 1) + (k << 3) + (s[i] ^ 48);
    return k;
}

u128 qpow(u128 a, u128 b, u128 m)
{
    a %= m;
    u128 res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
const u128 jp[30] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
#define MR_THRESHOLD rd_from_str("1000000000000000000000000000000000000")
#define MR_INDEX_THRESHOLD 20
#define THRESHOLD_20 rd_from_str("1543267864443420616877677640751301")
#define THRESHOLD_18 rd_from_str("564132928021909221014087501701")
#define THRESHOLD_16 rd_from_str("59276361075595573263446330101")
#define THRESHOLD_15 rd_from_str("6003094289670105800312596501")
#define THRESHOLD_14 rd_from_str("3317044064679887385961981")
#define THRESHOLD_13 rd_from_str("318665857834031151167461")
#define THRESHOLD_12 (u128)3825123056546413051ull
#define THRESHOLD_9 (u128)341550071728321ull
int range_for_prime_test(u128 n)
{
    if (n >= MR_THRESHOLD)
        return 40;
    else if (n >= THRESHOLD_20)
        return 20;
    else if (n >= THRESHOLD_18)
        return 18;
    else if (n >= THRESHOLD_16)
        return 16;
    else if (n >= THRESHOLD_15)
        return 15;
    else if (n >= THRESHOLD_14)
        return 14;
    else if (n >= THRESHOLD_13)
        return 13;
    else if (n >= THRESHOLD_12)
        return 12;
    else if (n >= THRESHOLD_9)
        return 9;
    else 
        return 8;
}
int check_prime(u128 n)
{
    
    if (n == 1 || ((!(n & 1)) && n > 2))
        return 0;
    int lim = range_for_prime_test(n);
    int use_probabilistic = n > 20;
    if (!use_probabilistic)
        for (int i = 0; i <= lim; ++i)
            if (n % jp[i] == 0)
                return n == jp[i];
    u128 r = n - 1, x, y;
    int e = 0;

    while (~r & 1)
        r >>= 1, ++e;

    for (int i = 0; i < lim; ++i)
    {
        u128 p = use_probabilistic ? ((rand() % (n - 2)) + 2) : jp[i];

        x = qpow(p, r, n);

        for (int t = 0; t < e && x > 1; ++t)
        {
            y = (x * x) % n;

            if (y == 1 && x != n - 1)
                return 0;

            x = y;
        }

        if (x != 1)
            return 0;
    }

    return 1;
}

u128 n;
int main()
{
    while (rd(&n))
        putchar(check_prime(n) ? 'Y' : 'N'), putchar('\n');
}