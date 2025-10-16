int func() {
    int lista[5];
    int m[5];
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        m[i] = i * 11 % 64;
        lista[i] = m[i];
    }
    
    for (j = 4; j >= 0; j = j - 1) {
        lista[j] = 0;
    }
    
    return;
}
