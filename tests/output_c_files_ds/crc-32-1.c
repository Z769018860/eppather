unsigned int crc32(unsigned int crc, const unsigned char *buf, unsigned int len) {
    static unsigned int table[256];
    unsigned int c = crc ^ 0xFFFFFFFF;
    unsigned int i;
    unsigned int j;
    
    for (i = 0; i < 256; i = i + 1) {
        unsigned int t = i;
        for (j = 0; j < 8; j = j + 1) {
            if ((t & 1) != 0) {
                t = (t >> 1) ^ 0xEDB88320;
            }
            else {
                t = t >> 1;
            }
        }
        table[i] = t;
    }

    for (i = 0; i < len; i = i + 1) {
        c = table[(c ^ buf[i]) & 0xFF] ^ (c >> 8);
    }

    return c ^ 0xFFFFFFFF;
}

unsigned int func() {
    const char s[44] = "The quick brown fox jumps over the lazy dog";
    unsigned int result = crc32(0, (const unsigned char*)s, 43);
    return result;
}
