void hanoi(int n, int from, int to, int via, int t0[8], int t1[8], int t2[8], int t0_n, int t1_n, int t2_n) {
    if (n == 0) {
        return;
    }
    hanoi(n - 1, from, via, to, t0, t1, t2, t0_n, t1_n, t2_n);
    
    int disk;
    if (from == 0) {
        disk = t0[t0_n - 1];
        t0_n = t0_n - 1;
    } else if (from == 1) {
        disk = t1[t1_n - 1];
        t1_n = t1_n - 1;
    } else {
        disk = t2[t2_n - 1];
        t2_n = t2_n - 1;
    }
    
    if (to == 0) {
        t0[t0_n] = disk;
        t0_n = t0_n + 1;
    } else if (to == 1) {
        t1[t1_n] = disk;
        t1_n = t1_n + 1;
    } else {
        t2[t2_n] = disk;
        t2_n = t2_n + 1;
    }
    
    hanoi(n - 1, via, to, from, t0, t1, t2, t0_n, t1_n, t2_n);
    return;
}
