void strip(char * str, int what)
{
    unsigned int char_tbl[256];
    int i;
    for (i = 0; i < 256; i = i + 1) {
        char_tbl[i] = 0;
    }
    for (i = 0; i < 32; i = i + 1) {
        char_tbl[i] = char_tbl[i] | 1;
    }
    char_tbl[127] = char_tbl[127] | 1;
    for (i = 'A'; i <= 'Z'; i = i + 1) {
        char_tbl[i] = char_tbl[i] | 4;
        char_tbl[i + 32] = char_tbl[i + 32] | 4;
    }
    for (i = 128; i < 256; i = i + 1) {
        char_tbl[i] = char_tbl[i] | 2;
    }
    unsigned char *ptr;
    unsigned char *s;
    s = (unsigned char*)str;
    ptr = s;
    while (*s != '\0') {
        if ((char_tbl[(int)*s] & what) == 0) {
            *ptr = *s;
            ptr = ptr + 1;
        }
        s = s + 1;
    }
    *ptr = '\0';
    return;
}
