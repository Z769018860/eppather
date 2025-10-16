#include <stdio.h>
#include <klee/klee.h>

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

    // 使用 KLEE 的符号输入代替 scanf
    klee_make_symbolic(&numItems, sizeof(numItems), "numItems");
    klee_make_symbolic(&capacity, sizeof(capacity), "capacity");


    int weights[numItems], values[numItems];

    // 用 KLEE 的符号输入初始化物品的重量和价值
    for (int i = 0; i < numItems; i++) {
        klee_make_symbolic(&weights[i], sizeof(weights[i]), "weights[i]");
        klee_make_symbolic(&values[i], sizeof(values[i]), "values[i]");
    }

    // 调用背包算法
    knapsack(weights, values, numItems, capacity);

    return 0;
}
