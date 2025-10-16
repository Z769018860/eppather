int factorial(int n) {
    int result;
    int i;
    result = 1;
    for (i = 1; i <= n; i = i + 1) {
        result = result * i;
    }
    return result;
}
