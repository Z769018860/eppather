#include<bits/stdc++.h>
#define fo(i, x, y) for(int i = x, _b = y; i <= _b; i ++)
#define ff(i, x, y) for(int i = x, _b = y; i <  _b; i ++)
#define fd(i, x, y) for(int i = x, _b = y; i >= _b; i --)
#define ll long long
#define pp printf
#define hh pp("\n")
using namespace std;

const int N = 122474500;

int mu[N], s[N];
int p[7000000], p0;

ll n, m, sq;

void sieve(int n) {
	fo(i, 2, n) {
		if(!s[i]) p[++ p0] = i, mu[i] = -1;
		for(int j = 1; i * p[j] <= n; j ++) {
			int k = i * p[j];
			s[k] = 1;
			if(i % p[j] == 0) { mu[k] = 0; break;}
			mu[k] = -mu[i];
		}
	}
	mu[1] = 1;
	fo(i, 1, n) s[i] = s[i - 1] + (mu[i] != 0), mu[i] += mu[i - 1];
}

int cc = 0;

ll calc(ll n) {
	if(n <= sq) return s[n];
	int m = sqrt(n);
	ll s = 0;
	for(int i = 1, j; i <= m; i = j + 1) {
		ll x = n / i / i;
		j = sqrt(n / x);
		s += (mu[j] - mu[i - 1]) * x;
	}
	return s;
}

int main() {
	scanf("%lld %lld", &n, &m);
	if(n > m) swap(n, m);
	sq = sqrt(n);
	sieve(sq);
	ll v1 = 0, ans = 0;
	for(ll i = 1, j; i <= n; i = j + 1) {
		ll x = sqrt(n / i), y = sqrt(m / i);
		j = n / x / x;
		j = min(j, m / y / y);
		ll v2 = calc(j);
		ans += (v2 - v1) * x * y;
		v1 = v2;
	}
	pp("%lld\n", ans);
}
