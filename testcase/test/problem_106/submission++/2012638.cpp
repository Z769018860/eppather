
#include <bits/stdc++.h> 
#define INF 2147483647
#define N 50004
using namespace std;
int n, T;
int a[N];
struct node {
	int val;
	int rnd;
	int siz;
	int ch[2];
}e[N << 6];
int tot;
#define val(i) e[i].val
#define rnd(i) e[i].rnd
#define siz(i) e[i].siz
#define lc(i) e[i].ch[0]
#define rc(i) e[i].ch[1]
class FHQ_Treap {
private:
	int root;
	int newnode(int x) {
		++tot;
		val(tot) = x;
		rnd(tot) = (rand() << 10) + (rand() << 4) + rand();
		siz(tot) = 1;
		return tot;
	}
	int push_up(int p) {
		siz(p) = siz(lc(p)) + siz(rc(p)) + 1;
		return p;
	}
	void spilt(int p, int x, int &l, int &r) {
		if (!p)
			return l = r = 0, void();
		if (val(p) <= x)
			l = p, spilt(rc(p), x, rc(p), r);
		else
			r = p, spilt(lc(p), x, l, lc(p));
		push_up(p);
	}
	int merge(int l, int r) {
		if (!l || !r)
			return l + r;
		if (rnd(l) >= rnd(r))
			return rc(l) = merge(rc(l), r), push_up(l);
		return lc(r) = merge(l, lc(r)), push_up(r);
	}
public:
	void insert(int x) {
		int l, r;
		spilt(root, x, l, r);
		root = merge(merge(l, newnode(x)), r);
	}
	void del(int x) {
		int l, r, mid;
		spilt(root, x - 1, l, mid);
		spilt(mid, x, mid, r);
		mid = merge(lc(mid), rc(mid));
		root = merge(merge(l, mid), r);
	}
	int rnk(int x) {
		int l, r;
		spilt(root, x - 1, l, r);
		int ans = siz(l) + 1;
		root = merge(l, r);
		return ans;
	}
	int find_rnk(int p, int rk) {
		if (rk == siz(lc(p)) + 1)
			return val(p);
		if (rk < siz(lc(p)) + 1)
			return find_rnk(lc(p), rk);
		return find_rnk(rc(p), rk - siz(lc(p)) - 1);
	}
	int pre(int x) {
		int l, r;
		spilt(root, x - 1, l, r);
		int ans;
		ans = (siz(l)) ? (find_rnk(l, siz(l))) : -INF;
		root = merge(l, r);
		return ans;			
	}
	int nxt(int x) {
		int l, r;
		spilt(root, x, l, r);
		int ans;
		ans = (siz(r)) ? (find_rnk(r, 1)) : INF;
		root = merge(l, r);
		return ans;
	}
	void build(int l, int r) {
		for (int i = l; i <= r; i++)
			insert(a[i]);
	}
}Tp[N << 6];
#undef val
#undef rnd
#undef siz
#undef lc
#undef rc
struct Node {
	int l, r;
}t[N << 2];
#define l(i) t[i].l
#define r(i) t[i].r
#define lc (p << 1)
#define rc (p << 1 | 1)
class SEG_Tree {
public:
	void build(int p, int l, int r) {
		l(p) = l, r(p) = r;
		Tp[p].build(l, r);
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		build(lc, l, mid);
		build(rc, mid + 1, r);
	}
	int rank(int p, int k, int l, int r) {
		if (l > r(p) || l(p) > r)
			return 0;
		if (l <= l(p) && r(p) <= r) 
			return Tp[p].rnk(k) - 1;
		return rank(lc, k, l, r) + rank(rc, k, l, r);
	}
	int kth(int p, int l, int r, int rk) {
		int L = 0, R = 1e8, ans = 0, mid = 0;
		while (L <= R) {
			mid = (L + R) >> 1;
			if (rank(1, mid, l, r) + 1 <= rk)
				ans = mid, L = mid + 1;
			else
				R = mid - 1; 
		}
		return ans;
	}
	void update(int p, int x, int v) {
		Tp[p].del(a[x]);
		Tp[p].insert(v);
		int mid = (l(p) + r(p)) >> 1;
		if (l(p) != r(p)) {
			if (x <= mid)
				update(lc, x, v);
			else
				update(rc, x, v);
		}
	}
	int pre(int p, int x, int l, int r) {
		if (l > r(p) || l(p) > r)
			return -INF;
		if (l <= l(p) && r(p) <= r)
			return Tp[p].pre(x);
		return max(pre(lc, x, l, r), pre(rc, x, l, r));
	}
	int nxt(int p, int x, int l, int r) {
		if (l > r(p) || l(p) > r)
			return INF;
		if (l <= l(p) && r(p) <= r)
			return Tp[p].nxt(x);
		return min(nxt(lc, x, l, r), nxt(rc, x, l, r));
	}
}Tree;
int main() {
	srand(time(0));
	scanf("%d%d", &n, &T);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	Tree.build(1, 1, n);
	while (T--) {
		int num;
		scanf("%d", &num);
		if (num == 1) {
			int l, r, k;
			scanf("%d%d%d", &l, &r, &k);
			printf("%d\n", Tree.rank(1, k, l, r) + 1);
		}
		else if(num == 2) {
			int l, r, k;
			scanf("%d%d%d", &l, &r, &k);
			printf("%d\n", Tree.kth(1, l, r, k));
		}
		else if(num == 3) {
			int pos, k;
			scanf("%d%d", &pos, &k);
			Tree.update(1, pos, k);
			a[pos] = k;
		}
		else if(num == 4) {
			int l, r, k;
			scanf("%d%d%d", &l, &r, &k);
			printf("%d\n", Tree.pre(1, k, l, r));
		}
		else if(num == 5) {
			int l, r, k;
			scanf("%d%d%d", &l, &r, &k);
			printf("%d\n", Tree.nxt(1, k, l, r));
		}
	}
	return 0;
}