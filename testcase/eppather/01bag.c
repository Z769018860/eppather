void knapsack(int weights[5], int values[5], int numItems, int capacity) {
    int dp[1000 + 1] = {0};

    for (int i = 0; i < numItems; i = i + 1) {
        for (int w = capacity; w >= weights[i]; w = w - 1) {
            dp[w] = dp[w] > dp[w - weights[i]] + values[i] ? dp[w] : dp[w - weights[i]] + values[i];
        }
    }
}
