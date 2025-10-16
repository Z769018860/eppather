int quaternion_operations(int q1, int q2, int q3, int q4, int a1, int a2, int a3, int a4, int b1, int b2, int b3, int b4, int d) {
    int r[4];
    int a[4];
    int b[4];
    int q[4];
    int i;
    
    q[0] = q1;
    q[1] = q2;
    q[2] = q3;
    q[3] = q4;
    a[0] = a1;
    a[1] = a2;
    a[2] = a3;
    a[3] = a4;
    b[0] = b1;
    b[1] = b2;
    b[2] = b3;
    b[3] = b4;
    
    for (i = 0; i < 4; i = i + 1) {
        r[i] = q[i];
    }
    
    r[0] = r[0] + d;
    
    for (i = 0; i < 4; i = i + 1) {
        r[i] = a[i] + b[i];
    }
    
    for (i = 0; i < 4; i = i + 1) {
        r[i] = q[i] * d;
    }
    
    for (i = 0; i < 4; i = i + 1) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    
    r[0] = a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3];
    r[1] = a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2];
    r[2] = a[0] * b[2] - a[1] * b[3] + a[2] * b[0] + a[3] * b[1];
    r[3] = a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + a[3] * b[0];
    
    for (i = 0; i < 4; i = i + 1) {
        r[i] = -q[i];
    }
    
    r[0] = q[0];
    for (i = 1; i < 4; i = i + 1) {
        r[i] = -q[i];
    }
    
    return 0;
}
