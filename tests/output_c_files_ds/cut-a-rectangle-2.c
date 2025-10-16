int calculate(int n, int k) {
    int dp[11][11];
    int i;
    int j;
    for (i = 0; i <= n; i = i + 1) {
        for (j = 0; j <= k; j = j + 1) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (i = 1; i <= n; i = i + 1) {
        for (j = 1; j <= k; j = j + 1) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] * j;
        }
    }
    return dp[n][k];
}
