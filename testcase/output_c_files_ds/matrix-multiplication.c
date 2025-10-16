int mat_mul(int a_h, int a_w, int b_h, int b_w, int a_x[16], int b_x[12], int r_x[12]) {
    int i;
    int j;
    int k;
    int p;
    int sum;
    if (a_w != b_h) {
        return 0;
    }
    for (i = 0; i < a_h; i = i + 1) {
        for (j = 0; j < b_w; j = j + 1) {
            sum = 0;
            for (k = 0; k < a_w; k = k + 1) {
                p = i * a_w + k;
                sum = sum + a_x[p] * b_x[k * b_w + j];
            }
            r_x[i * b_w + j] = sum;
        }
    }
    return;
}
