void rsa_encrypt_decrypt(int n1, int e1, int d1, int pt1, int ct1, int buffer1) {
    int n[5] = {0};
    int e[5] = {0};
    int d[5] = {0};
    int pt[5] = {0};
    int ct[5] = {0};
    int buffer[5] = {0};
    
    n[0] = n1;
    e[0] = e1;
    d[0] = d1;
    pt[0] = pt1;
    ct[0] = ct1;
    buffer[0] = buffer1;
    
    for (int i = 0; i < 5; i = i + 1) {
        pt[i] = pt[i] + 1;
    }
    
    if (pt[0] > n[0]) {
        return;
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        ct[i] = pt[i] * e[i] % n[i];
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        pt[i] = ct[i] * d[i] % n[i];
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        buffer[i] = pt[i];
    }
    
    return;
}
