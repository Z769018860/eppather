#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

#define x first
#define y second
#define mp make_pair

using namespace std;
typedef pair<int,int> PII;
const int N = 1e5 + 10;

int ans[N], n, m, fa[N], sz[N], head[N], r[N * 15], s[N * 15], stack[N * 15], top, L[N], R[N], tot, t, len, hc[N], vc[N], nc[N], tc;
int pos[N], posv[N];
int opt[N], b[N * 15]; 


PII res[N]; 


PII a[N];


PII op[N];


struct Resume{
	int x, y, szx, szy;
	vector <PII> by;
};
vector <Resume> rr;


PII q[N]; 

void add_c(int x, int y)
{
	vc[++tc] = y, nc[tc] = hc[x], hc[x] = tc;
}

void init(int x)
{
	r[x] = 0;
}

int get(int x)
{
	return x == fa[x] ? x : get(fa[x]);
}

void merge(int x, int y)
{
	Resume re;
	for(int p = head[y]; p; p = r[p])
	{
		re.by.push_back(mp(b[p], s[p]));
	}
	re.x = x, re.y = y, re.szx = sz[x], re.szy = sz[y];
	rr.push_back(re);
	
	fa[y] = x, sz[x] += sz[y];
	int i = head[x], j = head[y];
	int last = head[x] = head[y] = 0;
	for(; i && j; )
	{
		if(b[i] < b[j])
		{
			if(!head[x]) head[x] = i;
			if(last) r[last] = i;
			last = i;
			i = r[i];
		}
		else if(b[i] > b[j])
		{
			if(!head[x]) head[x] = j;
			if(last) r[last] = j;
			last = j;
			j = r[j];
		}
		else
		{
			if(!head[x]) head[x] = i;
			if(last) r[last] = i;
			s[i] += s[j];
			last = i;
			stack[++top] = j;
			i = r[i], j = r[j];
		}
	}
	while(i)
	{
		r[last] = i;
		last = i;
		i = r[i];
	}
	while(j)
	{
		r[last] = j;
		last = j;
		j = r[j];
	}
	init(last);
}

void resume(Resume re)
{
	int x = re.x, y = re.y, szx = re.szx, szy = re.szy;
	vector <PII>& by = re.by;
	fa[x] = x, fa[y] = y, sz[x] = szx, sz[y] = sz[y];
	for(int j = head[y]; j; j = r[j])
	{
		stack[++top] = j;
	}
	head[y] = 0;
	int last = 0;
	for(auto& P : by)
	{
		int p = top ? stack[top--] : ++tot;
		init(p);
		if(last) r[last] = p;
		b[p] = P.x, s[p] = P.y;
		last = p;
		if(!head[y]) head[y] = p;
	}
	for(int i = head[x], j = 0; i && j < by.size(); )
	{
		auto P = by[j];
		if(b[i] < P.x)
		{
			i = r[i];
		}
		else if(b[i] == P.x)
		{
			s[i] -= P.y;
			j++;
		}
	}
	by.clear(); by.shrink_to_fit();
}

void dfs(int p)
{
	int x = get(op[p].x), y = get(op[p].y);
	if(sz[x] < sz[y]) swap(x, y);
	if(x != y) merge(x, y);
	if(opt[p] == 3)
	{
		if(q[p].y > sz[get(q[p].x)])
		{
			ans[p] = -1;
		}
		else
		{
			int X = get(q[p].x);
			for(int i = head[X]; i; i = r[i])
			{
				if(q[p].y <= s[i])
				{
					res[p].x = b[i], res[p].y = q[p].y;
					break;
				}
				else
				{
					q[p].y -= s[i];
				}
			}
			for(int i = L[res[p].x]; i <= R[res[p].x]; i++)
			{
				if(get(a[i].y) == X)
				{
					q[p].y--;
					if(!q[p].y) ans[p] = a[i].x;
				}
			}
		}
	}
	for(int i = hc[p]; i; i = nc[i])
	{
		dfs(vc[i]);
	}
	if(x != y)
	{
		resume(rr[rr.size() - 1]);
		rr.pop_back();
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		a[i] = mp(x, i);
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++)
	{
		posv[a[i].y] = i;
	}
	len = 450;
	for(int i = 1; i <= n / len; i++)
	{
		L[i] = R[i - 1] + 1, R[i] = i * len;
		for(int j = L[i]; j <= R[i]; j++) pos[j] = i;
	}
	t = n / len;
	if(R[t] != n)
	{
		t++;
		L[t] = R[t - 1] + 1, R[t] = n;
		for(int i = L[t]; i <= R[t]; i++) pos[i] = t;
	}
	for(int i = 1; i <= n; i++)
	{
		init(++tot);
		head[i] = tot, b[tot] = pos[posv[i]], s[tot] = 1;
		fa[i] = i, sz[i] = 1;
	}
	
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		scanf("%d%d", &opt[i], &x);
		if(opt[i] == 2)
		{
			add_c(x, i);
		}
		else
		{
			add_c(i - 1, i);
		}
		
		if(opt[i] == 1)
		{
			scanf("%d", &y);
			op[i] = mp(x, y);
		}
		else if(opt[i] == 3)
		{
			scanf("%d", &y);
			q[i] = mp(x, y);
		}
	}
	
	dfs(0);
	for(int i = 1; i <= m; i++)
	{
		if(opt[i] == 3)
		{
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}