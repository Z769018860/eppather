void set_mode_get_key(int want_key, int* c) {
    int old[5] = {0};
    int new[5] = {0};
    int fs[5] = {0};
    int tv[5] = {0};
    
    if (want_key == 0) {
        return;
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        new[i] = old[i];
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        fs[i] = 0;
    }
    
    tv[0] = 0;
    tv[1] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        if (fs[i] != 0) {
            c[0] = 1;
            return;
        }
    }
    
    return;
}
