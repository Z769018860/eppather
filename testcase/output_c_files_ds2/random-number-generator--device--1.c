int func(int buf_size) {
    int buf[4];
    int v[5];
    int fin[5];
    int i;
    
    for (i = 0; i < 4; i = i + 1) {
        buf[i] = 0;
    }
    v[0] = 0;
    fin[0] = 0;
    
    v[0] = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
    
    return;
}
