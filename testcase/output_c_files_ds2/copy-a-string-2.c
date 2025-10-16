void func() {
    int src[5] = {72, 101, 108, 108, 111};
    int dst[80];
    int i;
    int n1 = 80;
    int n2 = 5;
    
    for (i = 0; i < n2; i = i + 1) {
        if (i < n1) {
            dst[i] = src[i];
        }
    }
    
    if (n2 >= n1) {
    }
    
    for (i = 0; i < n2; i = i + 1) {
        src[i] = 45;
    }
    
    return;
}
