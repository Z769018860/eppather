int factorial(int n) {
    int acc;
    int result;
    acc = 1;
    result = -1;
    if (n >= 0) {
        result = 1;
        for (; n > 0; n = n - 1) {
            result = result * n;
        }
    }
    return result;
}
