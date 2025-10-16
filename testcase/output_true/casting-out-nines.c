int func(int base, int n) {
    int c1[5] = {0};
    int c2[5] = {0};
    int k[5] = {0};
    int power[5] = {1};
    
    for (int i = 0; i < 5; i = i + 1) {
        power[0] = power[0] * base;
    }
    
    for (k[0] = 1; k[0] < power[0]; k[0] = k[0] + 1) {
        c1[0] = c1[0] + 1;
        if ((k[0] % (base - 1)) == ((k[0] * k[0]) % (base - 1))) {
            c2[0] = c2[0] + 1;
        }
    }
    
    return;
}
