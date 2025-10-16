#include <cstdio>
#include <vector>
#include <algorithm>

#define rep( i, a, b ) for( int i = (a) ; i <= (b) ; i ++ )
#define per( i, a, b ) for( int i = (a) ; i >= (b) ; i -- )

const int mod = 998244353;
const int MAXN = ( 1 << 19 ) + 5;

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

template<typename _T>
inline _T Max( const _T &a, const _T &b ) {
    return a > b ? a : b;
}

typedef std :: vector<int> Poly;

std :: vector<int> oper[MAXN], buf;

Poly dp, tmp;

int N, M;

inline int Qkpow( int, int );
inline int Inv( const int &a ) { return Qkpow( a, mod - 2 ); }
inline int Mul( int x, const int &v ) { return 1ll * x * v % mod; }
inline int Sub( int x, const int &v ) { return ( x -= v ) < 0 ? x + mod : x; }
inline int Add( int x, const int &v ) { return ( x += v ) >= mod ? x - mod : x; }

inline int& MulEq( int &x, const int &v ) { return x = 1ll * x * v % mod; }
inline int& SubEq( int &x, const int &v ) { return ( x -= v ) < 0 ? ( x += mod ) : x; }
inline int& AddEq( int &x, const int &v ) { return ( x += v ) >= mod ? ( x -= mod ) : x; }

inline int Qkpow( int base, int indx ) {
    int ret = 1;
    while( indx ) {
        if( indx & 1 ) MulEq( ret, base );
        MulEq( base, base ), indx >>= 1;
    }
    return ret;
}

namespace Basics {
    const int L = 19, g = 3, phi = mod - 1;

    int w[MAXN];

    inline void NTTInit( const int &n = 1 << L ) {
        w[0] = 1, w[1] = Qkpow( g, phi >> L );
        rep( i, 2, n - 1 ) w[i] = Mul( w[i - 1], w[1] );
    }

    inline void DIF( int *coe, const int &n ) {
        int *wp, p, e, o;
        for( int s = n >> 1 ; s ; s >>= 1 )
            for( int i = 0 ; i < n ; i += s << 1 ) {
                p = ( 1 << L ) / ( s << 1 ), wp = w;
                for( int j = 0 ; j < s ; j ++, wp += p ) {
                    e = coe[i + j], o = coe[i + j + s];
                    coe[i + j] = Add( e, o );
                    coe[i + j + s] = Mul( *wp, Sub( e, o ) );
                }
            }
    }

    inline void DIT( int *coe, const int &n ) {
        int *wp, p, k;
        for( int s = 1 ; s < n ; s <<= 1 )
            for( int i = 0 ; i < n ; i += s << 1 ) {
                p = ( 1 << L ) / ( s << 1 ), wp = w;
                for( int j = 0 ; j < s ; j ++, wp += p )
                    k = Mul( *wp, coe[i + j + s] ),
                    coe[i + j + s] = Sub( coe[i + j], k ),
                    coe[i + j] = Add( coe[i + j], k );
            }
        std :: reverse( coe + 1, coe + n );
        int inv = Inv( n ); rep( i, 0, n - 1 ) MulEq( coe[i], inv );
    }
}

inline Poly operator * ( const Poly &a, const Poly &b ) {
    static int P[MAXN] = {}, Q[MAXN] = {};
    int n = a.size(), m = b.size(), L;
    for( L = 1 ; L <= n + m - 2 ; L <<= 1 );
    rep( i, 0, L - 1 ) P[i] = Q[i] = 0;
    rep( i, 0, n - 1 ) P[i] = a[i];
    rep( i, 0, m - 1 ) Q[i] = b[i];
    Basics :: DIF( P, L );
    Basics :: DIF( Q, L );
    rep( i, 0, L - 1 ) MulEq( P[i], Q[i] );
    Basics :: DIT( P, L );
    return Poly( P, P + n + m - 1 );
}

Poly Divide( const int &l, const int &r ) {
    Poly ret;
    if( l == r ) ret = { Sub( 1, buf[l] ), buf[l] };
    else {
        int mid = ( l + r ) >> 1;
        ret = Divide( l, mid ) * Divide( mid + 1, r );
    }
    return ret;
}

int main() {
    int ans = 0;
    Basics :: NTTInit();
    Read( N ), Read( M );
    rep( i, 1, M ) {
        int a, x, y;
        Read( a ), Read( x ), Read( y );
        oper[a].push_back( Mul( x, Inv( y ) ) );
        AddEq( ans, Mul( x, Inv( y ) ) );
    }
    dp = { 1 }, MulEq( ans, 2 );
    for( int i = 0 ; i <= N + 30 ; i ++ ) {
        buf.swap( oper[i] );
        if( ! buf.empty() )
            dp = dp * Divide( 0, ( int ) buf.size() - 1 );
        while( ! dp.empty() && ! dp.back() ) dp.pop_back();
        int n = dp.size(), m;
        for( int j = 1 ; j < n ; j += 2 ) SubEq( ans, dp[j] );
        tmp.resize( m = ( n + 1 ) / 2, 0 ), tmp.shrink_to_fit();
        rep( j, 0, m - 1 ) tmp[j] = 0;
        rep( j, 0, n - 1 ) AddEq( tmp[j >> 1], dp[j] );
        dp.swap( tmp );
    }
    Write( ans ), putchar( '\n' );
    return 0;
}