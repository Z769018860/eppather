int rotr(int x, int s) {
    int result;
    int i;
    s = s % 32;
    for (i = 0; i < s; i = i + 1) {
        int lsb = x & 1;
        x = x >> 1;
        if (lsb) {
            x = x | (1 << 31);
        }
    }
    result = x;
    return result;
}
