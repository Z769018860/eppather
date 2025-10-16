#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;
const int N = 1e5 + 10, INF = 1e8;

int tot, n, m, root[N * 3], cnt, ans = INF;
map <int, int> mp; 

struct SegmentTree{
	int lc, rc, mx, mn, v;
}tr[N << 8];

void pushup(int p)
{
	tr[p].v = min(min(tr[tr[p].lc].v, tr[tr[p].rc].v), tr[tr[p].rc].mn - tr[tr[p].lc].mx);
	if(tr[p].lc)
	{
		tr[p].mn = tr[tr[p].lc].mn;
	}
	else
	{
		tr[p].mn = tr[tr[p].rc].mn;
	}
	if(tr[p].rc)
	{
		tr[p].mx = tr[tr[p].rc].mx;
	}
	else
	{
		tr[p].mx = tr[tr[p].lc].mx;
	}
}

void insert(int& p, int l, int r, int x)
{
	if(!p) p = ++tot;
	if(l == r)
	{
		tr[p].mn = tr[p].mx = x;
		tr[p].v = INF;
		return;
	}
	int mid = l + r >> 1;
	if(x <= mid) insert(tr[p].lc, l, mid, x);
	else insert(tr[p].rc, mid + 1, r, x);
	pushup(p);
}

int merge(int p, int q, int l, int r)
{
	if(!p || !q) return p + q;
	int mid = l + r >> 1;
	tr[p].lc = merge(tr[p].lc, tr[q].lc, l, mid);
	tr[p].rc = merge(tr[p].rc, tr[q].rc, mid + 1, r);
	pushup(p);
	return p;
}

int main()
{
	tr[0].mx = -INF, tr[0].mn = tr[0].v = INF;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		if(!mp.count(x)) mp[x] = ++cnt;
		insert(root[mp[x]], 1, n, i);
		ans = min(ans, tr[root[mp[x]]].v);
	}
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(!mp.count(x)) mp[x] = ++cnt;
		if(!mp.count(y)) mp[y] = ++cnt;
		root[mp[y]] = merge(root[mp[x]], root[mp[y]], 1, n);
		root[mp[x]] = 0;
		ans = min(ans, tr[root[mp[y]]].v);
		if(ans < n) printf("%d\n", ans);
		else puts("2147483647");
	}
	return 0;
}