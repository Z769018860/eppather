#include <iostream>

#define ll long long
using namespace std;

ll fpowM(ll a, ll b, ll p){
    ll prod = 1;
    while(b){
        if(b & 1){
            prod = (prod * a) % p;
        }
        a = (a * a) % p;
        b >>= 1;
    }
    return prod;
}

int main(){

    int n, p = 1e9 + 7, t, q = 998244353;

    cin >> n;

    ll a[n + 1], av[n + 1], s[n + 1], sv[n + 1];
    s[0] = 1, sv[0] = 1;
    for (int i = 1; i <= n;++i){
        scanf("%d", &t);
        a[i] = t;
        s[i] = s[i - 1] * a[i] % p;
    }
    sv[n] = fpowM(s[n], p - 2, p);
    for (int i = n; i >= 1;--i){
        sv[i - 1] = sv[i] * a[i] % p;
    }
    for (int i = 1; i <= n;++i){
        av[i] = sv[i] * s[i - 1] % p;
    }

    
    
    

    ll ans = av[n], r = q;
    for (int i = n - 1; i >= 1;--i){
        ans = (ans + av[i] * r) % p;
        r = (r * q) % p;
    }
    printf("%lld\n", ans);

    return 0;
}