

#define Ma 5000

#include <stdio.h>
#include <assert.h>
#define ll long long
#define lowbit(x) ((x)&(-(x)))

ll info[Ma][Ma];
int n, m;

void add(int x, int y, int k) {
	for (; x <= n; x += lowbit(x))
		for (int p = y; p <= m; p += lowbit(p))
			info[x][p] += k;
}

ll preQuerry(int x, int y) {
	ll ans = 0;
	for (; x; x -= lowbit(x))
		for (int p = y; p; p -= lowbit(p))
			ans += info[x][p];
	return ans;
}

ll rangeQuerry(int r1, int c1, int r2, int c2) {
	return preQuerry(r2, c2) - preQuerry(r1 - 1, c2) - preQuerry(r2, c1 - 1)
		   + preQuerry(r1 - 1, c1 - 1);
}

int main() {
	assert(scanf("%d%d", &n, &m) == 2);
	int op;
	while (~scanf("%d", &op)) {
		if (op == 1) {
			int x, y, k; 
			assert(scanf("%d%d%d", &x, &y, &k) == 3);
			add(x, y, k);
		} else {
			int a, b, c, d;
			assert(scanf("%d%d%d%d", &a, &b, &c, &d) == 4);
			printf("%lld\n", rangeQuerry(a, b, c, d));
		}
	}

	return 0;
}
