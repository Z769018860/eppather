#include <bits/stdc++.h>
#define il inline
#define re register
#define ll long long
#define ull unsigned ll
#define uint unsigned int
#define umap unordered_map
#define uset unordered_set
#define mset multiset
#define IT iterator
#define pr pair
#define pq priority_queue
#define mpr make_pair
#define pii pr <int, int>
#define graph std :: vector <std :: pii>
#define int ll
#define checkmemory std :: cerr << (&m2 - &m1) / 1024.0 / 1024 << std :: endl;
bool m1;
const int N = 3e5 + 5, inf = 1e12;
const double pi = acos(-1);
il int R() {
    int s = 0, f = 1;
    char ch = getchar();

    while (!isdigit(ch))
        f = (ch == '-') ? -1 : 1, ch = getchar();

    while (isdigit(ch))
        s = (s << 3) + (s << 1) + (ch ^ 48), ch = getchar();

    return s * f;
}
int m, s[N], n, k, a[N], minn, maxx, minpos, maxpos, lim;
bool m2;
signed main() {
    
    
    m = R();

    for (int i = 1; i <= m; i++)
        s[i] = R();

    n = R();

    while (n--) {
        a[0] = R(), a[1] = R(), k = R(), minn = inf, maxx = -inf, minpos = maxpos = 0;

        if (!a[0] && !a[1]) {
            printf("%lld %lld\n", s[1], s[1]);
            continue;
        }

        for (lim = 2; lim <= 100; lim++) {
            a[lim] = k * a[lim - 1] + a[lim - 2];

            if (a[lim] >= inf || a[lim] <= -inf)
                break;
        }

        for (int i = 1; i <= m; i++) {
            if (s[i] <= lim) {
                if (a[s[i]] < minn)
                    minn = a[s[i]], minpos = s[i];

                if (a[s[i]] > maxx)
                    maxx = a[s[i]], maxpos = s[i];
            } else
                break;
        }

        if (s[m] > lim) {
            if (a[lim] > a[lim - 1] && a[lim - 1] > a[lim - 2])
                maxpos = s[m];
            else if (a[lim] < a[lim - 1] && a[lim - 1] < a[lim - 2])
                minpos = s[m];
        }

        if (!maxpos)
            maxpos = s[1];

        if (!minpos)
            minpos = s[1];

        printf("%lld %lld\n", maxpos, minpos);
    }

    return 0;
}