#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using ll = long long;
const int N = 2e5 + 5, M = 5e5 + 5;
int n, m;
struct edge{
	int u, v, k;
	ll w;
	friend bool operator < (const edge &a, const edge &b){
		if (a.w != b.w) return a.w > b.w;
		else return a.k < b.k;
	}
}e[M], a[M], b[M], c[M << 1];
int fa[N]; int getfa(int x){return x == fa[x] ? x : fa[x] = getfa(fa[x]);}
pair<ll, int> check(ll _b){
	for (int i = 1; i <= m; i++){
		a[m - i + 1] = edge{e[i].u, e[i].v, -1, -e[i].w + _b};
		b[i] = edge{e[i].u, e[i].v, 1, e[i].w};
	}
	merge(a + 1, a + 1 + m, b + 1, b + 1 + m, c + 1);
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	pair<ll, int> res(0, 0);
	for (int i = 1, j = 0; i <= 2 * m && j < (n - 1) - (n - 1) % 2; i++){
		int u = getfa(c[i].u), v = getfa(c[i].v);
		if (u != v){
			fa[u] = v;
			res.first += c[i].w;
			if (c[i].k == -1) res.second++;
			j++;
		}
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);


	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> e[i].u >> e[i].v >> e[i].w;
	sort(e + 1, e + 1 + m);
	ll l = 0, r = 2e9, mid, ans = -1;
	while (l <= r){
		mid = (l + r) >> 1;
		pair<ll, int> res = check(mid);
		if (res.second >= (n - 1) / 2) r = mid - 1, ans = res.first - mid * ((n - 1) / 2);
		else l = mid + 1;
	}
	cout << ans;
	return 0;
}