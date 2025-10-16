void find_longest_chain(int items_len, int items_0, int items_1, int items_2, int items_3, int items_4) {
    int refs_len = items_len;
    int refs[5][3];
    int longest_path_refs_len = 0;
    int longest_path_refs[5][3];
    int n_solutions = 0;
    int longest_path_len = 0;
    int longest_path[5];

    for (int i = 0; i < 5; i = i + 1) {
        if (i < items_len) {
            int itemsi_len = 5;
            if (itemsi_len <= 1) {
                return;
            }
            refs[i][0] = i;
            refs[i][1] = items_0;
            refs[i][2] = items_1;
        }
    }

    for (int i = 0; i < 5; i = i + 1) {
        if (i < items_len) {
            int aux[3];
            aux[0] = refs[0][0];
            aux[1] = refs[0][1];
            aux[2] = refs[0][2];
            refs[0][0] = refs[i][0];
            refs[0][1] = refs[i][1];
            refs[0][2] = refs[i][2];
            refs[i][0] = aux[0];
            refs[i][1] = aux[1];
            refs[i][2] = aux[2];
            int curr_len = 1;
            if (curr_len == longest_path_refs_len) {
                n_solutions = n_solutions + 1;
            } else {
                if (curr_len > longest_path_refs_len) {
                    n_solutions = 1;
                    longest_path_refs_len = curr_len;
                    for (int j = 0; j < curr_len; j = j + 1) {
                        longest_path_refs[j][0] = refs[j][0];
                        longest_path_refs[j][1] = refs[j][1];
                        longest_path_refs[j][2] = refs[j][2];
                    }
                }
                int last_char = refs[curr_len - 1][1];
                for (int k = curr_len; k < refs_len; k = k + 1) {
                    if (refs[k][2] == last_char) {
                        int aux2[3];
                        aux2[0] = refs[curr_len][0];
                        aux2[1] = refs[curr_len][1];
                        aux2[2] = refs[curr_len][2];
                        refs[curr_len][0] = refs[k][0];
                        refs[curr_len][1] = refs[k][1];
                        refs[curr_len][2] = refs[k][2];
                        refs[k][0] = aux2[0];
                        refs[k][1] = aux2[1];
                        refs[k][2] = aux2[2];
                        curr_len = curr_len + 1;
                        if (curr_len == longest_path_refs_len) {
                            n_solutions = n_solutions + 1;
                        } else {
                            if (curr_len > longest_path_refs_len) {
                                n_solutions = 1;
                                longest_path_refs_len = curr_len;
                                for (int j = 0; j < curr_len; j = j + 1) {
                                    longest_path_refs[j][0] = refs[j][0];
                                    longest_path_refs[j][1] = refs[j][1];
                                    longest_path_refs[j][2] = refs[j][2];
                                }
                            }
                        }
                        refs[k][0] = refs[curr_len][0];
                        refs[k][1] = refs[curr_len][1];
                        refs[k][2] = refs[curr_len][2];
                        refs[curr_len][0] = aux2[0];
                        refs[curr_len][1] = aux2[1];
                        refs[curr_len][2] = aux2[2];
                        curr_len = curr_len - 1;
                    }
                }
            }
            refs[i][0] = refs[0][0];
            refs[i][1] = refs[0][1];
            refs[i][2] = refs[0][2];
            refs[0][0] = aux[0];
            refs[0][1] = aux[1];
            refs[0][2] = aux[2];
        }
    }

    longest_path_len = longest_path_refs_len;
    for (int i = 0; i < 5; i = i + 1) {
        if (i < longest_path_len) {
            longest_path[i] = longest_path_refs[i][0];
        }
    }
    return;
}
