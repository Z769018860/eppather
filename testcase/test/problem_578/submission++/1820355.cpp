#include <stdio.h>

typedef long long ll;

typedef struct {
	int l;
	int r;
	int ls;
	int rs;
	int cur_match_cnt;
	int lb_cnt;
	int rb_cnt;
	ll lb_match_sum;
	ll rb_match_sum;
	ll lb_sum;
	ll rb_sum;
	ll match_sum;
} Node;

int id = 0, root;
int a[100007], cnt[200007];
Node tree[4400007];

inline int min(int a, int b){
	return a < b ? a : b;
}

ll get_rb(int x, int k){
	if (tree[x].l == tree[x].r) return (ll)k * tree[x].l;
	int ls = tree[x].ls;
	if (k <= tree[ls].rb_cnt) return get_rb(ls, k);
	return get_rb(tree[x].rs, k - (tree[ls].rb_cnt - tree[x].cur_match_cnt)) + tree[ls].rb_sum - tree[x].rb_match_sum;
}

ll get_lb(int x, int k){
	if (tree[x].l == tree[x].r) return (ll)k * tree[x].l;
	int rs = tree[x].rs;
	if (k <= tree[rs].lb_cnt) return get_lb(rs, k);
	return get_lb(tree[x].ls, k - (tree[rs].lb_cnt - tree[x].cur_match_cnt)) + tree[rs].lb_sum - tree[x].lb_match_sum;
}

inline int merge(int x, int y){
	int ans = ++id;
	tree[ans].l = tree[x].l;
	tree[ans].r = tree[y].r;
	tree[ans].ls = x;
	tree[ans].rs = y;
	tree[ans].cur_match_cnt = min(tree[x].lb_cnt, tree[y].rb_cnt);
	tree[ans].lb_cnt = tree[x].lb_cnt + tree[y].lb_cnt - tree[ans].cur_match_cnt;
	tree[ans].rb_cnt = tree[x].rb_cnt + tree[y].rb_cnt - tree[ans].cur_match_cnt;
	if (tree[ans].cur_match_cnt == tree[x].lb_cnt){
		tree[ans].lb_match_sum = tree[x].lb_sum;
		tree[ans].rb_match_sum = get_rb(y, tree[ans].cur_match_cnt);
	} else {
		tree[ans].lb_match_sum = get_lb(x, tree[ans].cur_match_cnt);
		tree[ans].rb_match_sum = tree[y].rb_sum;
	}
	tree[ans].lb_sum = tree[x].lb_sum + tree[y].lb_sum - tree[ans].lb_match_sum;
	tree[ans].rb_sum = tree[x].rb_sum + tree[y].rb_sum - tree[ans].rb_match_sum;
	tree[ans].match_sum = tree[x].match_sum + tree[y].match_sum + tree[ans].lb_match_sum + tree[ans].rb_match_sum;
	return ans;
}

int build(int l, int r){
	if (l == r){
		int ans = ++id;
		tree[ans].l = tree[ans].r = l;
		if (cnt[l] == 0){
			tree[ans].lb_cnt = 1;
			tree[ans].lb_sum = l;
		} else {
			tree[ans].cur_match_cnt = 1;
			tree[ans].rb_cnt = cnt[l] - 1;
			tree[ans].lb_match_sum = tree[ans].rb_match_sum = l;
			tree[ans].rb_sum = (ll)l * tree[ans].rb_cnt;
			tree[ans].match_sum = l * 2;
		}
		return ans;
	}
	int mid = (l + r) >> 1;
	return merge(build(l, mid), build(mid + 1, r));
}

void modify(int &x, int pos){
	if (tree[x].l == tree[x].r){
		if (cnt[pos] == 0){
			tree[x].cur_match_cnt = 0;
			tree[x].lb_cnt = 1;
			tree[x].rb_cnt = 0;
			tree[x].lb_match_sum = tree[x].rb_match_sum = 0;
			tree[x].lb_sum = pos;
			tree[x].rb_sum = 0;
			tree[x].match_sum = 0;
		} else {
			tree[x].cur_match_cnt = 1;
			tree[x].lb_cnt = 0;
			tree[x].rb_cnt = cnt[pos] - 1;
			tree[x].lb_match_sum = tree[x].rb_match_sum = pos;
			tree[x].lb_sum = 0;
			tree[x].rb_sum = (ll)pos * tree[x].rb_cnt;
			tree[x].match_sum = pos * 2;
		}
		return;
	}
	if (pos <= tree[tree[x].ls].r){
		modify(tree[x].ls, pos);
	} else {
		modify(tree[x].rs, pos);
	}
	x = merge(tree[x].ls, tree[x].rs);
}

int query(int x, int l, int r){
	if (l <= tree[x].l && tree[x].r <= r) return x;
	int mid = (tree[x].l + tree[x].r) >> 1;
	if (r <= mid) return query(tree[x].ls, l, r);
	if (l > mid) return query(tree[x].rs, l, r);
	return merge(query(tree[x].ls, l, r), query(tree[x].rs, l, r));
}

inline ll query(int l, int r){
	if (l > r) return 0;
	return tree[query(root, l, r)].match_sum;
}

int main(){
	int n, q, m;
	scanf("%d %d", &n, &q);
	m = n * 2;
	for (register int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		cnt[a[i]]++;
	}
	root = build(1, m);
	for (register int I = 1; I <= q; I++){
		int op;
		scanf("%d", &op);
		if (op == 1){
			int i, v;
			scanf("%d %d", &i, &v);
			cnt[a[i]]--;
			modify(root, a[i]);
			a[i] = v;
			cnt[v]++;
			modify(root, v);
		} else {
			int l, r, t = id;
			scanf("%d %d", &l, &r);
			printf("%lld\n", query(1, m) - query(l + 1, m) - query(1, r - 1) + query(l + 1, r - 1));
			id = t;
		}
	}
	return 0;
}