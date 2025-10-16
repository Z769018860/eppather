


#include <stdio.h>
#include <stdlib.h>


#define TRUE    1
#define FALSE   0





typedef long long   I64;
typedef unsigned long long   U64;





#define WITNESS_NUM 9
int Witness[WITNESS_NUM] ={ 2, 3, 5, 7, 11, 13, 17, 19, 23};



U64 binMul( U64 a, U64 b, U64 mod)
{
    U64 r = 0;

    while( b ){
        if( b & 1)
            r = (r + a) % mod;
        
        a = (a + a)%mod;

        b >>= 1;
    }

    return r;
}

U64 binPower( U64 base, U64 power, U64 mod)
{
    U64 r = 1;

    base %= mod;

    while( power ) {
        if( power & 1 )
            r = binMul( r, base, mod);

        base = binMul( base, base, mod);

        power >>= 1;
    }

    return r;
}



int checkComposite( U64 n, U64 a, U64 d, int r)
{
    U64 x;
    int i;

    x = binPower( a, d, n);
    if( x == 1 || x == (n-1) )  return FALSE;

    for ( i = 1; i < r; i ++ ) {
        
        x = binMul( x, x, n);

        if( x == (n - 1) ) return FALSE;
    }

    return TRUE;
}


int millerRabin(U64 n )
{
    int r = 0;
    U64 a;
    int i;

    U64 d = n - 1;
    while ( (d&1) == 0) {
        d >>= 1;
        r ++;
    }

    for ( i=0; i < WITNESS_NUM; i ++ ) {
        a = Witness[i];
        if( a == n )   return TRUE;

        if( checkComposite(n, a, d, r )  )  return FALSE;
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


