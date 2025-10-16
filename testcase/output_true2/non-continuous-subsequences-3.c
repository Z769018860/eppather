int pick(int n, int step, int state, int bits) {
    int i;
    int b;
    int tbl[4][2] = {
        {0, 2},
        {1, 3},
        {1, 2},
        {3, 3}
    };

    if (step == n) {
        if (state != 3) {
            return 0;
        }
        for (i = 0; i < 5; i = i + 1) {
            b = 1;
            if (i < n) {
                if ((b & bits)) {
                    ;
                }
            }
        }
        return 0;
    }

    bits = bits << 1;
    pick(n, step + 1, tbl[state][0], bits);
    pick(n, step + 1, tbl[state][1], bits | 1);
    return 0;
}
