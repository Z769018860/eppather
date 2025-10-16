int fac(int x) {
    int result[5];
    result[0] = 1;
    int i;
    for (i = 1; i <= x; i = i + 1) {
        result[0] = result[0] * i;
    }
    return result[0];
}
