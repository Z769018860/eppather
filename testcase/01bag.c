#include <stdio.h>

#define MAX_CAPACITY 1000

void knapsack(int weights[], int values[], int numItems, int capacity) {
    int dp[MAX_CAPACITY + 1] = {0};

    // 动态规划解决 0/1 背包问题
    for (int i = 0; i < numItems; i++) {
        for (int w = capacity; w >= weights[i]; w--) {
            dp[w] = dp[w] > dp[w - weights[i]] + values[i] ? dp[w] : dp[w - weights[i]] + values[i];
        }
    }

    // 输出最大价值
    printf("Maximum value in knapsack: %d\n", dp[capacity]);
}

int main() {
    int numItems, capacity;

    // 用户输入物品数量和背包容量
    printf("Enter the number of items: ");
    scanf("%d", &numItems);
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    int weights[numItems], values[numItems];

    // 用户输入每个物品的重量和价值
    printf("Enter the weights and values of the items (weight value):\n");
    for (int i = 0; i < numItems; i++) {
        printf("Item %d: ", i + 1);
        scanf("%d %d", &weights[i], &values[i]);
    }

    // 调用背包算法
    knapsack(weights, values, numItems, capacity);

    return 0;
}
