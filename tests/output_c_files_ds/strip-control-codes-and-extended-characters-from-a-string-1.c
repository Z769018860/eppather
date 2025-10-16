int ascii(const unsigned char c) {
    unsigned char min = 32;
    unsigned char max = 126;
    if (c >= min && c <= max) {
        return 1;
    }
    return 0;
}

int ascii_ext(const unsigned char c) {
    unsigned char min_ext = 128;
    unsigned char max_ext = 255;
    if (c >= min_ext && c <= max_ext) {
        return 1;
    }
    return 0;
}

void strip(unsigned char str[256], const size_t n, int ext) {
    unsigned char buffer[256];
    size_t i;
    size_t j;
    size_t max;
    
    for (i = 0; i < 256; i = i + 1) {
        buffer[i] = 0;
    }
    
    i = 0;
    j = 0;
    if (n < 256) {
        max = n;
    } else {
        max = 255;
    }
    
    for (i = 0; i < max; i = i + 1) {
        if ((ext != 0 && ascii_ext(str[i]) != 0) || (ascii(str[i]) != 0)) {
            buffer[j] = str[i];
            j = j + 1;
        }
    }
    
    for (i = 0; i < max; i = i + 1) {
        str[i] = 0;
    }
    
    for (i = 0; i < j; i = i + 1) {
        str[i] = buffer[i];
    }
    
    str[j] = 0;
    return;
}
