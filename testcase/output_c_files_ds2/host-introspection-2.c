int check_endian() {
    int x[5];
    x[0] = 1;
    int y[5];
    y[0] = ((x[0] >> 24) & 255) | ((x[0] >> 8) & 65280) | ((x[0] << 8) & 16711680) | (x[0] << 24);
    if (y[0] == x[0]) {
        int result[5];
        result[0] = 1;
    } else {
        int result[5];
        result[0] = 0;
    }
    return;
}
