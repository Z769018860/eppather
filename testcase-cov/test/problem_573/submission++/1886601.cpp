#include <iostream>

typedef long long ll;
typedef double lf;

namespace FastIO
{
	const int MAXSIZE = 1 << 20;
	char buf[MAXSIZE], *p1, *p2;
	#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) ? EOF : *p1++)
	inline int Read()
	{
		int x = 0, f = 1; char ch = gc();
		while (!isdigit(ch)) {if (ch == '-') f = -1; ch = gc();}
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc();
		return x * f;
	}
}

using FastIO::Read;
using namespace std;

const int MAXN = 1e6 + 10, mod = 998244353;

int n, m, lg[MAXN];
bool TYPE;

struct Data
{
	int a, b, c, d;
	Data operator + (const Data &u) const
	{
		Data ans;
		ans.a = ((ll)a * u.a + (ll)b * u.c) % mod, ans.b = ((ll)a * u.b + (ll)b * u.d) % mod;
		ans.c = ((ll)c * u.a + (ll)d * u.c) % mod, ans.d = ((ll)c * u.b + (ll)d * u.d) % mod;
		return ans;
	}
}f[22][MAXN];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	for (int i = 1; i < MAXN; i++) lg[i] = lg[i >> 1] + 1;
	n = Read(), m = Read(), TYPE = Read();
	for (int i = 1; i <= n; i++) f[0][i] = Data{Read(), 1, 1, 0};
	for (int j = 1; j < lg[n]; j++)
		for (int i = n; i - (1 << j) + 1 >= 1; i--)
			f[j][i] = f[j - 1][i - (1 << j - 1)] + f[j - 1][i];
	int op, l, r, lstans = 0;
	while (m--)
	{
		op = Read();
		if (op == 1)
		{
			l = Read() ^ (TYPE ? lstans : 0);
			f[0][++n] = Data{l, 1, 1, 0};
			for (int i = 1; i < lg[n] && n - (1 << i) + 1 >= 1; i++)
				f[i][n] = f[i - 1][n - (1 << i - 1)] + f[i - 1][n];
		}
		else
		{
			l = Read() ^ (TYPE ? lstans : 0), r = Read() ^ (TYPE ? lstans : 0);
			Data ans = Data{1, 0, 0, 1};
			for (int i = lg[n] - 1; ~i; i--)
				if (r - (1 << i) + 1 >= l)
					ans = f[i][r] + ans, r -= (1 << i);
			lstans = ans.a ^ ans.c;
			cout << ans.a << " " << ans.c << "\n";
		}
	}
	return 0;
}