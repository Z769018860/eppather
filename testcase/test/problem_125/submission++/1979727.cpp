#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int n, ans;
inline int calc(int n) {
    int a = n, b = n + 1, c = 2 * n + 1;
    if(a % 2 == 0)a /= 2;
    else if(b % 2 == 0)b /= 2;
    else c /= 2;
    if(a % 3 == 0)a /= 3;
    else if(b % 3 == 0)b /= 3;
    else c /= 3;
    return 1ll * a * b % mod * c % mod;
}
int main(){
    cin >> n;
    for(int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        int tmp = 5ll * (r - l + 1) % mod;
        tmp = (tmp + 3ll * (r + l) * (r - l + 1) / 2) % mod;
        tmp = (tmp + 2ll * (calc(r) - calc(l-1) + mod)) % mod;
        ans = (ans + 1ll * tmp * (n / l)) % mod;
    }
    printf("%d\n", ans);
    return 0;
}