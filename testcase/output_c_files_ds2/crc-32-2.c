int rc_crc32(int crc, int buf_len) {
    int table[256];
    int have_table = 0;
    int rem;
    int octet;
    int i;
    int j;
    int p;
    int buf[5];
    
    if (have_table == 0) {
        for (i = 0; i < 256; i = i + 1) {
            rem = i;
            for (j = 0; j < 8; j = j + 1) {
                if ((rem & 1) != 0) {
                    rem = rem >> 1;
                    rem = rem ^ 3988292384;
                } else {
                    rem = rem >> 1;
                }
            }
            table[i] = rem;
        }
        have_table = 1;
    }
    
    crc = ~crc;
    for (p = 0; p < buf_len; p = p + 1) {
        octet = buf[p % 5];
        crc = (crc >> 8) ^ table[(crc & 255) ^ octet];
    }
    crc = ~crc;
    return crc;
}
