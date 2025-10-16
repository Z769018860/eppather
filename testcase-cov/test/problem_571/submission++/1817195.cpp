#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;
namespace FAST_READ{
    const int MAX_BUF=1<<20;
    char buf[MAX_BUF+10],*p1=buf,*p2=buf;
    #define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,MAX_BUF,stdin),p1==p2)?EOF:*p1++)
    long long rd(){
        long long x=0;bool f=0;char ch=gc();
        while(ch<'0'||ch>'9')f|=ch=='-',ch=gc();
        while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=gc();
        return f?-x:x;
    }
}
using FAST_READ::rd;

const int N = 1e5 + 5;
const int M = 1e7 + 5;

int n, m, L, R;
vector<int> T[N];
int q[N];

struct Edge {int v, w, nxt;} e[N << 1];
int cntn, cnte = 1, head[N];

void link(int u, int v, int w)
{
	e[++cnte] = {v, w, head[u]}, head[u] = cnte;
	e[++cnte] = {u, w, head[v]}, head[v] = cnte;
}

void rebuild(int u, int fa)
{
	int lst = 0;
	for(auto v : T[u]) if(v != fa)
	{
		if(!lst) link(u, v, 1), lst = u;
		else
		{
			int nw = ++cntn;
			link(lst, nw, 0), link(nw, v, 1); lst = nw;
		}
		rebuild(v, u);
	}
	return;
}

bool vis[M];
int rt, mxs, siz[N];

void getrt(int u, int fr, int all)
{
	siz[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt)
	{
		int v = e[i].v;
		if((i ^ 1) == fr || vis[i]) continue;
		getrt(v, i, all); siz[u] += siz[v];
		if(max(siz[v], all - siz[v]) < mxs)
			rt = i, mxs = max(siz[v], all - siz[v]);
	}
	return;
}

vector<int> vec[N];
int dep[N], mxd;

void dfs(int u, int fr, int d)
{
	if(u <= n) vec[d].push_back(u);
	mxd = max(mxd, dep[u] = d), siz[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt)
	{
		int v = e[i].v;
		if((i ^ 1) == fr || vis[i]) continue;
		dfs(v, i, d + e[i].w);
		siz[u] += siz[v];
	}
	return;
}

int tot, ls[M], rs[M];
vector<int> G[M];

struct Seg
{
	int lim, rt1, rt2;
	void build(int op, int l, int r, int &rt1, int &rt2)
	{
		rt1 = ++tot; rt2 = ++tot;
		if(l == r)
		{
			for(auto x : vec[l])
			{
				G[x + op * n].push_back(rt1);
				G[rt2].push_back(x + op * n);
			}
			return;
		}
		int mid = (l + r) >> 1;
		build(op, l, mid, ls[rt1], ls[rt2]), build(op, mid + 1, r, rs[rt1], rs[rt2]);
		G[ls[rt1]].push_back(rt1), G[rs[rt1]].push_back(rt1);
		G[rt2].push_back(ls[rt2]), G[rt2].push_back(rs[rt2]);
		return;
	}

	void init(int _lim, int op)
	{
		lim = _lim;
		build(op, 0, lim, rt1, rt2);
	}

	void link(int L, int R, int x, int op, int l, int r, int rt)
	{
		if(L <= l && r <= R)
		{
			if(op == 1) G[rt].push_back(x);
			else G[x].push_back(rt);
			return;
		}
		int mid = (l + r) >> 1;
		if(L <= mid) link(L, R, x, op, l, mid, ls[rt]);
		if(R > mid) link(L, R, x, op, mid + 1, r, rs[rt]);
		return;
	}

	void Link(int x, int op, int l, int r)
	{
		if(l > lim) return;
		if(r > lim) r = lim;
		if(op == 1) link(l, r, x, op, 0, lim, rt1);
		if(op == 2) link(l, r, x, op, 0, lim, rt2);
		return;
	}
} E[2][2];

void Link(int t, int x, int op, int d)
{
	int l = L - dep[x] - d, r = R - dep[x] - d;
	if(r < 0) return;
	if(l < 0) l = 0;
	if(op == 0) E[t][0].Link(x, 2, l, r), E[t][1].Link(n + x, 1, l, r);
	if(op == 1) E[t][1].Link(x, 2, l, r), E[t][0].Link(n + x, 1, l, r);
	if(op == 2) E[t][0].Link(n + x, 2, l, r), E[t][1].Link(x, 1, l, r);
	if(op == 3) E[t][1].Link(n + x, 2, l, r), E[t][0].Link(x, 1, l, r);
	return;
}

void solve(int id)
{
	

	vis[id] = vis[id ^ 1] = 1;
	int x = e[id].v, y = e[id ^ 1].v;
	vector<int> vx, vy;

	mxd = 0, dfs(x, 0, 0);
	for(int i : {0, 1}) E[0][i].init(mxd, i);
	for(int i = 0; i <= mxd; i++)
	{
		vx.insert(vx.end(), vec[i].begin(), vec[i].end());
		vec[i].clear();
	}

	mxd = 0, dfs(y, 0, 0);
	for(int i : {0, 1}) E[1][i].init(mxd, i);
	for(int i = 0; i <= mxd; i++)
	{
		vy.insert(vy.end(), vec[i].begin(), vec[i].end());
		vec[i].clear();
	}

	for(auto u : vx) for(int i = 0; i <= 3; i++) if(q[u] >> i & 1) Link(1, u, i, e[id].w);
	for(auto v : vy) for(int i = 0; i <= 3; i++) if(q[v] >> i & 1) Link(0, v, i, e[id].w);

	if(siz[x] > 1) mxs = cntn, getrt(x, 0, siz[x]), solve(rt);
	if(siz[y] > 1) mxs = cntn, getrt(y, 0, siz[y]), solve(rt);
	return;
}

int tp, st[M];

bool dfs(int u)
{
	if(u <= n && vis[n + u]) return false;
	if(n < u && u <= 2 * n && vis[u - n]) return false;
	vis[st[++tp] = u] = 1;
	for(auto v : G[u]) if(!vis[v] && !dfs(v)) return false;
	return true;
}

int main()
{
	n = rd(), m = rd(), L = rd(), R = rd();
	for(int i = 1, u, v; i < n; i++)
		u = rd(), v = rd(), T[u].push_back(v), T[v].push_back(u);
	for(int i = 1, x, op; i <= m; i++)
		x = rd(), op = rd(), q[x] |= 1 << op;

	cntn = n, rebuild(1, 0);
	tot = n << 1, mxs = cntn, getrt(1, 0, cntn), solve(rt);

	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= n; i++)
	{
		if(vis[i] || vis[n + i]) continue;
		if(tp = 0, !dfs(i))
		{
			while(tp) vis[st[tp--]] = 0;
			if(!dfs(n + i)) return puts("NO"), 0;
		}
	}
	return puts("YES"), 0;
}