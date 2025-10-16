#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1e5 + 5, M = 3e5 + 5, SN = 1.5e7 + 5;

int n, q, X[N], Y[N], op[M], nx[M], ny[M], s[N], ans[M];

int idx, ls[SN], rs[SN], val[SN];
void update(int &p, int L, int R, int l, int r, int d) {
	if (!p) p = ++idx;
	if (l <= L && r >= R) return val[p] += d, void();
	int mid = L + R >> 1;
	if (l <= mid) update(ls[p], L, mid, l, r, d);
	if (r > mid) update(rs[p], mid + 1, R, l, r, d);
}
int query(int p, int L, int R, int x) {
	if (!p) return 0;
	if (L == R) return val[p];
	int mid = L + R >> 1, res = val[p];
	if (x <= mid) res += query(ls[p], L, mid, x);
	else res += query(rs[p], mid + 1, R, x);
	return res;
}

void solve(int *a, int *ud) {
	s[0] = 1; for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
	int rt = 0, res, pos = 1, dt = 0;
	for (int i = 1; i < n; i++) update(rt, -5e7, 5e7, min(s[i], s[i + 1]), max(s[i], s[i + 1]), 1);
	res = query(rt, -5e7, 5e7, 0);
	if (s[1] < 0) res++;
	for (int i = 1; i <= q; i++) {
		if (!op[i]) {
			if (pos == 1) continue;
			s[--pos] -= dt;
			update(rt, -5e7, 5e7, min(s[pos], s[pos + 1]), max(s[pos], s[pos + 1]), 1);
		}
		if (op[i] == 1) {
			if (pos == n) continue;
			update(rt, -5e7, 5e7, min(s[pos], s[pos + 1]), max(s[pos], s[pos + 1]), -1);
			s[pos++] += dt;
		}
		if (op[i] == 2) {
			res -= query(rt, -5e7, 5e7, -dt);
			if (1ll * s[pos - 1] * (s[pos] + dt) < 0) res--;
			dt += ud[i] - a[pos], a[pos] = ud[i];
			res += query(rt, -5e7, 5e7, -dt);
			if (1ll * s[pos - 1] * (s[pos] + dt) < 0) res++;
		}
		if (op[i] == 3) ans[i] += res;
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d %d", &X[i], &Y[i]);
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		char c;
		scanf("\n%c", &c);
		if (c == 'F') op[i] = 1;
		if (c == 'C') op[i] = 2, scanf("%d %d", &nx[i], &ny[i]);
		if (c == 'Q') op[i] = 3;
	}
	solve(X, nx), solve(Y, ny);
	for (int i = 1; i <= q; i++)
		if (op[i] == 3) printf("%d\n", ans[i]);
	return 0;
}