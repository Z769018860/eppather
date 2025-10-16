#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 998244353;
const int maxn = 1e6 + 5;

int n, m, typ;
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

struct node
{
	int px, pt, qx, qt;
}f[maxn][20];

void add(int x, int d)
{
	f[x][0] = (node){1, d, 0, 1};
	int lim = 2, i = 1;
	while (lim <= x)
	{
		int y = x - (lim / 2);
		f[x][i].px = ((ll)f[y][i - 1].px * f[x][i - 1].qx % mod + (ll)f[y][i - 1].pt * f[x][i - 1].px % mod) % mod;
		f[x][i].pt = ((ll)f[y][i - 1].px * f[x][i - 1].qt % mod + (ll)f[y][i - 1].pt * f[x][i - 1].pt % mod) % mod;
		f[x][i].qx = ((ll)f[y][i - 1].qx * f[x][i - 1].qx % mod + (ll)f[y][i - 1].qt * f[x][i - 1].px % mod) % mod;
		f[x][i].qt = ((ll)f[y][i - 1].qx * f[x][i - 1].qt % mod + (ll)f[y][i - 1].qt * f[x][i - 1].pt % mod) % mod;
		lim <<= 1;
		i++;
	}
}

ll invp(ll a)
{
	ll b = mod - 2, ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m >> typ;
	for (int i = 1; i <= n; i++)
	{
		int d;
		cin >> d;
		add(i, d);
	}
	
	int las = 0;
	while (m--)
	{
		int op;
		cin >> op;
		if (op == 1)
		{
			int x;
			cin >> x;
			if (typ == 1) x ^= las;
			add(++n, x); 
		}
		else
		{
			int l, r;
			cin >> l >> r;
			if (typ == 1) l ^= las, r ^= las;
			int nw = r, len = r - l + 1;
			ll ansp = 1, ansq = 0;
			for (int i = 19; ~i; i--)
			{
				if (!(len & (1 << i))) continue;
				swap(ansp, ansq);
				ll nansp = (ansp * f[nw][i].px % mod + ansq * f[nw][i].pt % mod) % mod;
				ll nansq = (ansp * f[nw][i].qx % mod + ansq * f[nw][i].qt % mod) % mod;
				ansp = nansp, ansq = nansq;
				nw -= (1 << i);
			}
			las = ansp ^ ansq;
			cout << ansp << " " << ansq << "\n";
		}
	}
	return 0;
}