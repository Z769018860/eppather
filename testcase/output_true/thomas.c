void thomas(int a[5], int b[5], int c[5], int x[5], int size) {
    int y[5];
    int i;
    int scale;
    
    for (i = 0; i < 5; i = i + 1) {
        y[i] = 0;
    }
    
    y[0] = c[0] / b[0];
    x[0] = x[0] / b[0];
    
    for (i = 1; i < size; i = i + 1) {
        scale = 1 / (b[i] - a[i] * y[i - 1]);
        y[i] = c[i] * scale;
        x[i] = (x[i] - a[i] * x[i - 1]) * scale;
    }
    
    for (i = size - 2; i >= 0; i = i - 1) {
        x[i] = x[i] - y[i] * x[i + 1];
    }
    
    return;
}
