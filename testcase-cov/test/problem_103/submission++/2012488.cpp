#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++ )

using namespace std;

using LL = long long;
const int B = 1331;
const int P = 998244353;
const int N = 1000010;
LL h1[N], h2[N], p[N]; int n, m, ans;
char a[N], b[N];
int get_hash(int l, int r) { return (h1[r] - 1ll * h1[l - 1] * p[r - l + 1] % P + P) % P; }
int main() {
	scanf("%s", a + 1); n = strlen(a + 1);
	scanf("%s", b + 1); m = strlen(b + 1);
	rep(i, 1, n) h1[i] = (1ll * h1[i - 1] * B + a[i]) % P;
	p[0] = 1ll; rep(i, 1, n) p[i] = 1ll * p[i - 1] * B % P;
	rep(i, 1, m) h2[i] = (1ll * h2[i - 1] * B + b[i]) % P;
	rep(i, 1, n - m + 1) ans += (get_hash(i, i + m - 1) == h2[m]);
	printf("%d\n", ans); return 0;
}