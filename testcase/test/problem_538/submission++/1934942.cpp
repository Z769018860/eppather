#include <iostream>

typedef long long ll;
typedef double lf;

namespace FastIO
{
	const int MAXSIZE = 1 << 20;
	char buf[MAXSIZE], *p1, *p2;
	#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) ? EOF : *p1++)
	template <typename T>
	inline void Read(T &x)
	{
		x = 0; bool sgn = 0; char ch = gc();
		while (ch < '0' || ch > '9') {if (ch == '-') sgn = 1; ch = gc();}
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc();
		if (sgn) x = -x;
	}
}

using FastIO::Read;
using namespace std;

const int MAXN = 3e5 + 10, MAXM = 1e5 + 10;

int n, m, s[MAXM];
ll a[MAXN], k;

inline bool Check(int i)
{
	if (a[i - 1] == 0 && a[i] == 0) return 1;
	if (a[i] > 0 && a[i - 1] > 0) return 1;
	if (a[i] < 0 && a[i - 1] < 0) return 1;
	return 0;
}

inline void Solve(int x)
{

	ll mx = a[0], mn = a[0];
	for (int i = 1; i <= x; i++)
	{
		if (mx < a[i]) mx = a[i];
		if (mn > a[i]) mn = a[i];
	}
	
	int p = x;
	while (a[p] > 0 && k <= (mx - a[p - 1]) / a[p]) p++, a[p] = a[p - 2] + a[p - 1] * k;
	while (a[p] < 0 && k <= (a[p - 1] - mn) / -a[p]) p++, a[p] = a[p - 2] + a[p - 1] * k;
	int pos = 0;
	while (pos < m && s[pos + 1] <= p) pos++;
	
	ll res = -1e18; int ans = -1;
	for (int i = 1; i <= pos; i++)
		if (a[s[i]] > res) res = a[s[i]], ans = s[i];

	if (pos == m) cout << ans << " ";
	else if (a[p] == 0) cout << (res < 0 ? s[pos + 1] : ans) << " ";
	else if (a[p] < 0) cout << (~ans ? ans : s[pos + 1]) << " ";
	else cout << s[m] << " ";
	
	res = 1e18, ans = -1;
	for (int i = 1; i <= pos; i++)
		if (a[s[i]] < res) res = a[s[i]], ans = s[i];
	if (pos == m) cout << ans << "\n";
	else if (a[p] == 0) cout << (res > 0 ? s[pos + 1] : ans) << "\n";
	else if (a[p] > 0) cout << (~ans ? ans : s[pos + 1]) << "\n";
	else cout << s[m] << "\n";
}

int main()
{

	ios::sync_with_stdio(0), cin.tie(0);
	Read(m);
	for (int i = 1; i <= m; i++) Read(s[i]);
	
	Read(n);
	while (n--)
	{
		Read(a[0]), Read(a[1]), Read(k);
		if (Check(1)) {Solve(1); continue;}
		for (int i = 2; i <= 50; i++)
		{
			a[i] = a[i - 1] * k + a[i - 2];
			if (Check(i)) {Solve(i); break;}
		}
	}
	return 0;
}
