#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int maxN = 1e5 + 5;

int n;
ll w[maxN], p[maxN];

void write(__int128 x) {
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}

int main() {


	


	
	cin >> n;
	for (int i = 1; i <= n; ++i) scanf("%lld", w + i), p[i] = w[i];
	__int128 ans = 0;
	for (int i = 1; i <= n; ++i) ans += (__int128) w[i] * w[i];
	ans *= 2;

	sort(p + 1, p + 1 + n, [&](ll a, ll b) {
		return a > b;
	});
	int W;
	if (n & 1) W = (n + 1) / 2;
	else W = n / 2 + 1;
	int tmp = 2;
	for (int i = W - 1; i; --i, tmp += 2) w[i] = p[tmp];
	tmp = 1;
	for (int i = W; i <= n; ++i, tmp += 2) w[i] = p[tmp];
	w[n + 1] = w[1];
	__int128 sum = 0;


	for (int i = 1; i <= n; ++i) sum += (__int128) w[i] * w[i + 1];
	write(ans - 2 * sum);
	
	return 0;
}