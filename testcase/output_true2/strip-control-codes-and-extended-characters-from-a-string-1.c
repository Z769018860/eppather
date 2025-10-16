void strip_ascii(unsigned char* str, int n, int ext, int maxbuf) {
    unsigned char buffer[256];
    int i = 0;
    int j = 0;
    int max = (n < maxbuf) ? n : maxbuf - 1;
    int min = 32;
    int max_ascii = 126;
    int min_ext = 128;
    int max_ext = 255;

    for (i = 0; i < max; i = i + 1) {
        if (ext != 0) {
            if (str[i] >= min_ext && str[i] <= max_ext) {
                buffer[j] = str[i];
                j = j + 1;
            }
        } else {
            if (str[i] >= min && str[i] <= max_ascii) {
                buffer[j] = str[i];
                j = j + 1;
            }
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
