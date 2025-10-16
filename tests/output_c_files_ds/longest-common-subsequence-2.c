int lcs(char* a, int n, char* b, int m, char** s) {
    int dp[100][100];
    int i;
    int j;
    int max_len;
    int max_i;
    max_len = 0;
    max_i = 0;
    for (i = 0; i <= n; i = i + 1) {
        for (j = 0; j <= m; j = j + 1) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else {
                if (a[i - 1] == b[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    if (dp[i][j] > max_len) {
                        max_len = dp[i][j];
                        max_i = i;
                    }
                } else {
                    dp[i][j] = 0;
                }
            }
        }
    }
    *s = a + max_i - max_len;
    return max_len;
}
