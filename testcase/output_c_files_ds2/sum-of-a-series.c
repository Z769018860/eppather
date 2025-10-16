int Invsqr(int n[5], int start[5], int end[5], int sum[5]) {
    for (int i[5] = {0}; i[0] < 5; i[0] = i[0] + 1) {
        n[0] = start[0] + i[0];
        sum[0] = sum[0] + (1 / (n[0] * n[0]));
    }
    return;
}
