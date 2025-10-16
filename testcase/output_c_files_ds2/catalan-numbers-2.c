int catalan(int n) {
    int sum[5];
    int i[5];
    int j[5];
    int k[5];
    int result[5];
    
    if (n == 0) {
        result[0] = 1;
        return result[0];
    }
    
    sum[0] = 0;
    for (i[0] = 0; i[0] <= (n - 1); i[0] = i[0] + 1) {
        j[0] = catalan(i[0]);
        k[0] = catalan((n - 1) - i[0]);
        sum[0] = sum[0] + j[0] * k[0];
    }
    result[0] = sum[0];
    return result[0];
}
