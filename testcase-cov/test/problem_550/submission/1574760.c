#include <stdio.h>
#include <ctype.h>
#define ll long long


inline ll read() {
    ll r = 0, f = 0;
    char c = getchar();

    while (!isdigit(c))
        f = c == '-', c = getchar();

    while (isdigit(c))
        r = r * 10 + (c ^ 48), c = getchar();

    return f ? -r : r;
}

inline ll minn(ll a, ll b) {
    return a < b ? a : b;
}
inline ll maxx(ll a, ll b) {
    return a > b ? a : b;
}

const ll ml = 1e6 + 101;

ll t, n, m, x;

int main() {
    
    
    scanf("%lld",&t);

    while (t--) {
        scanf("%lld%lld%lld",&n,&m,&x);
        
        ll un = (n + 1) >> 1, dn = n >> 1;
        ll um = (m + 1) >> 1, dm = m >> 1;
        printf("%lld\n", dn *um*(un + dm) + un *dm*(dn + um));
    }

    return 0;
}