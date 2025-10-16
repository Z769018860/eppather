#include<bits/stdc++.h>
#define L(i, j, k) for(int i = (j); i <= (k); ++i)
#define R(i, j, k) for(int i = (j); i >= (k); --i)
#define ll long long
#define sz(a) ((int) (a).size())
#define vi vector < int >
#define me(a, x) memset(a, x, sizeof(a))
#define ull unsigned long long
#define ld __float128
#define pb emplace_back
using namespace std;
const int N = 1 << 20, mod = 998244353;
int n;
int a[N], b[N];
#define VP vector < pair < int, int > > 
int ans[N];
pair < int, int > mx[N];
void build(int x, int L, int R) {
	if(L == R)return mx[x] = {b[L], L}, void();
	int mid = (L + R) >> 1;
	build(x * 2, L, mid), build(x * 2 + 1, mid + 1, R);
	mx[x] = min(mx[x * 2], mx[x * 2 + 1]);
}
pair < int, int > query(int x, int L, int R, int l, int r) {
	if(l <= L && R <= r) return mx[x];
	pair < int, int > dm = {n + 1, 0};
	int mid = (L + R) >> 1;
	if(l <= mid)dm = min(dm, query(x * 2, L, mid, l, r));
	if(r > mid)dm = min(dm, query(x * 2 + 1, mid + 1, R, l, r));
	return dm;
}
void upd(int x, int L, int R, int p) {
	if(L == R)return mx[x] = {n + 1, 0}, void();
	int mid = (L + R) >> 1;
	p <= mid ? upd(x * 2, L, mid, p) : upd(x * 2 + 1, mid + 1, R, p);
	mx[x] = min(mx[x * 2], mx[x * 2 + 1]);
}
int mn[N], tag[N];
void add(int x, int L, int R, int l, int r, int w) {
	if(l <= L && R <= r) return tag[x] += w, mn[x] += w, void();
	int mid = (L + R) >> 1;
	if(l <= mid)add(x * 2, L, mid, l, r, w);
	if(r > mid)add(x * 2 + 1, mid + 1, R, l, r, w);
	mn[x] = min(mn[x * 2], mn[x * 2 + 1]) + tag[x];
}
inline int getp(int x, int L, int R) {
	if(L == R)return L;
	int mid = (L + R) >> 1;
	return mn[x * 2] < mn[x * 2 + 1] ? getp(x * 2, L, mid) : getp(x * 2 + 1, mid + 1, R);
}
int main() {
	ios :: sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	L(i, 1, n) {
		cin >> a[i];
	}
	L(i, 1, n) {
		cin >> b[i];
	}
	build(1, 1, n);
	R(i, n, 1) {
		add(1, 0, n, a[i], n, 1);
		int lst = getp(1, 0, n) + 1;
		pair < int, int > pr = query(1, 1, n, lst, n);
		ans[i] = pr.first;
		upd(1, 1, n, pr.second);
		add(1, 0, n, pr.second, n, -1);
	}
	L(i, 1, n) {
		cout << ans[i] << " \n"[i == n];
	}
	return 0;
} 