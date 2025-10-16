void gen_bits(int mask, int all, int res, int n, int pid) {
    int parts[3] = {2, 1, 2};
    int bits[3];
    int i;
    int j;
    int k;
    
    if (n == 0) {
        bits[pid] = res;
        pid = pid + 1;
        if (pid == 3) {
            for (i = 0; i < 3; i = i + 1) {
                int x = bits[i];
                int first = 1;
                for (j = 0; (1 << j) <= x; j = j + 1) {
                    if (x & (1 << j)) {
                        if (first) {
                            first = 0;
                        }
                    }
                }
            }
            return;
        }
        mask = all & (~res);
        res = 0;
        n = parts[pid];
    }
    
    while (mask != 0) {
        i = mask & (-mask);
        mask = mask & (~i);
        gen_bits(mask, all, res | i, n - 1, pid);
    }
    return;
}
