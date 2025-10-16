void comb(int pool, int need, unsigned long chosen, int at) {
    int n1;
    int n2;
    int n3;
    int at_arr[5];
    int pool_arr[5];
    int need_arr[5];
    unsigned long chosen_arr[5];
    int i;
    
    at_arr[0] = at;
    pool_arr[0] = pool;
    need_arr[0] = need;
    chosen_arr[0] = chosen;
    
    if (pool_arr[0] < need_arr[0] + at_arr[0]) {
        return;
    }
    
    if (need_arr[0] == 0) {
        for (i = 0; i < 5; i = i + 1) {
            if (i < pool_arr[0]) {
                n1 = 1;
                for (n2 = 0; n2 < i; n2 = n2 + 1) {
                    n1 = n1 * 2;
                }
                if (chosen_arr[0] & n1) {
                    n3 = i;
                }
            }
        }
        return;
    }
    
    n1 = 1;
    for (n2 = 0; n2 < at_arr[0]; n2 = n2 + 1) {
        n1 = n1 * 2;
    }
    comb(pool_arr[0], need_arr[0] - 1, chosen_arr[0] | n1, at_arr[0] + 1);
    comb(pool_arr[0], need_arr[0], chosen_arr[0], at_arr[0] + 1);
    return;
}
