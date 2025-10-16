void pick(int n, int step, int state, char **v, unsigned long bits) {
    int i;
    int b;
    if (step == n) {
        if (state != 3) {
            return;
        }
        for (i = 0, b = 1; i < n; i = i + 1, b = b << 1) {
            if ((b & bits)) {
            }
        }
        return;
    }
    bits = bits << 1;
    pick(n, step + 1, ((unsigned char[][2]){{0, 1}, {1, 3}, {1, 2}, {3, 3}})[state][0], v, bits);
    pick(n, step + 1, ((unsigned char[][2]){{0, 1}, {1, 3}, {1, 2}, {3, 3}})[state][1], v, bits | 1);
    return;
}
