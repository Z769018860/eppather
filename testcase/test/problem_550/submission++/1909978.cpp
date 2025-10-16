#include <bits/stdc++.h>

using namespace std;

inline long long solve(int n, int k) {return 1ll * (n / 2) * ((n + 1) / 2); }
inline long long solve() {
    int n, m, k; cin >> n >> m >> k;
    if(n % 2 == 0 && m % 2 == 0) 
        return 1ll * n * m / 2 * ((n / 2) + (m / 2));
    if(n % 2 == 0 && m % 2 == 1)
        return 1ll * n * (m - 1) / 2 * ((n / 2) + (m / 2) + 1) + solve(n, k);
    if(n % 2 == 1 && m % 2 == 0)
        return 1ll * (n - 1) * m / 2 * ((n / 2) + 1 + (m / 2)) + solve(m, k);
    if(n % 2 == 1 && m % 2 == 1)
        return 1ll *(n - 1) * (m - 1) / 2 * ((n / 2) + 1 + (m / 2) + 1) + solve(n, k) + solve(m, k);
    assert(false); return -1;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);

    int T; cin >> T;
    while(T --) cout << solve() << '\n';

    return 0;
}