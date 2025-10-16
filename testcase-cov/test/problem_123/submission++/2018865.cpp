#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<numeric>
using namespace std;
using ll = long long;
ll sum = 0;
const int NN = 2e5 + 4;
vector<vector<int> > G;

int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	vector<int> F(n + 2);
	iota(begin(F), end(F), 0);
	for (int i = 0, u, v, d; i < m; ++i) cin >> u >> v >> d, G.push_back({u, v, d});
	sort(begin(G), end(G), [&](vector<int>& a, vector<int>& b) {
		return a[2] < b[2];
	});
	function<int(int)> findSet = [&](int u) { return (u == F[u] ? u : (F[u] = findSet(F[u]))); };
	int cc = 0;
	for (int i = 0; i < m; ++i) {
		int u = findSet(G[i][0]), v = findSet(G[i][1]), d = G[i][2];
		if (u == v) continue;
		F[u] = v, ++cc, sum += d;
		if (cc == (n - 1)) break;
	}
	cout << sum;

	return 0;
};