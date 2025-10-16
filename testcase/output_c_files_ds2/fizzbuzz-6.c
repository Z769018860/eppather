void fizzbuzz(int n) {
    int i;
    int result[5];
    for (i = 1; i <= n; i = i + 1) {
        if ((i % 15) == 0) {
            result[0] = 0;
        } else if ((i % 3) == 0) {
            result[0] = 1;
        } else if ((i % 5) == 0) {
            result[0] = 2;
        } else {
            result[0] = 3;
            result[1] = i;
        }
    }
    return;
}
