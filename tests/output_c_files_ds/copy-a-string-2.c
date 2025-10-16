void copy_string() {
    char src[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char dst[80];
    int i;
    int src_len = 0;
    int dst_len = 80;
    
    for (i = 0; i < 6; i = i + 1) {
        if (src[i] == '\0') {
            break;
        }
        src_len = src_len + 1;
    }
    
    if (src_len >= dst_len) {
        return;
    }
    
    for (i = 0; i < src_len; i = i + 1) {
        dst[i] = src[i];
    }
    dst[src_len] = '\0';
    
    for (i = 0; i < 5; i = i + 1) {
        src[i] = '-';
    }
    
    return;
}
