#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

const int maxn = 1e6 + 5;

vector<int> c[1005];
int p[maxn], s[maxn], q[maxn], X[maxn];
bool a[maxn], vis[maxn];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int T;
	cin >> T;
	int n, k, sum = 0;
	cin >> n >> k;
	if (k > n / k || n % k) return cout << "No\n", 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> X[i];
		a[i] = (bool)(X[i] % k);
		sum += !a[i];
	}
	if (sum < 2 * k) return cout << "No\n", 0;
	if (a[1] || a[n]) return cout << "No\n", 0;
	
	int m1 = 0, m2 = 0, m3 = 0;
	for (int i = 1; i <= n; i++) if (m1 < k && !a[i]) p[++m1] = i, vis[i] = 1;
	for (int i = n; i; i--) if (m2 < k && !a[i]) s[++m2] = i, vis[i] = 1;
	for (int i = 1; i <= n; i++) if (!vis[i]) q[++m3] = i;
	p[k + 1] = n + 1;
	
	bool fl = true;
	int C = 1;
	for (int i = 1; i <= k; i++)
	{
		int l = p[i], r = s[k - i + 1];
		c[i].emplace_back(l);
		while (C <= m3 && l <= q[C] && q[C] <= r && c[i].size() < k - 1) c[i].push_back(q[C++]);
		if (c[i].size() < k - 1)
		{
			fl = false;
			break;
		}
		while (C <= m3 && q[C] < p[i + 1] && q[C] <= r) c[i].emplace_back(q[C++]);
		while (C <= m3 && c[i].size() % k != k - 1 && q[C] <= r) c[i].emplace_back(q[C++]);
		if (c[i].size() % k != k - 1)
		{
			fl = false;
			break;
		}
		c[i].emplace_back(r);
	}
	
	if (fl)
	{
		cout << "Yes\n" << k << "\n";
		for (int i = 1; i <= k; i++)
		{
			cout << c[i].size() << " ";
			for (int j = 0; j < c[i].size(); j++) cout << c[i][j] << " ";
			cout << "\n";
		}
		return 0;
	}
	
	for (int i = 1; i <= k; i++) c[i].clear();
	
	C = 1;
	c[1].emplace_back(1);
	while (C <= m3 && q[C] < p[2]) c[1].emplace_back(q[C++]);
	for (int i = 2; i <= k; i++)
	{
		int l = p[i], r = s[k - i + 2];
		c[i].emplace_back(l);
		while (C <= m3 && l <= q[C] && q[C] <= r && c[i].size() < k - 1) c[i].emplace_back(q[C++]);
		if (c[i].size() < k - 1) return cout << "No\n", 0;
		while (C <= m3 && q[C] < p[i + 1]) c[1].emplace_back(q[C++]);
		c[i].emplace_back(r);
	}
	while (C <= m3) c[1].emplace_back(q[C++]);
	c[1].emplace_back(n);
	cout << "Yes\n" << k << "\n";
	for (int i = 1; i <= k; i++)
	{
		cout << c[i].size() << " ";
		for (int j = 0; j < c[i].size(); j++) cout << c[i][j] << " ";
		cout << "\n";
	}
	return 0;
}