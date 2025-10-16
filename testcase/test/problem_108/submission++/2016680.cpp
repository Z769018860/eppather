#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,n,m) for(int i=(n);i<=(m);i++)
#define ROF(i,n,m) for(int i=(n);i>=(m);i--)
#define REP(i,n) for(int i=0;i<(n);i++)
#define SZ(v) v.size()
#define pb push_back
template < typename A , typename B>
inline bool chmax(A &x, B y) { return (x < y ? (x = y, true) : false); }
template < typename A , typename B>
inline bool chmin(A &x, B y) { return (x > y ? (x = y, true) : false); }
const int N = 1e6 + 5;
const double PI = acos(-1.);
int n, m;
struct cp {
	double x, y;
	cp(double x = 0, double y = 0): x(x), y(y) {}
	cp operator + (cp A) { return cp(x + A.x, y + A.y); }
	cp operator - (cp A) { return cp(x - A.x, y - A.y); }
	cp operator * (cp A) { return cp(x * A.x - y * A.y, x * A.y + y * A.x); }
};
int r[N << 2];
cp f[N << 2], g[N << 2];
void FFT(cp *a, int lim, int opt) {
	REP(i, lim) {
		if(i < r[i]) swap(a[i], a[r[i]]);
	}
	for(int i = 1; i < lim; i <<= 1) {
		cp wn(cos(PI / i), opt * sin(PI / i));
		for(int j = 0; j < lim; j += (i << 1)) {
			cp w(1, 0);
			for(int k = 0; k < i; k++, w = w * wn) {
				cp x = a[j + k];
				cp y = a[j + k + i] * w;
				a[j + k] = x + y;
				a[j + k + i] = x - y;
			}
		}
	}
	if(opt == 1) return;
	REP(i, lim) {
		a[i].x /= lim;
	}
}
void solve() {
	cin >> n >> m;
	FOR(i, 0, n) {
		ll x; cin >> x;
		f[i] = cp(x, 0);
	}
	FOR(i, 0, m) {
		ll x; cin >> x;
		g[i] = cp(x, 0);
	}
	int lim = 1, l = 0;
	while(lim <= (n + m)) lim <<= 1, l++;
	REP(i, lim) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1)); 
	FFT(f, lim, 1);
	FFT(g, lim, 1);
	REP(i, lim) f[i] = f[i] * g[i];
	FFT(f, lim, -1);
	FOR(i, 0, n + m) {
		cout << (ll)(f[i].x + 0.5) << " ";
	}
	cout << endl;
}
int main() {
	ios :: sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	solve();
	return 0;
}