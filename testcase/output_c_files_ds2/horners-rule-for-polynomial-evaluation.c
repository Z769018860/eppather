int horner(int coeffs[5], int s, int x[5]) {
    int res[5];
    res[0] = 0;
    int i;
    
    for (i = s - 1; i >= 0; i = i - 1) {
        res[0] = res[0] * x[0] + coeffs[i];
    }
    
    return res[0];
}
