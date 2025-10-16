int str_markov(int str_s[100], int str_alloc_len, int rules_pat[10][100], int rules_repl[10][100], int rules_terminate[10], int n) {
    int tmp_s[100];
    int tmp_alloc_len = 100;
    int i;
    int j;
    int k;
    int sl;
    int pl;
    int changed;
    int done;
    
    for (i = 0; i < 100; i = i + 1) {
        tmp_s[i] = 0;
    }
    
    done = 0;
    while (done == 0) {
        changed = 0;
        for (i = 0; i < n; i = i + 1) {
            if (done != 0) {
                break;
            }
            if (changed != 0) {
                break;
            }
            pl = 0;
            while (rules_pat[i][pl] != 0) {
                pl = pl + 1;
            }
            sl = 0;
            while (str_s[sl] != 0) {
                sl = sl + 1;
            }
            for (j = 0; j < sl; j = j + 1) {
                int match;
                match = 1;
                for (k = 0; k < pl; k = k + 1) {
                    if (str_s[j + k] != rules_pat[i][k]) {
                        match = 0;
                        break;
                    }
                }
                if (match == 0) {
                    continue;
                }
                for (k = 0; k < j; k = k + 1) {
                    tmp_s[k] = str_s[k];
                }
                tmp_s[k] = 0;
                k = 0;
                while (rules_repl[i][k] != 0) {
                    tmp_s[j + k] = rules_repl[i][k];
                    k = k + 1;
                }
                tmp_s[j + k] = 0;
                k = 0;
                while (str_s[j + pl + k] != 0) {
                    tmp_s[j + k + (j + k - j)] = str_s[j + pl + k];
                    k = k + 1;
                }
                tmp_s[j + k + (j + k - j)] = 0;
                for (k = 0; k < 100; k = k + 1) {
                    str_s[k] = tmp_s[k];
                }
                changed = 1;
                if (rules_terminate[i] != 0) {
                    done = 1;
                }
                break;
            }
        }
        if (changed == 0) {
            break;
        }
    }
    return;
}
