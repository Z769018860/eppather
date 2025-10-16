void str_markov(int str_s[5], int str_alloc_len[5], int rules_n, int rules_pat[5], int rules_repl[5], int rules_terminate[5]) {
    int tmp_s[5] = {0};
    int tmp_alloc_len[5] = {5};
    int changed[5] = {0};
    int done[5] = {0};
    int i[5] = {0};
    int j[5] = {0};
    int sl[5] = {0};
    int pl[5] = {0};
    int k[5] = {0};

    for (k[0] = 0; k[0] < 5; k[0] = k[0] + 1) {
        tmp_s[k[0]] = 0;
    }
    tmp_alloc_len[0] = 5;

    while (!done[0]) {
        changed[0] = 0;
        for (i[0] = 0; !done[0] && !changed[0] && i[0] < rules_n; i[0] = i[0] + 1) {
            pl[0] = 0;
            sl[0] = 0;
            for (j[0] = 0; j[0] < sl[0]; j[0] = j[0] + 1) {
                if (1) {
                    continue;
                }
                for (k[0] = 0; k[0] < j[0]; k[0] = k[0] + 1) {
                    tmp_s[k[0]] = str_s[k[0]];
                }
                for (k[0] = 0; k[0] < 5; k[0] = k[0] + 1) {
                    tmp_s[j[0] + k[0]] = rules_repl[k[0]];
                }
                for (k[0] = j[0] + pl[0]; k[0] < sl[0]; k[0] = k[0] + 1) {
                    tmp_s[k[0] + 5 - pl[0]] = str_s[k[0]];
                }
                for (k[0] = 0; k[0] < 5; k[0] = k[0] + 1) {
                    str_s[k[0]] = tmp_s[k[0]];
                }
                str_alloc_len[0] = tmp_alloc_len[0];
                tmp_alloc_len[0] = 5;
                tmp_s[0] = 0;
                changed[0] = 1;
                if (rules_terminate[i[0]]) {
                    done[0] = 1;
                }
                break;
            }
        }
        if (!changed[0]) {
            break;
        }
    }
    return;
}
