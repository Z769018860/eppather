#include <cstdio>
#include <iostream>
#define int unsigned int

using namespace std;

const int M = 3e5 + 5;

int prime[M], cnt = 0, a[M], g[M << 1], f[M << 1], primeMi[M];
int n, k, v[M << 1], ss = 0, mu[M], mus[M];

inline int getIdx(int o) { return (o > M) ? (M + n / o) : o; }

int mi(int o, int p) {
    int yu = 1;
    while (p) {
        if (p & 1) yu *= o;
        o *= o;
        p >>= 1;
    }
    return yu;
}

int cal(int o) {
    if (o < M) return mu[o];
    if (mus[n / o]) return mus[n / o];
    int yu = 1;
    for (int l = 2, r; l <= o; l = r + 1) {
        r = o / (o / l);
        yu -= (r - l + 1) * cal(o / l);
    }
    return mus[n / o] = yu;
}

int find(int o) {
    int l = 1, r = ss, res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (o <= v[mid] / o) {
            res = mid;
            l = mid + 1;
        } else
            r = mid - 1;
    }
    return res;
}

signed main() {
    scanf("%u%u", &n, &k);
    mu[1] = 1;
    for (int i = 2; i < M; i++) {
        if (!a[i]) {
            prime[++cnt] = i;
            primeMi[cnt] = mi(prime[cnt], k);
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * prime[j] < M; j++) {
            a[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
    mu[0] = 0;
    for (int i = 1; i < M; i++) mu[i] += mu[i - 1];
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        v[++ss] = n / l;
        g[getIdx(n / l)] = n / l - 1;
    }
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= ss; j++) {
            int t = v[j];
            if (prime[i] > t / prime[i]) break;
            g[getIdx(t)] -= g[getIdx(t / prime[i])] - i + 1;
        }
    }
    for (int j = 1; j <= ss; j++) {
        f[getIdx(v[j])] = g[getIdx(v[j])];
    }
    for (int i = cnt; i >= 1; i--) {
        int idx = find(prime[i]);
        for (int j = idx; j >= 1; j--) {
            int t = v[j];
            if (prime[i] > t / prime[i]) continue;
            int p1 = getIdx(t);
            int p2 = getIdx(t / prime[i]);
            f[p1] += f[p2] - g[p2] + primeMi[i] * (g[p2] - i + 1);
        }
    }
    int ans = 0;
    f[0] = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        int t = n / l, yu = 0;
        r = n / t;
        for (int l1 = 1, r1; l1 <= t; l1 = r1 + 1) {
            r1 = t / (t / l1);
            yu += (cal(r1) - cal(l1 - 1)) * (t / l1) * (t / l1);
        }
        ans += (f[getIdx(r)] - f[getIdx(l - 1)]) * yu;
    }
    cout << ans << endl;
    return 0;
}