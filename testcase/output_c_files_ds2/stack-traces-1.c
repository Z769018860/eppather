void outer(int a, int b, int c) {
    int x[5];
    int y[5];
    int k[5];
    int buffer[5];
    int n[5];
    
    x[0] = a + b;
    y[0] = b + c;
    
    k[0] = x[0] * y[0];
    
    n[0] = 5;
    for (int i = 0; i < 5; i = i + 1) {
        buffer[i] = 0;
    }
    
    n[0] = 5;
    for (int i = 0; i < 5; i = i + 1) {
        buffer[i] = 0;
    }
    
    return;
}
