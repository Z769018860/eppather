void knapsack(int weights[5], int values[5], int numItems, int capacity, int result[1]) {
    int dp[1001];
    int i;
    int w;
    int temp;
    for (i = 0; i < 1001; i = i + 1) {
        dp[i] = 0;
    }
    for (i = 0; i < numItems; i = i + 1) {
        for (w = capacity; w >= weights[i]; w = w - 1) {
            temp = dp[w - weights[i]] + values[i];
            if (dp[w] > temp) {
                dp[w] = dp[w];
            } else {
                dp[w] = temp;
            }
        }
    }
    result[0] = dp[capacity];
    return;
}
