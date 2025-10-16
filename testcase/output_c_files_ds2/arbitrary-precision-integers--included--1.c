int compute_power(int n) {
    int a[5];
    int len[5];
    int s[5];
    int i;
    
    a[0] = 5;
    for (i = 0; i < 5; i = i + 1) {
        a[0] = a[0] * a[0];
    }
    
    len[0] = 0;
    for (i = a[0]; i > 0; i = i / 10) {
        len[0] = len[0] + 1;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        s[i] = 0;
    }
    
    for (i = 0; i < len[0]; i = i + 1) {
        s[i] = 0;
    }
    
    return;
}
