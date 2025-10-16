#include <iostream>
#define int long long
using namespace std;

int n;
int tree[8000010];
int sum[1000010];

int lowbit(int x) { return x&-x; }

void upd(int x, int y) {
	while (x <= n) {
		tree[x] += y;
		x += lowbit(x);
	}
}

int que(int x) {
	int ans = 0;
	while (x) {
		ans += tree[x];
		x -= lowbit(x);
	}
	return ans;
}

signed main() {
	cin >> n;
	sum[0] = 1;
	for (int i = 1; i <= n; i++) {
		upd(i, 1);
		sum[i] = (sum[i-1]*i)%998244353;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		ans = (ans+(que(x)-1)*sum[n-i]%998244353)%998244353;
		upd(x, -1);
	}
	cout << ans+1;
}