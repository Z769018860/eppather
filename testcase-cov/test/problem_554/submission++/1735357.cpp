#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

#define int long long

namespace ningago
{

#define N 300010

int n, m;
int a[N];
std::vector <int> g[N];
std::map <int, bool> mp[N];
int sta[N], top;
void add_edge(int x, int y){g[x].push_back(y); }
void add(int x, int y){add_edge(x, y); add_edge(y, x); }
void ckmax(int &x, int y){x = x > y ? x : y; }
void ckmin(int &x, int y){x = x < y ? x : y; }
int R2[N], R3[N];
bool vis[N];
int l_[N], r_[N];
int ans1[N], ans2[N];
struct node
{
	int r, id, op;
};
std::vector <node> v[N];
struct Tree
{
	int tr[N];
	bool flag = 0;
	void ins(int x, int z)
	{
		if(flag)
			x = n - x + 1;
		for(; x <= n; x += x & (-x))
			tr[x] += z;
	}
	void clear()
	{
		memset(tr, 0, sizeof(tr));
	}
	int query(int x)
	{
		int res = 0;
		if(flag)
			x = n - x + 1;
		for(; x; x -= x & (-x))
			res += tr[x];
		return res;
	}
}t1, t2;

signed main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	scanf("%lld", &m);
	for(int i = 1; i <= m; i++)
		scanf("%lld%lld", &l_[i], &r_[i]);
	top = 0;
	for(int i = 1; i <= n; i++)
	{

		while(top && a[sta[top]] < a[i]) top--;
		if(top)
		{
			if(!mp[sta[top]][i])
			{
				mp[sta[top]][i] = mp[i][sta[top]] = 1;
				add(sta[top], i);
			}
		}
		sta[++top] = i;
	}
	top = 0;
	for(int i = 1; i <= n; i++)
	{
		while(top && a[sta[top]] > a[i]) top--;
		if(top)
		{
			if(!mp[sta[top]][i])
			{
				mp[sta[top]][i] = mp[i][sta[top]] = 1;
				add(sta[top], i);
			}
		}
		sta[++top] = i;
	}
	top = 0;
	for(int i = n; i; i--)
	{
		while(top && a[sta[top]] < a[i]) top--;
		if(top)
		{
			if(!mp[sta[top]][i])
			{
				mp[sta[top]][i] = mp[i][sta[top]] = 1;
				add(sta[top], i);
			}
		}
		sta[++top] = i;
	}
	top = 0;
	for(int i = n; i; i--)
	{
		while(top && a[sta[top]] > a[i]) top--;
		if(top)
		{
			if(!mp[sta[top]][i])
			{
				mp[sta[top]][i] = mp[i][sta[top]] = 1;
				add(sta[top], i);
			}
		}
		sta[++top] = i;
	}
	for(int i = n; i; i--)
	{
		R3[i] = n;
		R2[i] = i;
		if(i != n)
			R2[i] = i + 1;
		if(i < n - 1 && ((a[i] < a[i + 1]) == (a[i + 1] < a[i + 2])))
			R2[i] = R2[i + 1];
	}
	for(int k = 1; k <= n; k++)
	{
		int sz = g[k].size();
		if(sz < 4 || !(sz & 1))
			continue;
		for(int i = 0; i < sz; i++)
			vis[g[k][i]] = 1;
		bool flag = 1;
		for(int i = 0;flag && i < sz;i++)
		{
			int nx = g[k][i];
			int szz = g[nx].size();
			int cnt = 0;
			for(int j = 0;cnt < 2 && j < szz; j++)
			{
				if(vis[g[nx][j]])
					cnt++;
			}	
			if(cnt < 2)
				flag = 0;
		}
		for(int i = 0; i < sz; i++)
			vis[g[k][i]] = 0;
		if(!flag)
			continue;
		int left = n + 1, right = 0;
		for(int i = 0; i < sz; i++)
			ckmin(left, g[k][i]), ckmax(right, g[k][i]);

		ckmin(R3[left], right - 1);
	}
	for(int i = n - 1; i; i--)
		ckmin(R3[i], R3[i + 1]);



	for(int i = 1; i <= m; i++)
	{
		if(l_[i] == r_[i])
		{
			ans1[i] = ans2[i] = 1;
			continue;
		}
		if(R2[l_[i]] >= r_[i])
		{
			ans1[i] = 2;
			int len = r_[i] - l_[i] + 1;
			ans2[i] = len * (len + 1) / 2 - len;
			continue;
		}
		if(l_[i] != 1)
			v[l_[i] - 1].push_back((node){r_[i], i, -1});
		v[r_[i]].push_back((node){r_[i], i, 1});
	}
	t1.flag = t2.flag = 0;
	for(int i = 1; i <= n; i++)
	{
		t1.ins(R3[i], R3[i]);
		t2.ins(R3[i], 1);
		int sz = v[i].size();
		for(int j = 0; j < sz; j++)
		{
			node t = v[i][j];
			ans2[t.id] += t.op * (t2.query(t.r) * t.r - t1.query(t.r));
		}
		v[i].clear();
	}
	for(int i = 1; i <= m; i++)
	{
		if(ans2[i] && !ans1[i])
			ans1[i] = 4;
		if(ans1[i])
			continue;
		if(l_[i] != 1)
			v[l_[i] - 1].push_back((node){r_[i], i, -1});
		v[r_[i]].push_back((node){r_[i], i, 1});
	}
	t1.flag = t2.flag = 0;
	t1.clear(), t2.clear();
	for(int i = 1; i <= n; i++)
	{
		t1.ins(R2[i], R2[i]);
		t2.ins(R2[i], 1);
		int sz = v[i].size();
		for(int j = 0; j < sz; j++)
		{
			node t = v[i][j];
			ans2[t.id] += t.op * (t2.query(t.r) * t.r - t1.query(t.r));
		}
		v[i].clear();
	}
	if(n == 1)
		printf("1\n");
	else if(R2[1] == n)
		printf("2\n");
	else if(R3[1] == n)
		printf("3\n");
	else
		printf("4\n");


	for(int i = 1; i <= m; i++)
	{
		if(ans2[i] && !ans1[i])
			ans1[i] = 3;
		printf("%lld %lld\n",ans1[i], ans2[i]);
	}
	return 0;
}

}

#undef int

int main()
{
	return ningago::main();
}