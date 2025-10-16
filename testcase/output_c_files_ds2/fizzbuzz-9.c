void fizzbuzz(int n) {
    int i[5];
    int result[5];
    for (i[0] = 1; i[0] <= n; i[0] = i[0] + 1) {
        result[0] = 0;
        if (i[0] % 3 == 0) {
            result[0] = 1;
        }
        if (i[0] % 5 == 0) {
            result[0] = result[0] + 2;
        }
        if (i[0] * i[0] * i[0] * i[0] % 15 == 1) {
            result[0] = result[0] + 4;
        }
    }
    return;
}
