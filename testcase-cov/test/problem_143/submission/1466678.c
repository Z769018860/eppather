#include <stdio.h>



#define TRUE    1
#define FALSE   0





typedef long long   I64;
typedef unsigned long long   U64;
typedef __int128    I128;
typedef unsigned __int128    U128;




#define WITNESS_NUM 9
int Witness[WITNESS_NUM] ={ 2, 3, 5, 7, 11, 13, 17, 19, 23};






U64 binPower( U64 base, U64 power, U64 mod)
{
    U64 r = 1;

    base %= mod;

    while( power ) {
        if( power & 1 )
            r = (U128)r * base % mod;
        base = (U128)base * base % mod;

        power >>= 1;
    }

    return r;
}


int millerRabin(U64 n )
{
    U64 a;
    U64 x;
    int i, j;
    int pflag;

    int r = 0;
    U64 d = n - 1;
    while ( (d&1) == 0) {
        d >>= 1;
        r ++;
    }

    for ( i=0; i < WITNESS_NUM; i ++ ) {
        a = Witness[i];
        if( a == n )   return TRUE;

        x = binPower( a, d, n);
        if( x == 1 || x == (n-1) )  continue;

        pflag = FALSE;
        for( j = 1; j < r; j ++ ) {
            x = (U128)x * x % n;
            if( x == (n-1) ) {
                pflag = TRUE;
                break;
            }
        }

        if( !pflag )    return FALSE;
    }

    return TRUE;
}


int isPrime( U64 num )
{
    U64 t;

    if( num == 1)   return FALSE;
    if( (num == 2) || (num == 3) || (num == 5))
        return TRUE;

    if( (num & 0x01) == 0 ) return FALSE;   
    t = num % 6;
    if(  (t !=1) && (t != 5) )  return FALSE;

    if( millerRabin(num)) return TRUE;
    return FALSE;
}

int main(void) 
{
    U64 num;

    while( EOF != scanf("%lld", &num) ) {
        if( isPrime(num))
            puts("Y");
        else
            puts("N");
    }
    
    return 0;
}

