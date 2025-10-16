#include<iostream>
using namespace std;
const int N = 5000;
typedef long long ll;
int n, m;
ll a[N][N];
void add(int x, int y, int v) {
	for (int i = x; i <= n; i += i & -i) {
		for (int j = y; j <= m; j += j & -j) {
			a[i][j] += (ll)v;
		}
	}
}
void add_() {
	int x1, y1, x2, y2, v;
	scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
	add(x1, y1, v);
	add(x1, y2 + 1, -v);
	add(x2 + 1, y1, -v);
	add(x2 + 1, y2 + 1, v);
}
void ask() {
	ll sum = 0;
	int x, y;
	scanf("%d%d", &x, &y);
	for (int i = x; i; i -= i & -i) {
		for (int j = y; j; j -= j & -j) {
			sum += a[i][j];
		}
	}
	printf("%lld\n", sum);
}
int main() {
	scanf("%d%d", &n, &m);
	int op = -1;
	while (~scanf("%d", &op)) {
		if (op == 1) {
			add_();
		}
		else {
			ask();
		}
	}
}