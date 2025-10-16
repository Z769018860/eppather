#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

#define rep( i, a, b ) for( int i = (a) ; i <= (b) ; i ++ )
#define per( i, a, b ) for( int i = (a) ; i >= (b) ; i -- )

typedef long long LL;

const int mod = 1e9 + 7;
const int MAXN = 1e6 + 20;

template<typename _T>
inline void Read( _T &x ) {
    x = 0; char s = getchar(); bool f = false;
    while( s < '0' || '9' < s ) { f = s == '-', s = getchar(); }
    while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
    if( f ) x = -x;
}

template<typename _T>
inline void Write( _T x ) {
    if( x < 0 ) putchar( '-' ), x = -x;
    if( 9 < x ) Write( x / 10 );
    putchar( x % 10 + '0' );
}

double rt[MAXN];

int prefA[MAXN], prefB[MAXN];
int patA[MAXN], patB[MAXN];
int seq[MAXN], pos[MAXN];
int beg, len;

int A, B, C;

inline int Mul( int x, const int &v ) { return 1ll * x * v % mod; }
inline int Sub( int x, const int &v ) { return ( x -= v ) < 0 ? x + mod : x; }
inline int Add( int x, const int &v ) { return ( x += v ) >= mod ? x - mod : x; }

inline int& MulEq( int &x, const int &v ) { return x = 1ll * x * v % mod; }
inline int& SubEq( int &x, const int &v ) { return ( x -= v ) < 0 ? ( x += mod ) : x; }
inline int& AddEq( int &x, const int &v ) { return ( x += v ) >= mod ? ( x -= mod ) : x; }

inline int Term( const LL &x ) {
    if( x < beg ) return seq[x];
    return seq[( x - beg ) % len + beg];
}

inline void Process( int *ret ) {
    LL l, r; Read( l ), Read( r );
    LL k1 = std :: max( 0ll, ( LL ) ceil( 1. * ( l - beg ) / len ) ),
       k2 = std :: max( 0ll, ( LL ) floor( 1. * ( r - beg ) / len ) );
    while( l < beg + k1 * len && l <= r ) AddEq( ret[Term( l ++ )], 1 );
    while( r >= beg + k2 * len && r >= l ) AddEq( ret[Term( r -- )], 1 );
    int val = ( ( r - l + 1 ) / len ) % mod;
    rep( k, 1, len ) AddEq( ret[seq[beg + k - 1]], val );
}

int main() {
    Read( A ), Read( B ), Read( C ), Read( seq[0] );
    memset( pos, -1, sizeof pos ), pos[seq[0]] = 0;
    for( int i = 1 ; ; i ++ ) {
        seq[i] = ( 1ll * seq[i - 1] * A + B ) % C + 1;
        if( ~ pos[seq[i]] ) {
            beg = pos[seq[i]], len = i - beg;
            break;
        }
        pos[seq[i]] = i;
    }
    Process( patA );
    Process( patB );
    rep( i, 2, C + 1 ) 
        rt[i] = 0.5 * ( i + sqrt( 1. * i * i - 4 ) );
    int ans = 0;
    rep( i, 1, C ) 
        prefA[i] = Add( prefA[i - 1], patA[i] ),
        prefB[i] = Add( prefB[i - 1], patB[i] );
    rep( x, 1, C ) if( patA[x] || patB[x] ) {
        AddEq( ans, Mul( 2, Mul( patA[x], patB[x] ) ) );
        int up = ceil( 1. * C / x + 1. * x / C );
        rep( i, 3, up ) {
            int l = floor( rt[i - 1] * x ),
                r = std :: min( ( int ) floor( rt[i] * x ), C );
            AddEq( ans, Mul( i, Mul( patA[x], Sub( prefB[r], prefB[l] ) ) ) );
            AddEq( ans, Mul( i, Mul( patB[x], Sub( prefA[r], prefA[l] ) ) ) );
        }
    }
    Write( ans ), putchar( '\n' );
    return 0;
}