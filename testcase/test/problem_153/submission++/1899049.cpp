#include <bits/stdc++.h>
using namespace std;

const int NR = 1.4e5+10;
const int MR = 5e6+10;
const int p = 998244353;
int n, m, k, x;
long long inv[NR], a[MR];

void fmt(long long *a, int rev)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j <= n; j++)
			if ((j >> i) & 1) 
				a[j] = (a[j] + rev * a[j ^ (1 << i)]) % p;
}

int main()
{
	cin >> m >> n >> k;
	inv[1] = 1;
	for (int i = 2; i <= k; i++)
		inv[i] = -p / i * inv[p % i] % p;
	for (int i = 1; i <= n; i++)
		cin >> x, a[x]++;
	n = (1 << m) - 1;
	fmt(a, 1);
	for (int i = 0; i <= n; i++)
	{
		long long t = a[i], cnt = a[i];
		for (int j = 2; j <= k; j++)
			a[i] = ((a[i] + (cnt = cnt * (t - j + 1) % p * inv[j] % p)) % p + p) % p;
	}
	fmt(a, -1);
	cout << (a[n] + p) % p << endl;
	return 0;
}