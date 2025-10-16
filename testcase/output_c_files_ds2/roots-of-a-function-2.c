int polynomial_solver(int n, int p[4], int z[6]) {
    int w[24];
    int i;
    int j;
    int k;
    int temp;
    
    for (i = 0; i < 5; i = i + 1) {
        w[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp = p[0];
        for (j = 1; j < 4; j = j + 1) {
            temp = temp * i + p[j];
        }
        z[i] = temp;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (z[j] > z[j + 1]) {
                temp = z[j];
                z[j] = z[j + 1];
                z[j + 1] = temp;
            }
        }
    }
    
    return;
}
