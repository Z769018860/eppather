#include<bits/stdc++.h>
#define int __int128
#define fi first
#define se second
#define MULT_TEST 0
using namespace std;
typedef unsigned long long ull;
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;
const int N = 300005, M = 105;
int s[N], a[M], mp[M];
inline int read() {
    int w = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        w = (w << 1) + (w << 3) + ch - 48;
        ch = getchar();
    }
    return w * f;
}
inline void print(int x) {
    if (x >= 10) print(x / 10);
    putchar(x % 10 + '0');
}
inline void Solve() {
    int n;
    n = read();
    for (int i = 1; i <= n; i++) {
        s[i] = read();
        if (s[i] <= 60) mp[s[i]] = 1;
    }
    int q = read();
    while (q--) {
        int ans1 = 0, ans2 = 0;
        a[0] = read(); a[1] = read(); 
        int k = read(), op = 0, mx = -1, mn = -1;
        if (a[0] == 0 && a[1] == 0) {
            print(s[1]); printf(" ");
            print(s[1]); printf("\n");
            continue;
        }
        for (int i = 0; i <= 1; i++) {
            if (mp[i]) {
                if (mx == -1 || a[mx] < a[i]) mx = i;
                if (mn == -1 || a[mn] > a[i]) mn = i; 
            }            
        }
        for (int i = 2; i <= 60; i++) {
            a[i] = k * a[i - 1] + a[i - 2];
            if (mp[i]) {
                if (a[mx] < a[i] || mx == -1) mx = i;
                if (a[mn] > a[i] || mn == -1) mn = i; 
            }
            if (i > 2 && a[i] > a[i - 1] && a[i - 1] > a[i - 2] && a[i - 2] > a[i - 3]) op = i;
            if (i > 2 && a[i] < a[i - 1] && a[i - 1] < a[i - 2] && a[i - 2] < a[i - 3]) op = -i;
            if (op) break;
        }
        if (op < 0) {
            op *= -1;
            int pos = op;
            if (mn >= 0) {
                ans2 = mn;
                for (int i = op + 1; i <= 100; i++) {
                    a[i] = k * a[i - 1] + a[i - 2];
                    if (mp[i] && (mx == -1 || a[i] > a[mx])) mx = i;
                    if (a[i] < a[mn]) {
                        pos = i;
                        break;
                    }
                }
                if (s[n] >= pos) ans2 = s[n];
            }
            else ans2 = s[n];
            if (mx >= 0) ans1 = mx;
            else ans1 = s[1];
        }
        else {
            int pos = op;
            if (mx >= 0) {
                ans1 = mx;
                for (int i = op + 1; i <= 100; i++) {
                    a[i] = k * a[i - 1] + a[i - 2];
                    if (mp[i] && (mn == -1 || a[i] < a[mn])) mn = i;
                    if (a[i] > a[mx]) {
                        pos = i;
                        break;
                    }
                }
                if (s[n] >= pos) ans1 = s[n];
            }
            else ans1 = s[n];
            if (mn >= 0) ans2 = mn;
            else ans2 = s[1];
        }
        print(ans1); printf(" ");
        print(ans2); printf("\n");
    }
}
signed main() {
    int T = 1;
#if MULT_TEST
    T = read();
#endif 
    while (T--) Solve();
    return 0;
}