#include<iostream>
#include<vector>
using namespace std;
using ll = long long;
ll qpow(ll a, ll b, ll mod)
{
	ll res = 1, pows = a;
	while (b != 0)
	{
		if (b % 2 == 1)
			res = (res * pows) % mod;
		pows = (pows * pows) % mod;
		b /= 2;
	}
	return res;
}
int main()
{
	ll mod = 1e9 + 7;
	ll n, k;
	cin >> n >> k;
	vector<int> np(n + 1), minpri(n + 1), minpripow(n + 1), sigma(n + 1);
	vector<ll> primes;
	for (ll i = 2; i <= n; i++)
	{
		if (!np[i])
		{
			primes.push_back(i);
			minpri[i] = i;
			minpripow[i] = i;
		}
		for (ll p : primes)
		{
			if (i * p > n)
				break;
			ll j = p * i;
			np[j] = true;
			minpri[j] = p;
			if (i % p == 0)
			{
				minpripow[j] = minpripow[i] * p;
				break;
			}
			minpripow[j] = p;
		}
	}
	ll res = 1;
	for (ll i = 2; i <= n; i++)
	{
		if (!np[i])
			sigma[i] = (1 + qpow(i, k, mod)) % mod;
		else if (minpripow[i] == i)
			sigma[i] = (sigma[i / minpri[i]] + qpow(i, k, mod)) % mod;
		else
			sigma[i] = ((ll)sigma[i / minpripow[i]] * sigma[minpripow[i]]) % mod;
		res = (res + sigma[i]) % mod;
	}
	cout << res;
	return 0;
}