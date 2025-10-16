int fibb(int a, int b, int n) {
    int result;
    if (n > 1) {
        n = n - 1;
        result = fibb(b, a + b, n);
    } else {
        result = a;
    }
    return result;
}
