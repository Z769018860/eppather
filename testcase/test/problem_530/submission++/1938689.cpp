#include <bits/stdc++.h>

using i64 = long long;
using PII = std::pair<i64,i64>;
#define int i64
#define yes std::cout << "YES\n";
#define no std::cout << "NO\n";


const int N = 1e6 + 10;
int primes[N], cnt;     
bool st[N];         

void get_primes(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++] = i;
        for (int j = 0; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}











void solve() {
    int m;
    std::cin >> m;

    std::vector<int> e(m);
    int n = 1;

    for (int i = 0; i < m; i ++) {
        std::cin >> e[i];
        n = std::max(n,e[i] * primes[i]);
    }
    
    int l = 0,r = n;

    auto check = [&](int mid) {
        for (int i = 0; i < m; i++) {
            int t = mid, res = 0;
            while (t && res < e[i]) {
                res += t / primes[i];
                t /= primes[i];
            }
            if (res < e[i]) {
                return false;
            }
        }
        return true;
    };
    
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    std::cout << r << "\n";

    
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); 
    get_primes(1e6);
    int T = 1;
    
    std::cin >> T;

    while (T -- ) {
        solve();
    }
    return 0;
}

