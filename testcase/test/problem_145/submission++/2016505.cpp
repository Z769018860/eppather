


#include <iostream>
#include <cstdio>
#define debug(a) cerr<<"Line: "<<__LINE__<<" "#a<<endl
#define print(a) cerr<<#a"="<<(a)<<endl
#define file(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0);return Main();}signed Main
using namespace std;

#include <vector>

#define int long long

int n, m, root;
int v[1000010];

vector<int> edge[1000010];

int L[1000010], R[1000010], timer;
int l[1000010];
void dfs(int now, int fa){
	L[now] = ++timer, l[timer] = v[now];
	for (auto to:edge[now]) if (to != fa) dfs(to, now);
	R[now] = timer;
}

struct node{
	int sum;
	int lazy;
} tree[1000010 << 2];

void pushup(int idx){
	tree[idx].sum = tree[idx << 1].sum + tree[idx << 1 | 1].sum;
}

void pushdown(int idx, int left, int right){
	if (tree[idx].lazy == 0) return;
	int mid = left + right >> 1;
	tree[idx << 1].lazy += tree[idx].lazy;
	tree[idx << 1].sum += tree[idx].lazy * (mid - left + 1);
	tree[idx << 1 | 1].lazy += tree[idx].lazy;
	tree[idx << 1 | 1].sum += tree[idx].lazy * (right - mid);
	tree[idx].lazy = 0;
}

void build(int idx, int le, int ri){
	if (le == ri) return void(tree[idx] = {l[le], 0});
	int mid = le + ri >> 1;
	build(idx << 1, le, mid);
	build(idx << 1|1, mid+1, ri);
	pushup(idx);
}

void add(int idx, int le, int ri, int left, int right, int k){
	if (right < le || left > ri) return;
	if (left <= le && ri <= right){
		tree[idx].lazy += k;
		tree[idx].sum += k * (ri - le + 1);
		return;
	}
	int mid = le + ri >> 1;
	pushdown(idx, le, ri);
	add(idx << 1, le, mid, left, right, k);
	add(idx << 1 | 1, mid+1, ri, left, right, k);
	pushup(idx);
}

int query(int idx, int le, int ri, int left, int right){
	if (right < le || left > ri) return 0;
	if (left <= le && ri <= right) return tree[idx].sum;
	pushdown(idx, le, ri);
	int mid = le + ri >> 1;
	return query(idx << 1, le, mid, left, right) + 
		   query(idx << 1 | 1, mid+1, ri, left, right);
}

signed main(){
	cin >> n >> m >> root;
	for (int i=1;i<=n;++i) cin >> v[i];
	for (int i=1;i<=n-1;++i){
		int u, v; cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(root, 0);
	build(1, 1, timer);
	
	
	for (int i=1;i<=m;++i){
		int op, a, x; cin >> op;
		if (op == 1){
			cin >> a >> x;
			add(1, 1, timer, L[a], R[a], x);
		} else {
			cin >> a;
			#ifdef LOCAL
			cout << ">>>>>";
			#endif
			cout << query(1, 1, timer, L[a], R[a]) << endl;
		}
	}
	
	return 0;
}
