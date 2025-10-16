void quaternion_operations(int r[4], int a[4], int b[4], int d) {
    int i;
    int temp[4];
    
    for (i = 0; i < 4; i = i + 1) {
        temp[i] = a[i] + b[i];
    }
    
    for (i = 0; i < 4; i = i + 1) {
        r[i] = temp[i];
    }
    
    r[0] = r[0] + d;
    
    for (i = 0; i < 4; i = i + 1) {
        temp[i] = a[i] * d;
    }
    
    for (i = 0; i < 4; i = i + 1) {
        r[i] = temp[i];
    }
    
    temp[0] = a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3];
    temp[1] = a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2];
    temp[2] = a[0] * b[2] - a[1] * b[3] + a[2] * b[0] + a[3] * b[1];
    temp[3] = a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + a[3] * b[0];
    
    for (i = 0; i < 4; i = i + 1) {
        r[i] = temp[i];
    }
    
    for (i = 0; i < 4; i = i + 1) {
        temp[i] = -a[i];
    }
    
    for (i = 0; i < 4; i = i + 1) {
        r[i] = temp[i];
    }
    
    temp[0] = a[0];
    temp[1] = -a[1];
    temp[2] = -a[2];
    temp[3] = -a[3];
    
    for (i = 0; i < 4; i = i + 1) {
        r[i] = temp[i];
    }
    
    return;
}
