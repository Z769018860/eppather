#include <bits/stdc++.h>
#define fi first
#define se second

using std :: cin;
using std :: min;
using std :: max;
using std :: cout;
using std :: vector;

constexpr int M = 2005; 
constexpr int INF = 0x3f3f3f3f, mod = 998244353;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef std :: pair < int, int > pii;

inline int read() {
	int f = 1, s = 0; char ch = getchar();
	while(!isdigit(ch)) (ch == '-') && (f = -1), ch = getchar();
	while(isdigit(ch)) s = s * 10 + ch - '0', ch = getchar();
	return f * s;
}
namespace Solver {
	char _st; 
	int n, z[M][M], sz[M], a[M][M], os[M]; 
	inline int qpow(int a, int b, int p) {
		int s = 1; 
		for(int bas = a; b; b >>= 1, bas = (ll)bas * bas % p)
		    if(b & 1) s = (ll)s * bas % p; 
		return s; 
	}
	inline int add(int x, int y) {return (x += y) >= mod ? x - mod : x;}
    inline void Ad(int &x, const int &y) {if((x += y) >= mod) x -= mod;}
    inline void De(int &x, const int &y) {if((x -= y) < 0) x += mod;}
    int id[M], p[M]; 
    inline void gauss() {
    	std :: iota(id + 1, id + n + 1, 1), std :: sort(id + 1, id + n + 1, [] (int x, int y) {return sz[x] < sz[y];}); 
    	for(int i = 1; i <= n; ++i) for(int j = 1; j <= n + 1; ++j) a[i][j] = z[id[i]][j], os[i] += a[i][j] > 0; 
    	for(int i = 1; i <= n; ++i) sz[i] = os[i]; 
    	for(int i = 1; i <= n; ++i) {
    		int x = i; 
    		for(int j = i + 1; j <= n; ++j) if(a[j][i]) {
    			if(!a[x][i] || sz[j] < sz[x]) x = j; 
			}
			std :: swap(a[x], a[i]), std :: swap(sz[x], sz[i]); int inv = qpow(a[i][i], mod - 2, mod), m = 0; 
			for(int j = i; j <= n + 1; ++j) a[i][j] = (ll)a[i][j] * inv % mod, (a[i][j] > 0) && (p[++m] = j, 1); int *f = a[i]; 
			for(int j = i + 1; j <= n; ++j) if(a[j][i]) {
				int t = a[j][i]; 
				for(int k = 1, x; k <= m; ++k) x = p[k], sz[j] -= a[j][x] > 0, a[j][x] = (a[j][x] + (ll)(mod - f[x]) * t) % mod, sz[j] += a[j][x] > 0;  
			}
		}
		for(int i = n; i; --i) {
			for(int j = i + 1; j <= n; ++j) De(a[i][n + 1], (ll)a[j][n + 1] * a[i][j] % mod); 
			a[i][n + 1] = (ll)a[i][n + 1] * qpow(a[i][i], mod - 2, mod) % mod; 
		}
	}
	char _ed;
	inline void mian() {
		fprintf(stderr, "floor memery : %d\n", (&_st - &_ed) >> 20);
		n = read(); for(int i = 1; i <= n; ++i) for(int j = 1; j <= n + 1; ++j) z[i][j] = read(), sz[i] += z[i][j] > 0; 
		gauss(); for(int i = 1; i <= n; ++i) cout << a[i][n + 1] << ' '; 
	}
} ;

int main()
{

	Solver :: mian();
	return 0;
}

