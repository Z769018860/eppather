#include<iostream>
#include<cstdio>
#define fopen(x) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout); 
#define mod 998244353
#define maxn 500005

using namespace std;

int n, q, type, op, x, y, a[maxn], ansx, ansy;

struct frac {
	int ax, a, bx, b;
	int operator=(int x) {
		bx = ax = 0;
		b = 1;
		return a = x;
	} 
	frac operator+(int y) {
		frac c = *this;
		swap(c.ax, c.bx);
		swap(c.a, c.b);
		c.ax = ((long long)c.ax + (long long)c.bx * y % mod) % mod;
		c.a = ((long long)c.a + (long long)c.b * y % mod) % mod;
		return c;
	}
	frac operator*(int x) {
		frac c = *this;
		c.ax = (long long)c.ax * x % mod;
		c.a *= (long long)c.a * x % mod;
		return c;
	}
	frac dairu(frac y) {
		frac c;
		c.ax = ((long long)ax * y.ax % mod + (long long)bx * y.a % mod) % mod;
		c.a = ((long long)a * y.ax % mod + (long long)b * y.a % mod) % mod;
		c.bx = ((long long)ax * y.bx % mod + (long long)bx * y.b % mod) % mod;
		c.b = ((long long)a * y.bx % mod + (long long)b * y.b % mod) % mod;
		return c;
	}
} x0, one, f[1000005][21];

void init() {
	for(int j = 1; j <= 19; j++) {
		for(int i = (1 << j); i <= n; i++) {
			f[i][j] = f[i][j - 1].dairu(f[i - (1 << (j - 1))][j - 1]);
		}
	}
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(0);
	x0 = (frac){1, 0, 0, 1};
	one = (frac){0, 1, 0, 1};
	cin >> n >> q >> type;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		f[i][0] = x0 + a[i];
	}
	init();
	while(q--) {
		cin >> op;
		if(op == 1) {
			cin >> x;
			if(type)x ^= (ansx ^ ansy);
			n++;
			f[n][0] = x0 + x;
			for(int i = 1; i <= 19; i++) {
				if(n >= (1 << i)) {
					f[n][i] = f[n][i - 1].dairu(f[n - (1 << (i - 1))][i - 1]);
				}
			}
		}
		else {
			frac frc = x0;
			cin >> x >> y;
			if(type)x = x ^ (ansx ^ ansy);
			if(type)y = y ^ (ansx ^ ansy);
			int i = y;
			x--;
			for(int j = 19; j >= 0; j--) {
				if(i - (1 << j) >= x)  {
					frc = frc.dairu(f[i][j]);
					i -= (1 << j);
				}
			}
			ansx = frc.ax, ansy = frc.bx;
			cout << ansx << ' ' << ansy << '\n';
		}
	}
}