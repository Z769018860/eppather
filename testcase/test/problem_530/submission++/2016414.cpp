#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define mid ((l+r)>>1)
#define FOR(i,a,b) for(long long i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(long long i=(a); i>=(b); --i)
using namespace std;
const ll N = 1e4;
ll pre[N + 10], p[N + 10];
ll z[N + 10], cm[N + 10];
inline char gc() {
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
inline ll gt() {
    ll t = 0, f = 0;
    char v = gc();

    while (!isdigit(v))
        f |= (v == '-'), v = gc();

    while (isdigit(v))
        t = (t << 3) + (t << 1) + v - 48, v = gc();

    return f ? -t : t;
}
inline void wr(ll x) {
    if (x < 0) {
        x *= -1;
        putchar('-');
    }

    if (x > 9)
        wr(x / 10);

    putchar(x % 10 + '0');
    return;
}
int main() {
    ll pto = 0;
    FOR(i, 2, N) {
        if (!pre[i]) {
            pre[i] = i;
            p[++pto] = i;
        }

        FOR(j, 1, pto) {
            if (i * p[j] > N)
                break;

            pre[i * p[j]] = p[j];

            if (!(i % p[j]))
                continue;
        }
    }
    ll T = gt();

    while (T--) {
        ll m = gt(), ans = 1;
        FOR(i, 1, m) {
            ll lans = 0, x = gt();
            ll po = 0;
            z[0] = 0;

            while (z[po] <= x) {
                ++po;
                z[po] = z[po - 1] * p[i] + 1;

                if (po == 1)
                    cm[po] = 1;
                else
                    cm[po] = cm[po - 1] * p[i];
            }

            --po;
            ROF(j, po, 1) {
                ll t = x / z[j];
                lans += cm[j] * t;
                x -= t * z[j];
            }
            lans *= p[i];
            ans = max(ans, lans);
        }
        printf("%lld\n", ans);
    }
}