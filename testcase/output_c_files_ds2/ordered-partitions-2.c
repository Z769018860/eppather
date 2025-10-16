void gen_bits(int mask, int all, int res, int n, int pid, int parts[3], int bits[3], int n_parts) {
    int i;
    int j;
    int k;
    for (;;) {
        if (n == 0) {
            bits[pid] = res;
            pid = pid + 1;
            if (pid == n_parts) {
                for (i = 0; i < n_parts; i = i + 1) {
                    int x[5];
                    x[0] = bits[i];
                    int k[5];
                    k[0] = 0;
                    for (j = 0; (1 << j) <= x[0]; j = j + 1) {
                        if (x[0] & (1 << j)) {
                            k[0] = k[0] + 1;
                        }
                    }
                }
                return;
            }
            mask = all & (~res);
            res = 0;
            n = parts[pid];
        } else {
            break;
        }
    }
    for (;;) {
        if (mask) {
            i = mask & (-((int)mask));
            mask = mask & (~i);
            gen_bits(mask, all, res | i, n - 1, pid, parts, bits, n_parts);
        } else {
            break;
        }
    }
    return;
}
