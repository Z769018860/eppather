int gray_functions(int n, int mode) {
    int p[5];
    int result[5];
    result[0] = 0;
    p[0] = n;
    
    if (mode == 0) {
        result[0] = n ^ (n >> 1);
    } else {
        for (; n != 0; n = n >> 1) {
            p[0] = p[0] ^ n;
        }
        result[0] = p[0];
    }
    
    return result[0];
}
