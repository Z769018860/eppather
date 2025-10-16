#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1000005, M = 1005;

LL a[N];    
LL b[M];    
LL s[M];    
int id[N];  

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, opt, l, r, c;
    cin >> n >> m;
    LL d = sqrt(n);
    for (int i = 0; i < n; i++) id[i] = i / d, cin >> a[i], s[id[i]] += a[i];  
    for (int t = 0; t < m; t++) {
        cin >> opt >> l >> r;
        l--, r--;  
        if (opt == 1) {
            cin >> c;
            if (id[l] == id[r]) {
                for (int i = l; i <= r; i++) a[i] += c, s[id[i]] += c;
            } else {
                for (int i = l; id[i] == id[l]; i++) a[i] += c, s[id[i]] += c;  
                for (int i = r; id[i] == id[r]; i--) a[i] += c, s[id[i]] += c;  
                for (int i = id[l] + 1; i < id[r]; i++) s[i] += d * c, b[i] += c;
            }
        } else {
            LL ans = 0;
            if (id[l] == id[r]) {
                for (int i = l; i <= r; i++) ans += a[i] + b[id[i]];
            } else {
                for (int i = l; id[i] == id[l]; i++) ans += a[i] + b[id[i]];  
                for (int i = r; id[i] == id[r]; i--) ans += a[i] + b[id[i]];  
                for (int i = id[l] + 1; i < id[r]; i++) ans += s[i];
            }
            cout << ans << '\n';
        }
    }
    return 0;
}