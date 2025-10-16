void sum_multiples(int result[1], const int limit[1], const int f) {
    int m[1];
    m[0] = limit[0] - 1;
    m[0] = m[0] / f;
    
    result[0] = m[0];
    result[0] = result[0] + 1;
    result[0] = result[0] * m[0];
    result[0] = result[0] * f;
    result[0] = result[0] / 2;
    
    return;
}
