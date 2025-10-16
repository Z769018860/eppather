int lcs(int a[5], int n, int b[5], int m, int* s[5]) {
    int dp[5][5];
    int i;
    int j;
    int max_len;
    max_len = 0;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            dp[i][j] = 0;
        }
    }
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (a[i] == b[j]) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                if (dp[i][j] > max_len) {
                    max_len = dp[i][j];
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    return;
}
