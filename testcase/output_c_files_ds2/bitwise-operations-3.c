int rotr(int x, int s) {
    int result[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        result[i] = 0;
    }
    result[0] = x;
    for (i = 0; i < s; i = i + 1) {
        int lsb = result[0] & 1;
        result[0] = result[0] >> 1;
        if (lsb) {
            result[0] = result[0] | -2147483648;
        }
    }
    return result[0];
}
