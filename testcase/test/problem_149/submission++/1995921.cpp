#include<bits/stdc++.h>
using namespace std;
#define ll long long
constexpr int N = 1e5 + 5;
constexpr double eps = 1e-8;
int n, k, a[N], b[N];
double tmp[N];
inline bool check(double lim)
{
	for (int i = 1; i <= n; ++i) {
		tmp[i] = a[i] / lim - b[i];
	}
	sort(tmp + 1, tmp + 1 + n, greater<double>());
	double sum = 0;
	for (int i = 1; i <= k; ++i) sum += tmp[i];
	return sum >= 0;
}
int main()
{
#ifdef IAKIOI
	freopen("in.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) cin >> b[i];
	double l = eps, r = 1;
	while (r - l > eps) {
		double mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	cout << fixed << setprecision(10) << l << endl;
	return 0;
}