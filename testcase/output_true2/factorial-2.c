int factorialSafe(int n) {
    int result[5];
    result[0] = 1;
    if(n < 0) {
        return -1;
    }
    for (int i = 1; i <= n; i = i + 1) {
        result[0] = result[0] * i;
    }
    return result[0];
    return;
}
