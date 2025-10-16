#include <bits/stdc++.h>
#define SZ(x) (int) x.size() - 1
#define all(x) x.begin(), x.end()
#define ms(x, y) memset(x, y, sizeof x)
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define DF(i, x, y) for (int i = (x); i >= (y); i--)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template <typename T> void chkmax(T &x, T y) { x = max(x, y); }
template <typename T> void chkmin(T &x, T y) { x = min(x, y); }
template <typename T> void read(T &x) {
	x = 0; int f = 1; char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}
ll n, MOD, T, q;
mt19937_64 mrand(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll l, ll r) { return mrand() % (r - l + 1) + l; }
ll power(ll x, ll y) {
	ll ans = 1;
	for (; y; x = (__int128) x * x % MOD, y >>= 1)
		if (y & 1) ans = (__int128) ans * x % MOD;
	return ans;
}
bool check2(ll n) {
	if (n == 0) return true;
	return power(n, (MOD - 1) / 2) == 1;
}
bool check3(ll n) {
	if (n == 0) return true;
	return power(n, (MOD - 1) / 3) == 1;
}
struct com {
	ll x, y;
};
com operator * (com x, com y) {
	return {(ll) (((__int128) x.x * y.x + (__int128) x.y * y.y % MOD * T) % MOD), (ll) (((__int128) x.x * y.y + (__int128) x.y * y.x) % MOD)};
}
com power(com x, ll y) {
	com ans = {1, 0};
	for (; y; x = x * x, y >>= 1)
		if (y & 1) ans = ans * x;
	return ans;
}
struct con {
	ll x, y, z;
};
con operator * (con x, con y) {
	ll a = 0, b = 0, c = 0;
	a = (a + (__int128) x.x * y.x) % MOD;
	b = (b + (__int128) x.x * y.y) % MOD;
	c = (c + (__int128) x.x * y.z) % MOD;
	b = (b + (__int128) x.y * y.x) % MOD;
	c = (c + (__int128) x.y * y.y) % MOD;
	a = (a + (__int128) x.y * y.z % MOD * T) % MOD;
	c = (c + (__int128) x.z * y.x) % MOD;
	a = (a + (__int128) x.z * y.y % MOD * T) % MOD;
	b = (b + (__int128) x.z * y.z % MOD * T) % MOD;
	return {a, b, c};
}
con power(con x, __int128 y) {
	con ans = {1, 0, 0};
	for (; y; x = x * x, y >>= 1)
		if (y & 1) ans = ans * x;
	return ans;
}
void zhk() {
	read(n), read(MOD);
	q = 3;
	n %= MOD;
	if (!n) {
		puts("0");
		return;
	}
	if (q == 2) {
		if (!check2(n)) {
			puts("0");
			return;
		}
		ll a = 0;
		while (check2(((__int128) a * a - n + MOD) % MOD)) a = rnd(0, MOD - 1);
		T = ((__int128) a * a - n + MOD) % MOD;
		
		cout << power((com) {a, 1}, (MOD + 1) >> 1).x << '\n';
		return;
	}
	if (q == 3) {
		if (MOD == 3) {
			if (n == 1) {
				puts("1");
				return;
			}
			if (n == 2) {
				puts("2");
				return;
			}
		}
		if (MOD % 3 == 2) {
			cout << power(n, (2 * MOD - 1) / 3) << '\n';
			return;
		}
		if (!check3(n)) {
			puts("0");
			return;
		}
		ll a = 0;
		while (check3((n - (__int128) a * a % MOD * a % MOD + MOD) % MOD)) a = rnd(0, MOD - 1);
		T = (n - (__int128) a * a % MOD * a % MOD + MOD) % MOD;
		cout << power((con) {a, 1, 0}, ((__int128) MOD * MOD + MOD + 1) / 3).x << '\n';
		return;
	}
}
signed main() {
	int _ = 1;
	cin >> _;
	while (_--) zhk();
	return 0;
}