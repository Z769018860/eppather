#include <stdio.h>

#define N 4000001
#define MOD 998244353

int id[N], sz[N];

int main() {
    int i, j, p, q, n, m, op, ans = 0;
    scanf("%d%d", &n, &m);
    for(i = 0; i < n; i++) {
        id[i] = i;
        sz[i] = 1;
    }
    while(m--) {
        scanf("%d%d%d", &op, &p, &q);
        for(i = p; i != id[i]; i = id[i]) {
            id[i] = id[id[i]];
        }
        for(j = q; j != id[j]; j = id[j]) {
            id[j] = id[id[j]];
        }
        if(op == 0) {
            if(i == j) {
                continue;
            }
            if(sz[i] < sz[j]) {
                id[i] = j;
                sz[j] += sz[i];
            } else {
                id[j] = i;
                sz[i] += sz[j];
            }
        } else {
            if(i == j) {
                ans = (ans * 2 + 1) % MOD;
            } else {
                ans = (ans * 2) % MOD;
            }
        }
    }
    printf("%d\n", ans);
}