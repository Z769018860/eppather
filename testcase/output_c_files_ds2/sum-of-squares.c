int squaredsum(int l[5], int e) {
    int sum[5];
    sum[0] = 0;
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (i < e) {
            sum[0] = sum[0] + l[i] * l[i];
        }
    }
    return sum[0];
}
