#include<iostream>

typedef long long ll;

using namespace std;
const int p = 998244352;
ll qpow(ll a, ll b, ll mod)
{
	ll ans = 1;
	ll base = a;

	while (b)
	{
		if (b & 1)
			ans *= base, ans %= mod;
		base *= base;
		base %= mod;
		b >>= 1;
	}
	return ans % mod;
}
int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll a, t;

	cin >> a >> t;
	while (t--) {
		ll b; cin >> b;
		cout << qpow(a, b, p) << " ";
	}
	return 0;
}
