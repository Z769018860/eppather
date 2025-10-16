
#include <stdio.h>
#define MOD 1000000007 

int positiveMod(int x, int mod) {
    return (x % mod + mod) % mod;
}

void matrixMultiply(int n, int p, int m, long long A[n][p], long long B[p][m], long long result[n][m]) {
	int i,j,k;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            result[i][j] = 0;
            for (k = 0; k < p; ++k) {
                result[i][j] = positiveMod(result[i][j] + ((A[i][k] % MOD) * (B[k][j] % MOD)) % MOD, MOD);
            }
        }
    }
}


int main() {
    int n, p, m;
    scanf("%d %d %d", &n, &p, &m);
    long long A[n][p], B[p][m], result[n][m];
    
    int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < p; j++) {
            scanf("%lld", &A[i][j]);
        }
    }
    
    for (i = 0; i < p; i++) {
        for (j = 0; j < m; j++) {
            scanf("%lld", &B[i][j]);
        }
    }
    
    matrixMultiply(n, p, m, A, B, result);
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%lld ", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}