#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = (x); i <= (y); i+=1)
#define epr(i, x) for (int i = head[x]; i; i = nxt[i])
#define per(i, x, y) for (int i = (x); i >= (y); i-=1)
#define DC int T = gi <int> (); while (T--)
#define eb emplace_back
#define ep emplace
#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int, int> PII;
typedef pair <LL, int> PLI;
typedef pair <int, LL> PIL;
typedef pair <LL, LL> PLL;
typedef pair <__int128, __int128> P88;

template <typename T>
inline T gi()
{
	T x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar();}
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return f * x;
}

template <typename T, typename U> inline void chkmax(T &x, const U &y) {x = x > y ? x : y;}
template <typename T, typename U> inline void chkmin(T &x, const U &y) {x = x < y ? x : y;}

const int N = 1000003, M = N << 1;
const LL INF = 4000000000000000000ll;

int n;
LL K;
vector <int> g[N];
int x[N], y[N];
int ans[N];
int sz, cnt;
int stk[N], tp;
int lim;
int del[N];
bool vis[N];

inline void ban(int u)
{
	if (!del[u] && u > lim) --cnt;
	++del[u];
	for (auto v : g[u])
	{
		if (!del[v] && v > lim) --cnt;
		++del[v];
	}
}

inline void unban(int u)
{
	--del[u];
	if (!del[u] && u > lim) ++cnt, stk[++tp] = u;
	for (auto v : g[u])
	{
		--del[v];
		if (!del[v] && v > lim) ++cnt, stk[++tp] = v;
	}
}

inline void Add1() {++lim; if (!del[lim]) --cnt;}
inline void Del1() {if (!del[lim]) ++cnt, stk[++tp] = lim; --lim;}

P88 dfs(int u)
{
	vis[u] = 1;
	P88 res = {1, 1};
	for (auto v : g[u])
		if (!vis[v] && v > lim && !del[v])
		{
			auto tmp = dfs(v);
			res.fi *= tmp.se;
			res.se *= (tmp.fi + tmp.se);
		}
	return res;
}

inline LL calc()
{
	if (cnt > 120) return INF;
	vector <int> tmp;
	__int128 res = 1;
	while (tp)
	{
		int u = stk[tp--];
		if (u <= lim || del[u]) continue;
		tmp.eb(u);
		if (!vis[u])
		{
			auto tans = dfs(u);
			res *= (tans.fi + tans.se);
		}
	}
	for (auto x : tmp) stk[++tp] = x, vis[x] = 0;
	if (res > INF) res = INF;
	return res;
}

int main()
{
	n = gi <int> (), K = gi <LL> ();
	rep(i, 1, n - 1) x[i] = gi <int> () + 1;
	rep(i, 1, n - 1) y[i] = gi <int> () + 1, g[x[i]].eb(y[i]), g[y[i]].eb(x[i]);
	cnt = n;
	rep(i, 1, n) stk[++tp] = i;
	sz = gi <int> (); rep(i, 1, sz) ans[i] = gi <int> () + 1, ban(ans[i]);
	sort(ans + 1, ans + 1 + sz);
	while (lim < ans[sz]) Add1();
	LL now = calc() - 1;
	while (sz && now < K)
	{
		K -= now;
		while (lim > ans[sz]) Del1();
		unban(ans[sz--]);
		now = calc() - 1;
	}
	if (now < K) return !!0;
	while (lim < n && K)
	{
		Add1();
		while (del[lim]) Add1();
		ans[++sz] = lim;
		ban(lim);
		now = calc();
		if (now < K) K -= now, unban(lim), --sz;
		else --K;
	}
	rep(i, 1, sz) printf("%d ", ans[i] - 1);
	return !!0;
}
