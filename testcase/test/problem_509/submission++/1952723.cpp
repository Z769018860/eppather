#include <bits/stdc++.h>

using i64 = long long;

i64 sqrt(i64 x) {
    i64 a = std::sqrt(x);
    while (a * a > x) a--;
    while (a * a <= x) a++;
    return a - 1;
}

constexpr int limit = 1e7;
int primes[664579], count;
std::bitset<limit> composite;
int miu[limit], miusum[limit];
int miu2[limit], miu2sum[limit];
void sieve() {
    composite[1] = true;
    miu[1] = 1;
    
    for (int x = 2; x < limit; x++) {
        if (!composite[x]) {
            primes[count++] = x;
            miu[x] = -1;
        }
        
        for (int i = 0; i < count; i++) {
            int p = primes[i];
            int j = x * p;
            if (j >= limit) {
                break;
            }
            composite[j] = true;
            if (x % p == 0) {
                miu[j] = 0;
                break;
            }
            miu[j] = miu[x] * miu[p];
        }
    }
    
    for (int i = 1; i < limit; i++) {
        miu2[i] = miu[i] * miu[i];
        miusum[i] = miusum[i - 1] + miu[i];
        miu2sum[i] = miu2sum[i - 1] + miu2[i];
    }
}

std::unordered_map<i64, i64> miumem;
i64 miuSum(i64 n) {
    if (n < limit) {
        return miusum[n];
    }
    auto it = miumem.find(n);
    if (it != miumem.end()) {
        return it->second;
    }
    i64 ans = 1;
    i64 l = 2;
    while (l <= n) {
        i64 nl = n / l;
        i64 r = n / nl;
        ans -= (r - l + 1) * miuSum(nl);
        l = r + 1;
    }
    return miumem[n] = ans;
}

i64 miu2Sum(i64 n) {
    if (n < limit) {
        return miu2sum[n];
    }
    i64 ans = 0;
    i64 i = 1;
    while (i * i * i <= n) {
        ans += n / (i * i) * miu[i];
        i++;
    }
    i64 last = miuSum(i - 1);
    i64 m = n / (i * i);
    for (i64 i = 1; i <= m; i++) {
        ans += miuSum(sqrt(n / i)) - last;
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    sieve();
    
    i64 N, M;
    std::cin >> N >> M;
    i64 R = std::min(N, M);
    
    i64 l = 1;
    i64 ans = 0;
    i64 last = 0;
    while (l <= R) {
        i64 n = sqrt(N / l);
        i64 m = sqrt(M / l);
        i64 r = std::min({N / (n * n), M / (m * m), R});
        i64 now = miu2Sum(r);
        ans += (now - last) * n * m;
        l = r + 1;
        last = now;
    }
    
    std::cout << ans << "\n";
    
    return 0;
}