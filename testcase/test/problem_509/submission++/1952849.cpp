#include <algorithm>
#include <cstdio>
#include <cmath>
#include <map>

constexpr int maxn = 20000000 + 5;

int S, tot = 0, primes[maxn / 13], mu[maxn], mu2[maxn];
bool vis[maxn];

std::map<int, int> mp;

void init() {
    int tot = 0;
    mu[1] = mu2[1] = 1;

    for (int i = 2; i <= S; i ++) {
        if (!vis[i]) {
            primes[tot ++] = i;
            mu[i] = -1;
            mu2[i] = 1;
        }

        for (int j = 0; j < tot && i * primes[j] <= S; j ++) {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                break;
            }
            mu[i * primes[j]] = -mu[i];
            mu2[i * primes[j]] = mu2[i];
        }

        mu[i] += mu[i - 1];
        mu2[i] += mu2[i - 1];
    }
}

int sum_mu(int n) {
    if (n <= S) {
        return mu[n];
    }
    if (mp.count(n)) {
        return mp[n];
    }

    int ans = 1;

    for (int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans -= (r - l + 1) * sum_mu(n / l);
        tot ++;
    }

    return mp[n] = ans;
}

long long sum_mu2(long long n) {
    if (n <= S) {
        return mu2[n];
    }

    int lim = sqrtl(n);
    long long ans = 0;

    for (int l = 1, r; l <= lim; l = r + 1) {
        r = sqrtl(n / (n / l / l));
        ans += (sum_mu(r) - sum_mu(l - 1)) * (n / l / l);
        tot ++;
    }

    return ans;
}

int main() {
    long long n, m;
    scanf("%lld%lld", &n, &m);
    if (n > m) {
        std::swap(n, m);
    }

    S = pow(m, 3.0 / 7);
    init();

    long long ans = 0, lst = 0;

    for (long long l = 1, r; l <= n; l = r + 1) {
        int v1 = sqrtl(n / l);
        int v2 = sqrtl(m / l);
        r = std::min(n / v1 / v1, m / v2 / v2);
        long long now = sum_mu2(r);
        ans += (now - lst) * v1 * v2;
        lst = now;
    }

    printf("%lld\n", ans);

    return 0;
}
