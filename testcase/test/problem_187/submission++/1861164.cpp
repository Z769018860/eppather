#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int n, m, k, a[N];
vector<pair<int, int>> e[N];
int dis[N][1510], ans = 1e9;
queue<pair<int, int>> q;
bool inq[N][1510];

void push(int x, int y) {
	if(inq[x][y]) return ;
	inq[x][y] = 1, q.push({x, y});
}
int main() {
	ios::sync_with_stdio(0); cin.tie(nullptr);
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i++) {
		int x, y, z; cin >> x >> y >> z;
		e[x].push_back({y, z}), e[y].push_back({x, z});
	}
	for(int i = 1; i <= k; i++) cin >> a[i];
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < (1 << k); j++)
			dis[i][j] = 1e9;
	for(int i = 1; i <= n; i++) {
		int state = 0;
		for(int j = 1; j <= k; j++)
			if(i == a[j]) state |= (1 << (j - 1));
		dis[i][0] = dis[i][state] = 0;
		push(i, 0), push(i, state);
	}
	for(; !q.empty();) {
		int ux = q.front().first, uy = q.front().second;
		q.pop(), inq[ux][uy] = 0;
		for(auto v : e[ux]) {
			if(dis[v.first][uy] <= dis[ux][uy] + v.second) continue;
			dis[v.first][uy] = dis[ux][uy] + v.second;
			push(v.first, uy);
		}
		int full = (1 << k) - 1 - uy;
		for(int state = full; state; state = full & (state - 1)) {
			if(dis[ux][uy | state] <= dis[ux][uy] + dis[ux][state]) continue;
			dis[ux][uy | state] = dis[ux][uy] + dis[ux][state];
			push(ux, uy | state);
		}
	}
	for(int i = 1; i <= n; i++)
		if(ans > dis[i][(1 << k) - 1])
			ans = dis[i][(1 << k) - 1];
	cout << ans << "\n";
	return 0;
}