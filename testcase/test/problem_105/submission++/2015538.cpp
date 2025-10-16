#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int Maxn = 2e5 + 5;

struct FHQ_Treap {
	int l, r, val, siz, key, tag;	
}t[Maxn];

#define lp t[p].l
#define rp t[p].r

int root, tot;

int add(int k) {
	t[++tot] = {0, 0, k, 1, rand(), 0};
	return tot;
}

void pushup(int p) {
	t[p].siz = t[lp].siz + t[rp].siz + 1;
}

void pushdown(int p) {
	if(t[p].tag) {
		swap(lp, rp);
		t[lp].tag ^= 1;
		t[rp].tag ^= 1;
		t[p].tag = 0;
	}
}

void split(int p, int k, int &x, int &y) {
	if(!p) {
		x = y = 0;
		return ;
	}
	pushdown(p);
	if(k <= t[lp].siz) {
		y = p;
		split(lp, k, x, lp);
	}
	else {
		x = p;
		split(rp, k - t[lp].siz - 1, rp, y);
	}
	pushup(p);
}

int merge(int x, int y) {
	if(!x || !y) {
		return x + y;
	}
	if(t[x].key < t[y].key) {
		pushdown(x);
		t[x].r = merge(t[x].r, y);
		pushup(x);
		return x; 
	}
	else {
		pushdown(y);
		t[y].l = merge(x, t[y].l);
		pushup(y);
		return y;
	}
}

void print(int p) {
	if(!p) return ;
	pushdown(p);
	print(lp);
	cout << t[p].val << " ";
	print(rp);
}

int n, m;

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		root = merge(root, add(i));
	} 
	while(m--) {
		int l, r;
		cin >> l >> r;
		int x, y, z;
		split(root, r, x, z);
		split(x, l - 1, x, y);
		t[y].tag ^= 1;
		root = merge(merge(x, y), z);
	}
	print(root);
	return 0;
}