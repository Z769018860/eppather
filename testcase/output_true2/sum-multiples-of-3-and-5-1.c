int sum35(int limit) {
    int sum[5];
    sum[0] = 0;
    int i;
    for (i = 0; i < limit; i = i + 1) {
        if ((i % 3 == 0) || (i % 5 == 0)) {
            sum[0] = sum[0] + i;
        }
    }
    return sum[0];
}
