#include <bits/stdc++.h>
#define rep(i, n) for (int i = 1; i <= (n); ++i)
using namespace std;
typedef pair<int, int> PII;
typedef long long ll;
const int N = 1e6 + 10;
const ll INF = 2e18;
int n, m;
int a[N];
ll sum[N], tmp[N];
ll f[N];
int main(void)
{
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)cin >> a[i];
	for (int i = 1; i <= n; ++i) {
		int x; cin >> x;
		sum[i] = sum[i - 1] + x;
	}
	for (int i = 1; i <= m; ++i)tmp[i] = -INF;
	for (int i = 1; i <= n; ++i) {
		f[i] = max(f[i - 1], sum[i] + tmp[a[i]]);
		tmp[a[i]] = max(tmp[a[i]], f[i - 1] - sum[i - 1]);
	}
	cout << f[n] << endl;
	return 0;
}
