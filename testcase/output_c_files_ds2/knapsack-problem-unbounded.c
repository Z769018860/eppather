void knapsack(int i, int value, int weight, int volume, int count[3], int best[3], int best_value[1], int items_value[3], int items_weight[3], int items_volume[3], int n) {
    int j;
    int m1;
    int m2;
    int m;
    if (i == n) {
        if (value > best_value[0]) {
            best_value[0] = value;
            for (j = 0; j < n; j = j + 1) {
                best[j] = count[j];
            }
        }
        return;
    }
    m1 = weight / items_weight[i];
    m2 = volume / items_volume[i];
    if (m1 < m2) {
        m = m1;
    } else {
        m = m2;
    }
    for (count[i] = m; count[i] >= 0; count[i] = count[i] - 1) {
        knapsack(
            i + 1,
            value + count[i] * items_value[i],
            weight - count[i] * items_weight[i],
            volume - count[i] * items_volume[i],
            count,
            best,
            best_value,
            items_value,
            items_weight,
            items_volume,
            n
        );
    }
    return;
}
