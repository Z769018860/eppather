#include <cstdio>
#include <vector>
#include <utility>

#define rep( i, a, b ) for( int i = (a) ; i <= (b) ; i ++ )
#define per( i, a, b ) for( int i = (a) ; i >= (b) ; i -- )

typedef long long LL;

const int MAXLOG = 35;

template<typename _T>
inline void Read( _T &x ) {
	x = 0; char s = getchar(); bool f = false;
	while( ! ( '0' <= s && s <= '9' ) ) { f = s == '-', s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s ^ '0' ), s = getchar(); }
	if( f ) x = -x;
}

template<typename _T>
inline void Write( _T x ) {
	if( x < 0 ) putchar( '-' ), x = -x;
	if( 9 < x ) Write( x / 10 );
	putchar( x % 10 + '0' );
}

inline int Qkpow( int, LL, const int& );
inline int Inv( const int&, const int& );

struct PrimePower {
	int p, e, mod;
	std :: vector<int> prod;

	PrimePower(): p( 1 ), e( 0 ), mod( 1 ), prod() {}
	
	inline void Init( const int &P, const int &E ) {
		p = P, e = E, mod = 1;
		rep( i, 1, e ) mod *= p;
		prod.reserve( mod + 1 ), prod.push_back( 1 );
		rep( i, 1, mod ) {
			prod.push_back( prod.back() );
			if( i % P ) prod[i] = 1ll * prod[i] * i % mod;
		}
	}

	std :: pair<int, int> Decompose( const LL &n ) {
		if( n <= 0 ) return { 0, 1 };
		std :: pair<int, int> tmp( Decompose( n / p ) );
		return std :: make_pair( tmp.first + n / mod, 1ll * tmp.second * prod[n % mod] % mod );
	}

	inline LL Legendre( LL n ) const {
		LL ret = 0;
		while( n )
			ret += n /= p;
		return ret;
	}

	inline int Query( LL n, LL m ) {
		std :: pair<int, int>
			up( Decompose( n ) ),
			lef( Decompose( m ) ),
			rig( Decompose( n - m ) );
		LL idx = Legendre( n ) - Legendre( m ) - Legendre( n - m );
		return 1ll * Qkpow( p, idx, mod ) * Qkpow( prod[mod], up.first - lef.first - rig.first, mod ) % mod *
			   up.second % mod * Inv( lef.second, mod ) % mod * Inv( rig.second, mod ) % mod;
	}
};

PrimePower sub[MAXLOG];
int coe[MAXLOG], tot = 0;

int mod;

inline int Exgcd( const int &a, const int &b, int &x, int &y ) {
	if( ! b ) return x = 1, y = 0, a;
	int d = Exgcd( b, a % b, y, x );
	y -= x * ( a / b ); return d;
}

inline int Qkpow( int base, LL indx, const int &mod ) {
	int ret = 1;
	while( indx ) {
		if( indx & 1 ) ret = 1ll * ret * base % mod;
		base = 1ll * base * base % mod, indx >>= 1;
	}
	return ret;
}

inline int Inv( const int &a, const int &b ) {
	static int x, y; Exgcd( a, b, x, y );
	return ( x % b + b ) % b;
}

inline void Init( int x ) {
	for( int i = 2 ; i * i <= x ; i ++ )
		if( ! ( x % i ) ) {
			int e = 0;
			while( ! ( x % i ) ) x /= i, e ++;
			sub[++ tot].Init( i, e );
		}
	if( x > 1 ) sub[++ tot].Init( x, 1 );
	rep( i, 1, tot ) 
		coe[i] = 1ll * Inv( mod / sub[i].mod, sub[i].mod ) * ( mod / sub[i].mod ) % mod;
}

inline int Binom( const LL &n, const LL &m ) {
	int ret = 0;
	rep( i, 1, tot ) 
		( ret += 1ll * coe[i] * sub[i].Query( n, m ) % mod ) %= mod;
	return ret;
}

int main() {
	int T; 
	Read( T ), Read( mod );
	Init( mod );
	while( T -- ) {
		LL n, m;
		Read( n ), Read( m );
		Write( Binom( n, m ) ), putchar( '\n' );
	}
	return 0;
}