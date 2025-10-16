int subrand_seed_subrand(int p1, int state[55], int si_sj[2]) {
    int i;
    int j;
    int p2 = 1;
    int x;
    int n1 = 1000000000;
    int n2 = 55;
    int n3 = 21;
    int n4 = 24;
    int n5 = 165;
    
    state[0] = p1 % n1;
    for (i = 1; i < n2; i = i + 1) {
        j = j + n3;
        if (j >= n2) {
            j = j - n2;
        }
        state[j] = p2;
        p2 = p1 - p2;
        if (p2 < 0) {
            p2 = p2 + n1;
        }
        p1 = state[j];
    }
    si_sj[0] = 0;
    si_sj[1] = n4;
    for (i = 0; i < 5; i = i + 1) {
        if (si_sj[0] == si_sj[1]) {
            subrand_seed_subrand(0, state, si_sj);
        }
        si_sj[0] = si_sj[0] - 1;
        if (si_sj[0] < 0) {
            si_sj[0] = n2 - 1;
        }
        si_sj[1] = si_sj[1] - 1;
        if (si_sj[1] < 0) {
            si_sj[1] = n2 - 1;
        }
        x = state[si_sj[0]] - state[si_sj[1]];
        if (x < 0) {
            x = x + n1;
        }
        state[si_sj[0]] = x;
    }
    return;
}
