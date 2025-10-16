#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
const int N = 2e5 + 3;

int n, m;
int arr[N];
int qx[N], qy[N];
int apps[N << 2], apc = 0;

void read() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> arr[i], apps[apc++] = arr[i];
	for (int i = 1; i <= m; ++i) {
		cin >> qx[i] >> qy[i];
		apps[apc++] = qx[i], apps[apc++] = qy[i];
	}
}

void discrete() {
	sort(apps, apps + apc);
	int *ae = unique(apps, apps + apc); apc = ae - apps;
	for (int i = 1; i <= n; ++i) arr[i] = lower_bound(apps, ae, arr[i]) - apps;
	for (int i = 1; i <= m; ++i) {
		qx[i] = lower_bound(apps, ae, qx[i]) - apps;
		qy[i] = lower_bound(apps, ae, qy[i]) - apps;
	}
}

int gmin = 2147483647;
set<int> whr[N];
inline void insert(int i, int x) {
	auto prv = whr[x].insert(i).first;
	auto nxt = prv--, it = nxt++;

	if (it != whr[x].begin())
		gmin = min(gmin, *it - *prv);

	if (nxt != whr[x].end())
		gmin = min(gmin, *nxt - *it);
}

inline void merge(int x, int y) {
	if (whr[x].size() < whr[y].size()) swap(whr[x], whr[y]);
	for (auto i : whr[y]) insert(i, x);
	whr[y].clear();
}

int main() {
	read();
	discrete();
	for (int i = 1; i <= n; ++i) insert(i, arr[i]);
	for (int i = 1; i <= m; ++i) {
		if (gmin > 1) merge(qy[i], qx[i]);
		cout << gmin << '\n';
	}
	return 0;
}
