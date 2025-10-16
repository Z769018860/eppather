#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n;
long long a[N], ans;

int main()
{
	ios :: sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		ans += a[i] * a[i];
	}
	sort(a + 1, a + 1 + n);
	ans -= a[1] * a[2] + a[n - 1] * a[n];
	int f = n & 1;
	for (int i = 2; i < n - f; i += 2)
	{
		ans -= a[i] * a[i + 2];
	}
	f ^= 1;
	for (int i = n - f; i > 1; i -= 2)
	{
		ans -= a[i] * a[i - 2];
	}
	cout << 2 * ans;
	return 0;
}