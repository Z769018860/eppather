#include <bits/stdc++.h>
using namespace std;

const int N = 100001;
bool ip[N]; vector<int> ps;
void sieve(){
    fill_n(ip, N, 1); ip[1] = 0;
    for (int i = 2; i < N; ++i) {
        if (ip[i]) ps.push_back(i);
        for (int j : ps) {
            if (i * j >= N) break;
            ip[i * j] = 0;
            if (i % j == 0);
        }
    }
}

struct pf_t { int p, c; };
vector<pf_t> pfd(int n) {
    vector<pf_t> res;
    for (int p : ps) {
        if (1ll * p * p > n) break;
        if (n % p) continue;
        res.push_back({ p, 0 });
        do res.back().c++, n /= p;
        while (n % p == 0);
    }
    if (n != 1) res.push_back({ n, 1 });
    return res;
}

struct divisor_t { int d, cnt; };
vector<divisor_t> get_divisors(int n, int p, const vector<pf_t>& pf) {
    vector<divisor_t> res;
    function<void(int, int, int)> dfs = [&](int i, int d, int c) {
        if (i == pf.size())
            res.push_back({ d, c });
        else {
            for (int e = 0, q = 1; e <= pf[i].c; ++e, q *= pf[i].p) {
                int t;
                if (e == 0) t = 1;
                else {
                    int w = pf[i].p == 2 ? 2 : pf[i].p - 1;
                    t = w / __gcd(w, p);
                    if (e >= 2) {
                        w = q / pf[i].p;
                        if (pf[i].p == 2) w /= pf[i].p;
                        t *= w / __gcd(w, p);
                    }
                }
                dfs(i + 1, d, c * t);
                d *= pf[i].p;
            }
        }
    };
    dfs(0, 1, 1);
    return res;
}

int qpm(int a, int b, int n) {
    int r = 1;
    do if (b & 1) r = 1ll * r * a % n;
    while (a = 1ll * a * a % n, b >>= 1);
    return r;
}

int main(void) {
    sieve();
    int p, q, n; scanf("%d %d %d", &p, &q, &n);
    auto divs = get_divisors(n, p, pfd(n));
    int ans = 0;
    vector<int> d;
    for (auto x : divs) d.push_back(__gcd(n, qpm(x.d, p, n)));
    sort(d.begin(), d.end());
    d.erase(unique(d.begin(), d.end()), d.end());
    for (auto x : divs) {
        if (binary_search(d.begin(), d.end(), n / x.d))
            ans += x.cnt;
    }
    printf("%d\n", ans);
    return 0;
}