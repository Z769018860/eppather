
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

template <typename T> bool chkMax(T &x, T y) { return (y > x) ? x = y, 1 : 0; }
template <typename T> bool chkMin(T &x, T y) { return (y < x) ? x = y, 1 : 0; }

template <typename T> void inline read(T &x) {
    int f = 1; x = 0; char s = getchar();
    while (s < '0' || s > '9') { if (s == '-') f = -1; s = getchar(); }
    while (s <= '9' && s >= '0') x = x * 10 + (s ^ 48), s = getchar();
    x *= f;
}

const int N = 300;

LL f[N], k;

int p;

int main() {
	f[0] = 1;
	for (int i = 0; i < N; i++) {
		if (f[i] > 1e18) {
			p = i;
			break;
		}
		for (int j = 1; i + j < N; j++) {
			chkMax(f[i + 1 + j], f[i] * j);
		}
	}
    int T; read(T);
    while (T--) {
    	read(k);
    	for (int i = 2; i <= p; i++) {
    		if (f[i] >= k) {
    			printf("%d\n", i * 2);
    			break;
    		}
    	}
    }
    return 0;
}