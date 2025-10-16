int get_key(int want_key) {
    int old[5];
    int new[5];
    int c[5];
    int fs[5];
    int i;
    
    if (want_key == 0) {
        return 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        old[i] = 0;
        new[i] = 0;
        c[i] = 0;
        fs[i] = 0;
    }
    
    new[0] = old[0];
    new[0] = new[0] & 4294967039;
    
    for (i = 0; i < 5; i = i + 1) {
        fs[i] = 0;
    }
    
    fs[0] = 1;
    
    if (fs[0] != 0) {
        c[0] = 0;
    }
    
    return c[0];
}
