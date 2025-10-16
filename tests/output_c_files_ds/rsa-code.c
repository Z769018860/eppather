int rsa_encrypt_decrypt() {
    int pt[40] = {0};
    int ct[40] = {0};
    int n[40] = {9,5,1,6,3,1,1,8,4,5,7,9,0,6,5,6,1,5,3,4,9,9,7,1,6,7,6,0,8,4,7,0,0,1,4,3,3,4,4,1};
    int e[5] = {6,5,5,3,7};
    int d[40] = {5,6,1,7,8,4,3,1,8,7,8,4,4,9,5,3,1,7,0,3,0,8,4,6,3,6,2,2,2,3,0,2,8,3,3,7,6,2,9,8};
    int plaintext[13] = {82,111,115,115,101,116,116,97,32,67,111,100,101};
    int buffer[64] = {0};
    int i;
    int j;
    int temp;
    int carry;
    
    for (i = 0; i < 13; i = i + 1) {
        pt[i] = plaintext[i];
    }
    
    for (i = 0; i < 40; i = i + 1) {
        if (pt[i] > n[i]) {
            return;
        }
    }
    
    for (i = 0; i < 40; i = i + 1) {
        temp = 1;
        for (j = 0; j < 5; j = j + 1) {
            temp = temp * pt[i];
        }
        ct[i] = temp % n[i];
    }
    
    for (i = 0; i < 40; i = i + 1) {
        temp = 1;
        for (j = 0; j < 40; j = j + 1) {
            temp = temp * ct[i];
        }
        pt[i] = temp % n[i];
    }
    
    for (i = 0; i < 13; i = i + 1) {
        buffer[i] = pt[i];
    }
    
    return;
}
