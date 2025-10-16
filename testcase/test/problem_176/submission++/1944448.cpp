
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> PII;
template <typename T> inline void read(T &x)
{
	x = 0; int f = 1; char ch;
	while((ch = getchar()) > '9' || ch < '0') if(ch == '-') f = -1;
	while(ch >= '0' && ch <= '9') x = x*10+(ch^'0'),ch = getchar();
	x *= f;
}

const int N = 2e5+5;

struct line
{
	LL k,b; int id;
}e[N],a[N];

pair<line,LL> max(line a,line b)
{
	if(a.k < b.k || (a.k == b.k && a.b < b.b)) swap(a,b);
	if(a.b >= b.b) return {a,2e18};
	return {b,(b.b-a.b)/(a.k-b.k)};
}

class segment
{
	public:
		struct smt
		{
			int l,r; line s; LL xx,tag;
		}tree[N<<2];
		#define ls(x) x<<1
		#define rs(x) x<<1|1
		void pushup(smt &x,smt &l,smt &r)
		{
			x.xx = min(l.xx,r.xx);
			pair<line,LL> now;
			now = max(l.s,r.s);
			x.s = now.fi, x.xx = min(x.xx,now.se); 
		}
		void down_load(int x,LL v)
		{
			tree[x].xx -= v; 
			tree[x].s.b += v*tree[x].s.k;
			tree[x].tag += v;
		}
		void down(int x)
		{
			if(tree[x].tag)
			{
				down_load(ls(x),tree[x].tag);
				down_load(rs(x),tree[x].tag);
				tree[x].tag = 0;
			}
		}
		void down_modify(int x,LL v)
		{
			if(v > tree[x].xx)
			{
				down_modify(ls(x),tree[x].tag+v),down_modify(rs(x),tree[x].tag+v);
				tree[x].tag = 0;
				pushup(tree[x],tree[ls(x)],tree[rs(x)]);
			}
			else down_load(x,v);
		}
		void build(int x,int l,int r)
		{
			tree[x].l = l,tree[x].r = r;
			if(l == r)
			{
				tree[x].s = e[l], tree[x].xx = 2e18;
				return ;
			}
			int mid = (l+r)/2;
			build(ls(x),l,mid),build(rs(x),mid+1,r);
			pushup(tree[x],tree[ls(x)],tree[rs(x)]);
		}
		void modify(int x,int p)
		{
			if(tree[x].l == tree[x].r){tree[x].s = e[p];return ;}
			down(x);
			int mid = (tree[x].l+tree[x].r)/2;
			if(p <= mid) modify(ls(x),p);
			else modify(rs(x),p);
			pushup(tree[x],tree[ls(x)],tree[rs(x)]);
		}
		smt query(int x,int l,int r)
		{
			if(l <= tree[x].l && tree[x].r <= r) return tree[x];
			down(x);
			int mid = (tree[x].l+tree[x].r)/2;
			if(l > mid) return query(rs(x),l,r);
			else if(r <= mid) return query(ls(x),l,r);
			else
			{
				smt ans = tree[x],s1 = query(ls(x),l,r),s2 = query(rs(x),l,r);
				pushup(ans,s1,s2);
				return ans;
			}
		}
}ss;

int n,m,c[N];

int main()
{
	read(n); read(m);
	for(int i = 1;i <= n;i++) read(e[i].k),e[i].id = i;
	for(int i = 1;i <= n;i++) read(e[i].b);
	ss.build(1,1,n);
	while(m--)
	{
		int opt; read(opt);
		if(opt == 1)
		{
			int x; read(x);
			ss.down_modify(1,x);
		}
		else if(opt == 2)
		{
			int l,r,x; read(l); read(r); read(x);
			for(int i = 1;i <= x;i++)
			{
				auto ans = ss.query(1,l,r);
				a[i] = ans.s;
				e[a[i].id].k = -2e18,e[a[i].id].b = -2e18;
				ss.modify(1,a[i].id);
				if(i == x) printf("%lld%c",ans.s.b," \n"[i == x]);
			}
			for(int i = 1;i <= x;i++) e[a[i].id].k = a[i].k,e[a[i].id].b = a[i].b,ss.modify(1,a[i].id);
		}
		else
		{
			int x; LL k,b; read(x); read(k); read(b);
			e[x].k = k,e[x].b = b;
			ss.modify(1,x);
		}
	}
	return (0-0); 
}