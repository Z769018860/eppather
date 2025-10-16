int factorial(int n) {
    int acc[5];
    acc[0] = 1;
    int n1;
    n1 = n;
    if (n1 < 0) {
        return -1;
    }
    for (; n1 > 0; n1 = n1 - 1) {
        acc[0] = acc[0] * n1;
    }
    return acc[0];
}
