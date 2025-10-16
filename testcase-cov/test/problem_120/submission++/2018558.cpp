#include<map>
#include<queue>
#include<cmath>
#include<vector>
#include<complex>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<unordered_map>
using namespace std;

char buf[1<<20], *p1=buf, *p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf, 1, 1<<20, stdin), p1==p2)?EOF:*p1++)
template <typename T>
void read(T &x)
{
	x=0;int f=1;char c=getchar();
	while (!isdigit(c)) f=(c=='-')?-1:1, c=getchar();
	while (isdigit(c)) x=(x<<1)+(x<<3)+c-'0', c=getchar();
	x*=f;
}

typedef long long LL;
const int N=3e5+10;
int n, m, tot, cnt, root[N];
struct treap
{
	int l, r;
	int v, Size, key;
}tr[N*50];

void pushup(int p) {tr[p].Size=tr[tr[p].l].Size+tr[tr[p].r].Size+1;}
int add(int v)
{
	++tot;
	tr[tot].l=tr[tot].r=0;
	tr[tot].v=v, tr[tot].Size=1;
	tr[tot].key=rand();return tot;
}

void split(int p, int v, int &x, int &y)
{
	if (!p) {x=y=0;return ;}
	if (tr[tr[p].l].Size>=v)
	{
		y=++tot;tr[y]=tr[p];
		split(tr[p].l, v, x, tr[y].l);
		pushup(y);
	}
	else
	{
		x=++tot;tr[x]=tr[p];
		split(tr[p].r, v-tr[tr[p].l].Size-1, tr[x].r, y);
		pushup(x); 
	}
}

int merge(int x, int y)
{
	if (!x||!y) return x+y;
	if (tr[x].key<=tr[y].key)
	{
		int p=++tot;tr[p]=tr[x];
		tr[p].r=merge(tr[p].r, y);
		pushup(p);return p;
	}
	else
	{
		int p=++tot;tr[p]=tr[y];
		tr[p].l=merge(x, tr[p].l);
		pushup(p);return p;
	}
}

void insert(int &pos, int k, int v)
{
	int x, y, z;
	split(pos, k-1, x, y);
	z=add(v);pos=merge(merge(x, z), y);
}

void del(int &pos, int v)
{
	int x, y, z;
	split(pos, v, x, y);
	split(x, v-1, x, z);
	pos=merge(x, y);
}

int kth(int p, int k)
{
	if (k==tr[tr[p].l].Size+1) return p;
	if (k<=tr[tr[p].l].Size) return kth(tr[p].l, k);
	else return kth(tr[p].r, k-tr[tr[p].l].Size-1);
}

int main()
{
	read(n);
	for (int i=1;i<=n;i++)
	{
		int op, x, y, v;
		read(op), read(v), read(x);
		if (op!=3)  root[++cnt]=root[v];
		if (op==1) read(y), insert(root[cnt], x, y);
		else if (op==2) del(root[cnt], x);
		else printf("%d\n", tr[kth(root[v], x)].v);
	}
	return 0;
}