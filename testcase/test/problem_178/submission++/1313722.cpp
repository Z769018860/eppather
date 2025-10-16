#include<bits/stdc++.h>
#define L(i, j, k) for(int i = (j); i <= (k); ++i)
#define R(i, j, k) for(int i = (j); i >= (k); --i)
#define ll long long
#define vi vector <int> 
#define sz(a) ((int) (a).size())
#define ull unsigned long long 
using namespace std;
const int N = 1 << 10;
int mod; 
int qpow (int x, int y = mod - 2) {
	int ret = 1;
	for (; y; x = (ll) x * x % mod, y >>= 1) if(y & 1) ret = (ll) ret * x % mod;
	return ret;
}
typedef vector < int > poly;
poly operator + (poly a, poly b) {
	poly ns (max(sz(a), sz(b)));
	L(i, 0, sz(a) - 1) ns[i] = a[i];
	L(i, 0, sz(b) - 1) (ns[i] += b[i]) %= mod;
	return ns;
}
poly operator - (poly a, poly b) {
	poly ns (max(sz(a), sz(b)));
	L(i, 0, sz(a) - 1) ns[i] = a[i];
	L(i, 0, sz(b) - 1) (ns[i] += mod - b[i]) %= mod;
	return ns;
}
poly operator * (poly a, poly b) {
	poly ns (sz(a) + sz(b) - 1);
	L(i, 0, sz(a) - 1) L(j, 0, sz(b) - 1) 
		(ns[i + j] += (ll) a[i] * b[j] % mod) %= mod; 
	return ns;
}
poly operator / (poly a, poly b) { 
	if(sz(a) < sz(b)) a.resize (sz(b) - 1);
	reverse(b.begin(), b.end());
	int n = sz(a), m = sz(b), iv = qpow (b[0]);
	poly ns (sz(a) - sz(b) + 1);
	R(i, n - 1, m - 1) {
		int w = (ll) iv * (mod - a[i]) % mod;
		ns[i - m + 1] = w;
		L(j, 0, m - 1) (a[i - j] += (ll) w * b[j] % mod) %= mod;
	}
	return ns;
}
poly operator % (poly a, poly b) { 
	if(sz(a) < sz(b)) a.resize (sz(b) - 1);
	reverse(b.begin(), b.end());
	int n = sz(a), m = sz(b), iv = qpow (b[0]);
	poly ns (sz(b) - 1);
	R(i, n - 1, m - 1) {
		int w = (ll) iv * (mod - a[i]) % mod;
		L(j, 0, m - 1) (a[i - j] += (ll) w * b[j] % mod) %= mod;
	}
	L(i, 0, sz(b) - 2) ns[i] = a[i];
	return ns;
}

poly Pow (poly a, poly mod, int b) {
	poly ret = {1};
	for (; b; b >>= 1, a = a * a % mod) if(b & 1) ret = ret * a % mod;
	return ret; 
}
poly gcd (poly a, poly b) {
	while (true) {
		while (sz(b) && b.back() == 0) b.pop_back();
		if(!sz(b)) return a;
		a = a % b, swap (a, b);
	}
	return assert (false), vi{};
}
mt19937_64 orz(time(0) ^ clock());
inline int rad (int l, int r) {
	return orz() % (r - l + 1) + l;
}
int n;
int main () {
	ios :: sync_with_stdio(false);
	cin.tie (0); cout.tie (0);
	cin >> n >> mod;
	poly a (n + 1);
	L(i, 0, n) cin >> a[i];
	poly g = Pow (vi {0, 1}, a, mod);
	if(sz(g) <= 1) g.resize (2);
	(g[1] += mod - 1) %= mod;
	vi ns;
	queue < poly > q;
	q.push (gcd (a, g));
	while (sz(q)) {
		poly u = q.front();
		q.pop();
		if(sz(u) == 1) continue ;
		if(sz(u) == 2) {
			ns.push_back((ll) (mod - qpow (u[1])) * u[0] % mod);
			continue;
		}
		poly ret (sz(u) - 1);
		L(i, 0, sz(ret) - 1) ret[i] = rad (0, mod - 1);
		ret = Pow (ret, u, (mod - 1) / 2);
		(ret[0] += mod - 1) %= mod;
		poly r = gcd (ret, u);
		q.push (u / r);
		q.push (r);
	}
	sort(ns.begin(), ns.end());
	ns.erase(unique(ns.begin(), ns.end()), ns.end());
	cout << sz(ns) << '\n';
	for (const int &u : ns) 
		cout << u << ' ';
	return 0;
}
