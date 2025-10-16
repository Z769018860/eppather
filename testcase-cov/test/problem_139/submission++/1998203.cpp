#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int M = 2e5 + 5;
struct segment_tree
{
	long long a[N];
	int num = 0;
	struct edge
	{
		int lson,rson;
		long long sum = 0,lazy = 0;
	}tree[M];
	void push_up(int k1)
	{
		tree[k1].sum = tree[tree[k1].lson].sum + tree[tree[k1].rson].sum;
	} 
	void down(int k1,int l,int r,long long lay)
	{
		tree[k1].sum += (r - l + 1) * lay;
		tree[k1].lazy += lay;
	}
	void push_down(int k1,int l,int r)
	{
		int mid = (l + r) >> 1;
		down(tree[k1].lson,l,mid,tree[k1].lazy);
		down(tree[k1].rson,mid + 1,r,tree[k1].lazy);
		tree[k1].lazy = 0;
	}
	void buildtree(int &k1,int l,int r)
	{
		k1 = ++num;
		int mid = (l + r) >> 1;
		if(l == r)
		{
			tree[k1].sum = a[l];
			return;
		}
		buildtree(tree[k1].lson,l,mid);
		buildtree(tree[k1].rson,mid + 1,r);
		push_up(k1);
	} 
	void modify(int k1,int l,int r,int x,int y,long long k)
	{
		if(x <= l && r <= y)
		{
			tree[k1].sum += (r - l + 1) * k;
			tree[k1].lazy += k;
			return;
		}
		push_down(k1,l,r);
		int mid = (l + r) >> 1;
		if(x <= mid) modify(tree[k1].lson,l,mid,x,y,k);
		if(y > mid) modify(tree[k1].rson,mid + 1,r,x,y,k); 
		push_up(k1);
	}
	long long query(int k1,int l,int r,int x,int y)
	{
		if(x <= l && r <= y) return tree[k1].sum;
		push_down(k1,l,r);
		int mid = (l + r) >> 1;
		long long ans = 0;
		if(x <= mid) ans += query(tree[k1].lson,l,mid,x,y);
		if(y > mid) ans += query(tree[k1].rson,mid + 1,r,x,y); 
		return ans;
	}
}t;
int n,m,r = 1,cnt,tot,head[N],fa[N],dis[N],son[N],dfn[N],siz[N],top[N];
long long c[N];
struct edge
{
	int to,nxt;
}e[M];
void addedge(int x,int y)
{
	e[++cnt].to = y;
	e[cnt].nxt = head[x];
	head[x] = cnt;
}
void dfs1(int x)
{
	dis[x] = dis[fa[x]] + 1;
	siz[x] = 1;
	int mx = -1;
	for(int i = head[x];i;i = e[i].nxt)
	{
		if(e[i].to != fa[x])
		{
			dfs1(e[i].to);
			siz[x] += siz[e[i].to];
			if(siz[e[i].to] > mx)
			{
				mx = siz[e[i].to];
				son[x] = e[i].to;
			}
		}
	}
}
void dfs2(int x,int f)
{
	dfn[x] = ++tot;
	t.a[tot] = c[x];
	top[x] = f;
	if(son[x]) dfs2(son[x],f);
	for(int i = head[x];i;i = e[i].nxt) if(e[i].to != fa[x] && e[i].to != son[x]) dfs2(e[i].to,e[i].to);
}
void ask2(int x,int y,long long k)
{
	while(top[x] != top[y])
	{
		if(dis[top[x]] < dis[top[y]]) swap(x,y);
		t.modify(1,1,n,dfn[top[x]],dfn[x],k); 
		x = fa[top[x]];
	}
	if(dfn[x] > dfn[y]) swap(x,y);
	t.modify(1,1,n,dfn[x],dfn[y],k); 
}
int get_up(int x,int y)
{
	int lst;
	while(top[x] != top[y])
	{
		lst = top[y];
		y = fa[top[y]];
	}
	if(y != x) return son[x];
	else return lst;
}
void ask3(int x,long long k)
{
	if(x == r) t.modify(1,1,n,1,n,k); 
	else if(dfn[x] <= dfn[r] && dfn[r] <= dfn[x] + siz[x] - 1)
	{
		int p = get_up(x,r);
		t.modify(1,1,n,1,n,k);
		t.modify(1,1,n,dfn[p],dfn[p] + siz[p] - 1,-k);  
	}
	else t.modify(1,1,n,dfn[x],dfn[x] + siz[x] - 1,k); 
}
long long ask4(int x,int y)
{
	long long ans = 0;
	while(top[x] != top[y])
	{
		if(dis[top[x]] < dis[top[y]]) swap(x,y);
		ans += t.query(1,1,n,dfn[top[x]],dfn[x]); 
		x = fa[top[x]];
	}
	if(dfn[x] > dfn[y]) swap(x,y);
	ans += t.query(1,1,n,dfn[x],dfn[y]); 	
	return ans;
}
long long ask5(int x)
{
	if(x == r) return t.query(1,1,n,1,n); 
	else if(dfn[x] <= dfn[r] && dfn[r] <= dfn[x] + siz[x] - 1)
	{
		int p = get_up(x,r);
		return t.query(1,1,n,1,n) - t.query(1,1,n,dfn[p],dfn[p] + siz[p] - 1);  
	}
	else return t.query(1,1,n,dfn[x],dfn[x] + siz[x] - 1); 
}
signed main()
{	
	scanf("%d",&n);;
	for(int i = 1;i <= n;i++) scanf("%lld",&c[i]);
	for(int i = 2;i <= n;i++)
	{
		scanf("%d",&fa[i]);
		addedge(i,fa[i]);
		addedge(fa[i],i);
	}
	fa[r] = r;
	dfs1(r);
	dfs2(r,r);
	t.buildtree(t.tree[0].lson,1,n); 
	scanf("%d",&m);
	for(int i = 1;i <= m;i++)
	{
		int opt;
		scanf("%d",&opt);
		if(opt == 1) scanf("%d",&r);
		else if(opt == 2)
		{
			int x,y;
			long long z;
			scanf("%d%d%lld",&x,&y,&z);
			ask2(x,y,z);
		}
		else if(opt == 3)
		{
			int x;
			long long z;
			scanf("%d%lld",&x,&z);
			ask3(x,z);
		}
		else if(opt == 4)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			printf("%lld\n",ask4(x,y));
		}
		else
		{
			int x;
			scanf("%d",&x);
			printf("%lld\n",ask5(x));
		}
	}
	return 0;
}