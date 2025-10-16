int gray_encode_decode(int n, int mode) {
    int result;
    int p;
    if (mode == 0) {
        result = n ^ (n >> 1);
    }
    else {
        p = n;
        for (; n > 0; n = n >> 1) {
            p = p ^ n;
        }
        result = p;
    }
    return result;
}
