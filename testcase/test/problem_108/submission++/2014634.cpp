#include <bits/stdc++.h>
using namespace std;






const int mod = 998244353;
const int g = 3;
const int N = 262145;
int add(int x, int y) {
	return x >= mod - y ? x + y - mod : x + y;
}
int sub(int x, int y) {
	return x < y ? x - y + mod : x - y;
}
int qpow(long long a, int b) {
	long long res = 1;
	while (b) {
		if (b & 1) {
			res = res * a % mod;
		}
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
int get(int len) {
    int lenb = 1;
    while (1 << lenb <= len) {
        lenb++;
    }
    return lenb;
}
int mxlen = 0;
int w[N];
void init(int len) {
	if (len <= mxlen) return;
	for (int i = 1, j ; i < len ; i *= 2) {
		long long k = qpow(g, (mod - 1) / (2 * i));
		w[i] = 1;
        for (int j = i + 1 ; j < 2 * i ; j++) {
            w[j] = w[j - 1] * k % mod;
        }
    }
    mxlen = len;
}
void DNT(int *a, int len) {
    for (int k = len / 2 ; k >= 1 ; k /= 2) {
    	int L = k * 2;
        for (int i = 0 ; i < len ; i += L) {
            for (int j = 0 ; j < k ; j++) {
                int z = a[i + j + k];
                a[i + j + k] = 1LL * sub(a[i + j], z) * w[j + k] % mod;
                a[i + j] = add(a[i + j], z);
            }
        }
    }
}
void IDNT(int *a, int len) {
    for (int k = 1 ; k < len ; k *= 2) {
    	int L = k * 2;
        for (int i = 0 ; i < len ; i += L) {
            for (int j = 0 ; j < k ; j++) {
            	int z = 1LL * a[i + j + k] * w[j + k] % mod;
                a[i + j + k] = sub(a[i + j], z);
                a[i + j] = add(a[i + j], z);
            }
        }
    }
    reverse(a + 1, a + len);
    for (int inv = qpow(len, mod - 2), i = 0 ; i < len ; i++) {
        a[i] = 1LL * a[i] * inv % mod;
    }
}
void NTT(int *a, int *b, int n, int m) {
    int lenb = get(n + m);
    int len = 1 << lenb;
    init(len);
    DNT(a, len);
    DNT(b, len);
    for (int i = 0 ; i < len ; i++) {
        a[i] = 1LL * a[i] * b[i] % mod;
    }
    IDNT(a, len);
}
int a[N], b[N];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 0 ; i <= n ; i++) {
		cin >> a[i];
	}
	for (int i = 0 ; i <= m ; i++) {
		cin >> b[i];
	}
	NTT(a, b, n, m);
	for (int i = 0 ; i <= n + m ; i++) {
		cout << a[i] << " ";
	}
	return 0;
}