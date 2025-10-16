#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); ++i)
#define FR(i, a, b) for(int i = (a); i >= (b); --i)
using namespace std;
constexpr int N = 3010, p = 998244353;
int n, m, x[N], y[N], s[N];
int Qpow(int a, int b){
    return !b? 1 : ((b & 1)? 1ll * a : 1ll) * Qpow(1ll * a * a % p, b >> 1) % p;
}
int Inv(int x){return Qpow(x % p, p - 2);}
int main(){
    scanf("%d", &m);
    while(m--){
        int op; scanf("%d", &op);
        if(op == 1){
            ++n, scanf("%d%d", &x[n], &y[n]), s[n] = 1;
            FL(i, 1, n - 1){
                s[n] = 1ll * s[n] * (x[n] - x[i] + p) % p;
                s[i] = 1ll * s[i] * (x[i] - x[n] + p) % p;
            }
        }
        else{
            int k, v = 1, ans = 0; scanf("%d", &k);
            FL(i, 1, n) if(k == x[i]){printf("%d\n", y[i]), v = 0; break;}
            if(!v) continue; FL(i, 1, n) v = 1ll * v * (k - x[i] + p) % p;
            FL(i, 1, n) (ans += 1ll * v * Inv(k - x[i] + p) % p * Inv(s[i]) % p * y[i] % p) %= p;
            printf("%d\n", ans);
        }
    }
    return 0;
}