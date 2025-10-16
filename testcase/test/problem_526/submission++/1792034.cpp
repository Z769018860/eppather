#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 505;
int n, a[MAXN], match[MAXN];
bool vis[MAXN];
vector<int> G[MAXN]; 
inline int gcd (const int &a, const int &b) { return !b ? a : gcd(b, a % b); }
inline bool dfs (const int &u) {
	for (int v : G[u]) if (!vis[v]) {
		vis[v] = true;
		if (!match[v] || dfs(match[v]))
			return match[v] = u, true;
	}
	return false;
}
inline int MaxMatch () {
	int res = 0;
	for (int i = 1; i <= n; i++) if (!(a[i] & 1)) {
		for (int j = 1; j <= n; j++) vis[j] = false;
		res += dfs(i);
	}
	return res;
} 
signed main () {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	for (int i = 1; i <= n; i++) if (!(a[i] & 1))
		for (int j = 1; j <= n; j++) if (a[j] & 1)
			if (gcd(a[i], a[j]) == 1 && gcd(a[i] + 1, a[j] + 1) == 1) {

				G[i].push_back(j);
			}
	printf("%d", n - MaxMatch());
	return 0;
}