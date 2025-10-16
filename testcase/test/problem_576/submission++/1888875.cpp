#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 100005;

int n, q;

#define ls p << 1
#define rs p << 1 | 1
int g[N << 2];
void build(int p, int l, int r) {
	if (l == r) { scanf("%d", &g[p]); return; }
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	g[p] = __gcd(g[ls], g[rs]);
}
void change(int p, int l, int r, int x, int y) {
	if (l == r) { g[p] = y; return; }
	int mid = (l + r) >> 1;
	x > mid ? change(rs, mid + 1, r, x, y) : change(ls, l, mid, x, y);
	g[p] = __gcd(g[ls], g[rs]);
}
int find(int p, int l, int r, int L, int R) {
	if (l == r) return l;
	int mid = (l + r) >> 1, pre = __gcd(g[ls], L), suf = __gcd(g[rs], R);
	return pre < suf ? find(ls, l, mid, L, suf) : find(rs, mid + 1, r, pre, R);
}
LL getp(int p, int l, int r, int x, int y) {
	if (l == r) return __gcd(g[p], y);
	int mid = (l + r) >> 1, suf = __gcd(g[rs], y);
	if (x <= mid) return getp(ls, l, mid, x, suf);
	if (g[ls] % suf == 0) return (mid - l + 1ll) * suf + getp(rs, mid + 1, r, x, y);
	return getp(ls, l, mid, x, suf) + getp(rs, mid + 1, r, x, y);
}
LL gets(int p, int l, int r, int x, int y) {
	if (l == r) return __gcd(g[p], y);
	int mid = (l + r) >> 1, pre = __gcd(g[ls], y);
	if (x > mid) return gets(rs, mid + 1, r, x, pre);
	if (g[rs] % pre == 0) return (r - mid + 0ll) * pre + gets(ls, l, mid, x, y);
	return gets(ls, l, mid, x, y) + gets(rs, mid + 1, r, x, pre);
}

int main() {
	scanf("%d%d", &n, &q), build(1, 1, n);
	while (q--) {
		int pos, val, p; scanf("%d%d", &pos, &val);
		change(1, 1, n, pos, val), p = find(1, 1, n, 0, 0);
		printf("%lld\n", getp(1, 1, n, p, 0) + gets(1, 1, n, p, 0) - g[1]);
	}
	return 0;
}