#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 5, mod = 998244353;
int n, vis[N];
long long ans[N], sna[N], mx;
vector<int> e[N];
map<int, int> mp[N];

struct Boom
{
	int id, v;
	long long p, r;
}a[N];

inline void dfs(int x, long long V, int lst)
{
	if (V <= ans[x] - min(2 * mx * mx, mod) || (mp[x].count(lst) && mp[x][lst] >= V))
	{
		return;
	}
	ans[x] = max(ans[x], V);
	mp[x][lst] = V;
	int VV = a[lst].v;
	for (auto y : e[x])
	{
		dfs(y, V + ((VV ^ a[y].v) + VV * a[y].v) % mod, y);
		dfs(y, V, lst);
	}
}

signed main()
{


	ios :: sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		a[i].id = i;
		cin >> a[i].p;
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].r;
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].v;
		mx = max(mx, 1ll * a[i].v);
	}
	sort(a + 1, a + 1 + n, [](Boom x, Boom y){return x.p < y.p;});
	for (int i = 1; i <= n; i++)
	{
		for (int j = i - 1; j >= 1; j--)
		{
			if (a[j].p < a[i].p - a[i].r)
			{
				break;
			}
			e[i].push_back(j);
			vis[j]++;
		}
		for (int j = i + 1; j <= n; j++)
		{
			if (a[j].p > a[i].p + a[i].r)
			{
				break;
			}
			e[i].push_back(j);
			vis[j]++;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (!vis[i])
		{
			dfs(i, 0, i);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		sna[a[i].id] = ans[i];
	}
	for (int i = 1; i <= n; i++)
	{
		cout << sna[i] << '\n';
	}
	return 0;
}