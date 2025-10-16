

#include <chrono>
#include <random>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define eputchar(c) putc(c, stderr)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define eputs(str) fputs(str, stderr), putc('\n', stderr)
using namespace std;

const int mod = 998244353;

mt19937 gen(chrono::system_clock::now().time_since_epoch().count());

int n, m, x[20005], y[20005], v[20005], b[2505];
int u[2505], f[5005][2505];
int k, c[5005], r[2505], lstr[2505], tmpr[2505];
int ans[2505];

int power(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1) ans = (long long)ans * a % mod;
		a = (long long)a * a % mod;
		b >>= 1;
	}
	return ans % mod;
}
void BM() {
	int p = -1, delta = 0, lstk = 0;
	k = 1, r[0] = 1;
	for (int i = 0; i < 2 * n; i++) {
		int tmp = 0;
		for (int j = 0; j < k; j++) tmp = (tmp + (long long)c[i - j] * r[j]) % mod;
		if (tmp == 0) continue;
		if (p == -1) {
			p = i, delta = tmp;
			lstk = 1, lstr[0] = 1;
			k = i + 2;
			continue;
		}
		memcpy(tmpr, r, sizeof(tmpr));
		int _t = (mod - (long long)tmp * power(delta, mod - 2) % mod) % mod;
		for (int j = 0; j < lstk; j++)
			r[i - p + j] = (r[i - p + j] + (long long)_t * lstr[j]) % mod;
		memcpy(lstr, tmpr, sizeof(lstr));
		int tmpk = k;
		if (i - p + lstk >= k) {
			k = i - p + lstk;
			lstk = tmpk;
			p = i;
			delta = tmp;
		}
	}
	return ;
}

int main() {
	
	
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int w;
			scanf("%d", &w);
			if (w) m++, x[m]= i, y[m] = j, v[m] = w;
		}
		scanf("%d", &b[i]);
	}
	for (int i = 1; i <= n; i++) u[i] = gen() % mod;
	memcpy(f[0], b, sizeof(f[0]));
	for (int i = 0; i < 2 * n; i++) {
		for (int j = 1; j <= n; j++) c[i] = (c[i] + (long long)u[j] * f[i][j]) % mod;
		for (int j = 1; j <= m; j++)
			f[i + 1][x[j]] = (f[i + 1][x[j]] + (long long)v[j] * f[i][y[j]]) % mod;
	}
	BM();
	for (int i = 0; i <= k - 2; i++)
		for (int j = 1; j <= n; j++) ans[j] = (ans[j] + (long long)f[i][j] * r[k - 2 - i]) % mod;
	int inv = power(r[k - 1], mod - 2);
	for (int i = 1; i <= n; i++) printf("%lld ", (mod - (long long)ans[i] * inv % mod) % mod);
	puts("");
	return 0;
}