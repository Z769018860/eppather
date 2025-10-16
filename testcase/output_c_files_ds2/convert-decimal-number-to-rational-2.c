void find_rational_approximation(int denom_limit, int num[2]) {
    int f_int[5];
    f_int[0] = 0;
    int denom[5];
    denom[0] = 0;
    int best_num[5];
    best_num[0] = 0;
    int best_denom[5];
    best_denom[0] = 1;
    int min_diff[5];
    min_diff[0] = 2147483647;
    int current_diff[5];
    current_diff[0] = 0;
    int i[5];
    int j[5];
    
    for (i[0] = 1; i[0] <= denom_limit; i[0] = i[0] + 1) {
        for (j[0] = 0; j[0] <= 5; j[0] = j[0] + 1) {
            if (j[0] == 0) {
                f_int[0] = 0;
                denom[0] = 1;
            }
            if (j[0] == 1) {
                f_int[0] = 3;
                denom[0] = 1;
            }
            if (j[0] == 2) {
                f_int[0] = 22;
                denom[0] = 7;
            }
            if (j[0] == 3) {
                f_int[0] = 355;
                denom[0] = 113;
            }
            if (j[0] == 4) {
                f_int[0] = 104348;
                denom[0] = 33215;
            }
            if (j[0] == 5) {
                f_int[0] = 3126535;
                denom[0] = 995207;
            }
            
            if (denom[0] <= denom_limit) {
                current_diff[0] = f_int[0] * best_denom[0] - best_num[0] * denom[0];
                if (current_diff[0] < 0) {
                    current_diff[0] = -current_diff[0];
                }
                if (current_diff[0] < min_diff[0]) {
                    min_diff[0] = current_diff[0];
                    best_num[0] = f_int[0];
                    best_denom[0] = denom[0];
                }
            }
        }
    }
    
    num[0] = best_num[0];
    num[1] = best_denom[0];
    return;
}
