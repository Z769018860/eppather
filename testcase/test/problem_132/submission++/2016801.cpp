#include <bits/stdc++.h>
#define int long long
#define lc (id << 1)
#define rc (id << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

const int N = 1e6 + 10;

int n, q;
int a[N];

int s[N << 2], lazy[N << 2];

void pushdown(int id, int l, int r){
	int &t = lazy[id];
	if (t){
		lazy[lc] += t;
		lazy[rc] += t;
		s[lc] += t * (mid - l + 1);
		s[rc] += t * (r - mid);
		t = 0;
	}
}

void pushup(int id){
	s[id] = s[lc] + s[rc];
}

void build(int id, int l, int r){
	if (l == r){
		s[id] = a[l];
		return ;
	}
	build(lc, l, mid), build(rc, mid + 1, r);
	pushup(id);
}

void update(int id, int l, int r, int x, int y, int v){
	if (x <= l && r <= y){
		s[id] += v * (r - l + 1);
		lazy[id] += v;
		return ;
	} pushdown(id, l, r);
	if (x <= mid) update(lc, l, mid, x, y, v);
	if (y > mid) update(rc, mid + 1, r, x, y, v);
	return pushup(id), void();
}

int query(int id, int l, int r, int x, int y, int ans = 0){
	if (x <= l && r <= y){
		return s[id];
	} pushdown(id, l, r);
	if (x <= mid) ans += query(lc, l, mid, x, y);
	if (y > mid) ans += query(rc, mid + 1, r, x, y);
	return ans;
	
}

signed main(){
	
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> a[i]; build(1, 1, n);
	
	for (int op, l, r, x; q--; ){
		cin >> op >> l >> r;
		if (op == 1) cin >> x, update(1, 1, n, l, r, x);
		if (op == 2) cout << query(1, 1, n, l, r) << endl;
	}
	
	return 0;
}