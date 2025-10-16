#include <cstdio>
#include <vector>

#define rep( i, a, b ) for( int i = (a) ; i <= (b) ; i ++ )
#define per( i, a, b ) for( int i = (a) ; i >= (b) ; i -- )

typedef long long LL;

const int MAXN = 1e6 + 5, MAXP = 30;

template<typename _T>
void read( _T &x ) {
    x = 0; char s = getchar(); bool f = false;
    while( s < '0' || '9' < s ) { f = s == '-', s = getchar(); }
    while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
    if( f ) x = -x;
}

template<typename _T>
void write( _T x ) {
    if( x < 0 ) putchar( '-' ), x = -x;
    if( 9 < x ) write( x / 10 );
    putchar( x % 10 + '0' );
}

inline int Inv( const LL, const int );
inline int Qkpow( int, LL, const int );

struct Remainder {
    std :: vector<int> pref;
    int mod, prm, idx;

    struct RetType {
        LL allIdx; int fac, mdl;
    
        RetType(): allIdx( 0 ), fac( 0 ), mdl( 1 ) {}
        RetType( LL A, int F, int M ): allIdx( A ), fac( F ), mdl( M ) {}

        inline RetType operator + ( const RetType &a ) const {  
            return RetType( allIdx + a.allIdx, 1ll * fac * a.fac % mdl, mdl );
        }
    };
    
    Remainder(): pref(), mod( 1 ), prm(), idx() {}

    void Init( const int p, const int e ) {
        prm = p, idx = e, mod = 1;
        rep( i, 1, e ) mod *= prm;
        pref.reserve( mod + 1 ), pref[0] = 1;
        rep( i, 1, mod ) {
            pref[i] = pref[i - 1];
            if( i % prm ) pref[i] = 1ll * pref[i] * i % mod;
        }
    }

    RetType Recurse( const LL n ) {
        if( n < prm ) return RetType( 0, pref[n], mod );
        return Recurse( n / prm ) + RetType( n / mod, pref[n % mod], mod );
    }

    int Factorial( const LL n ) {
        RetType ret = Recurse( n );
        return 1ll * Qkpow( pref[mod], ret.allIdx, mod ) * ret.fac % mod;
    }

    LL GetIndx( LL x ) {
        LL ret = 0;
        for( ; x ; ret += ( x /= prm ) );
        return ret;
    }

    int Binom( const LL n, const LL m ) {
        if( n < m ) return 0;
        int facN = Factorial( n ),
            facM = Factorial( m ),
            facN_M = Factorial( n - m );
        return 1ll * facN * Inv( facM, mod ) % mod * Inv( facN_M, mod ) % mod *
               Qkpow( prm, GetIndx( n ) - GetIndx( m ) - GetIndx( n - m ), mod ) % mod;
    }
};

Remainder rem[MAXP];
int coe[MAXP];
int tot = 0;

int mod;

inline int Qkpow( int base, LL indx, const int mod ) {
    int ret = 1;
    while( indx ) {
        if( indx & 1 ) ret = 1ll * ret * base % mod;
        base = 1ll * base * base % mod, indx >>= 1;
    }
    return ret;
}

inline int Exgcd( const int a, const int b, int &x, int &y ) {
    if( ! b ) return x = 1, y = 0, a;
    int d = Exgcd( b, a % b, y, x );
    y -= x * ( a / b ); return d;
}

inline int Inv( const LL a, const int mod ) {
    int x, y; Exgcd( a % mod, mod, x, y );
    return ( x % mod + mod ) % mod;
}

void Init() {
    int x = mod;
    for( int i = 2 ; 1ll * i * i <= x ; i ++ )
        if( ! ( x % i ) ) {
            int idx = 0;
            while( ! ( x % i ) ) x /= i, idx ++;
            rem[++ tot].Init( i, idx );
            coe[tot] = Inv( mod / rem[tot].mod, rem[tot].mod );
        }
    if( x > 1 ) {
        rem[++ tot].Init( x, 1 );
        coe[tot] = Inv( mod / x, x );
    }
}

int Binom( const LL n, const LL m ) {
    int ret = 0;
    rep( i, 1, tot ) {
        int tmp = rem[i].Binom( n, m );
        ( ret += 1ll * tmp * ( mod / rem[i].mod ) % mod * coe[i] % mod ) %= mod;
    }
    return ret;
}

int main() {
    int T;
    read( T ), read( mod );
    Init();
    while( T -- ) {
        LL n, m;
        read( n ), read( m );
        write( Binom( n, m ) ), putchar( '\n' );
    }
    return 0;
}