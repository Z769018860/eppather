int calculate_means(int argc, int argv_1, int argv_2, int argv_3, int argv_4, int argv_5) {
    int count[5] = {0};
    int sum[5] = {0};
    int prod[5] = {1};
    int resum[5] = {0};
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < argc) {
            int f[5] = {0};
            if (i == 0) { f[0] = argv_1; }
            if (i == 1) { f[0] = argv_2; }
            if (i == 2) { f[0] = argv_3; }
            if (i == 3) { f[0] = argv_4; }
            if (i == 4) { f[0] = argv_5; }
            
            count[0] = count[0] + 1;
            sum[0] = sum[0] + f[0];
            prod[0] = prod[0] * f[0];
            if (f[0] != 0) {
                resum[0] = resum[0] + (1 / f[0]);
            }
        }
    }
    
    return;
}
