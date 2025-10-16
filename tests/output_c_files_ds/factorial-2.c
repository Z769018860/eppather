int factorialSafe(int n) {
    int result;
    int i;
    result = 1;
    if (n < 0) {
        return -1;
    }
    for (i = 1; i <= n; i = i + 1) {
        result = result * i;
    }
    return result;
    return;
}
