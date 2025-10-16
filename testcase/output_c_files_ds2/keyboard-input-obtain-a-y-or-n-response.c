void set_mode_get_key(int want_key, int no_timeout, int* result) {
    int c[5];
    c[0] = 0;
    int tv_sec[5];
    tv_sec[0] = 0;
    int tv_usec[5];
    tv_usec[0] = 0;
    int fs[5];
    fs[0] = 0;
    
    if (want_key == 0) {
        return;
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        fs[i] = 0;
    }
    
    if (no_timeout == 0) {
        if (fs[0] != 0) {
            c[0] = 1;
            want_key = 0;
        }
    } else {
        if (fs[0] != 0) {
            c[0] = 1;
            want_key = 0;
        }
    }
    
    result[0] = c[0];
    return;
}
