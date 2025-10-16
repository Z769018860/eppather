int multifact(int n, int deg) {
    int result;
    result = n;
    if (n <= deg) {
        result = n;
    } else {
        for (; n >= deg + 1; n = n - deg) {
            result = result * (n - deg);
        }
    }
    return result;
}
