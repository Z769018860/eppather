int crc32_function(int param1, int param2, int param3) {
    int crc_table[256];
    int crc = param1;
    int buffer[5];
    buffer[0] = 0;
    for (int i = 0; i < 256; i = i + 1) {
        int c = i;
        for (int j = 0; j < 8; j = j + 1) {
            if ((c & 1) != 0) {
                c = 3988292384 ^ (c >> 1);
            } else {
                c = c >> 1;
            }
        }
        crc_table[i] = c;
    }
    for (int i = 0; i < param3; i = i + 1) {
        crc = crc_table[(crc ^ buffer[i]) & 255] ^ (crc >> 8);
    }
    return crc ^ 4294967295;
}

int compute_crc() {
    int s[5];
    s[0] = 'T';
    s[1] = 'h';
    s[2] = 'e';
    s[3] = ' ';
    s[4] = 'q';
    int result = crc32_function(0, s, 5);
    return result;
}
