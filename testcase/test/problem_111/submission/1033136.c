#include <stdio.h>
#include <string.h>

typedef long long LL;
#define maxn    1000012

char s[maxn];
LL n, m, sa[maxn], rank[maxn], sb[maxn], c[maxn];

#define radixsort() do { \
    for (i = 0; i <= m; i++) c[i] = 0; \
    for (i = 1; i <= n; i++) c[fk[i]]++; \
    for (i = 1; i <= m; i++) c[i] += c[i - 1]; \
    for (i = n; i >= 1; i--) sa[c[fk[sk[i]]]--] = sk[i]; \
} while (0)
void build() {
    LL i, k, p, *fk = rank, *sk = sb, *tmp;
    for (i = 1; i <= n; i++) fk[i] = s[i], sk[i] = i;
    radixsort();
    for (p = k = 1; k <= n && p < n; k <<= 1, m = p, p = k) {
        for (i = 1; i <= k; i++) sk[i] = n - k + i;
        for (i = 1; i <= n; i++) if (sa[i] > k) sk[++p] = sa[i] - k;
        radixsort();
        tmp = fk; fk = sk; sk = tmp;
        fk[sa[1]] = p = 1;
        for (i = 2; i <= n; i++) fk[sa[i]] = (sk[sa[i]] == sk[sa[i - 1]] && sk[sa[i] + k] == sk[sa[i - 1] + k]) ? p : ++p;
    }
}

int main() {
    LL i;
    scanf("%s", s + 1); n = strlen(s + 1); m = 127;
    build();
    for (i = 1; i <= n; i++) printf("%lld%c", sa[i], " \n"[i == n]);
    return 0;
}

