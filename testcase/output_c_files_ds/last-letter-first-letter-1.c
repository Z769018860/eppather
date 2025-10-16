void search(int refs[100][3], int longest_path_refs[100][3], int* longest_path_refs_len, int* n_solutions, int curr_len, int refs_len) {
    if (curr_len == *longest_path_refs_len) {
        *n_solutions = *n_solutions + 1;
    } else {
        if (curr_len > *longest_path_refs_len) {
            *n_solutions = 1;
            *longest_path_refs_len = curr_len;
            for (int i = 0; i < curr_len; i = i + 1) {
                longest_path_refs[i][0] = refs[i][0];
                longest_path_refs[i][1] = refs[i][1];
                longest_path_refs[i][2] = refs[i][2];
            }
        }
    }

    int last_char = refs[curr_len - 1][2];
    for (int i = curr_len; i < refs_len; i = i + 1) {
        if (refs[i][1] == last_char) {
            int aux0 = refs[curr_len][0];
            int aux1 = refs[curr_len][1];
            int aux2 = refs[curr_len][2];
            refs[curr_len][0] = refs[i][0];
            refs[curr_len][1] = refs[i][1];
            refs[curr_len][2] = refs[i][2];
            refs[i][0] = aux0;
            refs[i][1] = aux1;
            refs[i][2] = aux2;
            search(refs, longest_path_refs, longest_path_refs_len, n_solutions, curr_len + 1, refs_len);
            refs[i][0] = refs[curr_len][0];
            refs[i][1] = refs[curr_len][1];
            refs[i][2] = refs[curr_len][2];
            refs[curr_len][0] = aux0;
            refs[curr_len][1] = aux1;
            refs[curr_len][2] = aux2;
        }
    }
    return;
}

void find_longest_chain(int items[100][20], int items_len, int longest_path[100], int* longest_path_len, int* n_solutions) {
    int refs[100][3];
    int longest_path_refs[100][3];
    int longest_path_refs_len_val = 0;
    *longest_path_len = 0;
    *n_solutions = 0;

    for (int i = 0; i < items_len; i = i + 1) {
        int itemsi_len = 0;
        while (items[i][itemsi_len] != 0) {
            itemsi_len = itemsi_len + 1;
        }
        if (itemsi_len <= 1) {
            return;
        }
        refs[i][0] = i;
        refs[i][1] = items[i][0];
        refs[i][2] = items[i][itemsi_len - 1];
    }

    for (int i = 0; i < items_len; i = i + 1) {
        int aux0 = refs[0][0];
        int aux1 = refs[0][1];
        int aux2 = refs[0][2];
        refs[0][0] = refs[i][0];
        refs[0][1] = refs[i][1];
        refs[0][2] = refs[i][2];
        refs[i][0] = aux0;
        refs[i][1] = aux1;
        refs[i][2] = aux2;
        search(refs, longest_path_refs, &longest_path_refs_len_val, n_solutions, 1, items_len);
        refs[i][0] = refs[0][0];
        refs[i][1] = refs[0][1];
        refs[i][2] = refs[0][2];
        refs[0][0] = aux0;
        refs[0][1] = aux1;
        refs[0][2] = aux2;
    }

    *longest_path_len = longest_path_refs_len_val;
    for (int i = 0; i < *longest_path_len; i = i + 1) {
        longest_path[i] = longest_path_refs[i][0];
    }
    return;
}
