void sum_multiples(int result[5], int limit[5], int f) {
    int m[5];
    m[0] = limit[0] - 1;
    m[0] = m[0] / f;

    result[0] = m[0];
    result[0] = result[0] + 1;
    result[0] = result[0] * m[0];
    result[0] = result[0] * f;
    result[0] = result[0] / 2;

    return;
}
