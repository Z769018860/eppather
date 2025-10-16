int mat_mul(int a_h, int a_w, int b_h, int b_w, int a_x[20], int b_x[20], int r_x[20]) {
    int i;
    int j;
    int k;
    int p;
    int pa;
    int pb;
    int sum;
    
    if (a_w != b_h) {
        return 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            sum = 0;
            for (k = 0; k < 5; k = k + 1) {
                pa = i * a_w + k;
                pb = k * b_w + j;
                sum = sum + a_x[pa] * b_x[pb];
            }
            p = i * b_w + j;
            r_x[p] = sum;
        }
    }
    return;
}
