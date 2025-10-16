#include <bits/stdc++.h>

using namespace std;

inline long long calc(long long p, int c, long long E) {
    long long n = 1;
    for(int i = 1; i <= c; i ++) n *= p;
    long long phi = n / p * (p - 1);
    if(p == 2 && n > 4 && E % 2 == 0) phi /= 2;
    return phi / __gcd(phi, E);
}
inline long long solve(long long p, int c, long long E) {
    long long n = 1, res = 1;
    for(int i = 1; i <= c; i ++) n *= p;

    do {
        res += calc(p, c, E);
        c -= E;
    } while(c > 0);
    return res;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);

    long long p, q, n; cin >> p >> q >> n;
    long long res = 1;
    for(long long i = 2; i * i <= n; i ++) if(n % i == 0) {
        int c = 0;
        while(n % i == 0) c ++, n /= i;
        res *= solve(i, c, p);
    }
    if(n > 1) res *= solve(n, 1, p);
    cout << res << '\n';

    return 0;
}