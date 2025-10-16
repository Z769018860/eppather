#include <bits/stdc++.h>
using namespace std;
#define add(x, y) (x >= mod - y ? x + y - mod : x + y)
#define sub(x, y) (x < y ? x - y + mod : x - y)
const int mod = 167772161;
const int N = 2097153;
int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = 1LL * res * a % mod;
        }
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return res;
}
namespace Poly {
    int w[N];
    int preW = 0;
    int getLen(int x) {
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return x + 1;
    }
    const int inv2 = qpow(2, mod - 2);
    void init(int len) {
        if (len <= preW) {
            return;
        }
        preW = len;
        for (int i = 1, j ; i < len ; i *= 2) {
        	long long k = qpow(3, (mod - 1) / (2 * i));
            for (w[j = i] = 1, j++ ; j < 2 * i ; j++) {
                w[j] = w[j - 1] * k % mod;
            }
        }
    }
void DNT(int *a, int len) {
    for (int k = len / 2 ; k > 0 ; k /= 2) {
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
    int NTT(int *a, int *b, int n, int m) {
        int len = getLen(n + m);
        init(len);
        DNT(a, len);
        DNT(b, len);
        for (int i = 0 ; i < len ; i++) {
            a[i] = 1LL * a[i] * b[i] % mod;
        }
        IDNT(a, len);
        return len;
    }
} 
using Poly::NTT;
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