void topological_sort() {
    const char* input_lines[16] = {
        "des_system_lib   std synopsys std_cell_lib des_system_lib dw02 dw01 ramlib ieee",
        "dw01             ieee dw01 dware gtech",
        "dw02             ieee dw02 dware",
        "dw03             std synopsys dware dw03 dw02 dw01 ieee gtech",
        "dw04             dw04 ieee dw01 dware gtech",
        "dw05             dw05 ieee dware",
        "dw06             dw06 ieee dware",
        "dw07             ieee dware",
        "dware            ieee dware",
        "gtech            ieee gtech",
        "ramlib           std ieee",
        "std_cell_lib     ieee std_cell_lib",
        "synopsys",
        "cycle_11      cycle_12",
        "cycle_12      cycle_11",
        "cycle_21      dw01 cycle_22 dw02 dw03"
    };

    int item_count = 0;
    char* item_names[32];
    int deps[32][32];
    int dep_counts[32] = {0};
    int depths[32] = {0};
    int visited[32] = {0};

    for (int line = 0; line < 16; line = line + 1) {
        const char* s = input_lines[line];
        int parent_idx = -1;
        int word_start = 1;
        char word[32];
        int word_len = 0;

        for (int i = 0; s[i] != '\0'; i = i + 1) {
            if (s[i] == ' ' || s[i] == '\t') {
                if (word_len > 0) {
                    word[word_len] = '\0';
                    int found = 0;
                    for (int j = 0; j < item_count; j = j + 1) {
                        int match = 1;
                        for (int k = 0; word[k] != '\0'; k = k + 1) {
                            if (word[k] != item_names[j][k]) {
                                match = 0;
                                break;
                            }
                        }
                        if (match && word[k] == '\0' && item_names[j][k] == '\0') {
                            found = 1;
                            if (word_start) {
                                parent_idx = j;
                                word_start = 0;
                            } else {
                                deps[parent_idx][dep_counts[parent_idx]] = j;
                                dep_counts[parent_idx] = dep_counts[parent_idx] + 1;
                            }
                            break;
                        }
                    }
                    if (!found) {
                        item_names[item_count] = word;
                        if (word_start) {
                            parent_idx = item_count;
                            word_start = 0;
                        } else {
                            deps[parent_idx][dep_counts[parent_idx]] = item_count;
                            dep_counts[parent_idx] = dep_counts[parent_idx] + 1;
                        }
                        item_count = item_count + 1;
                    }
                    word_len = 0;
                }
            } else {
                word[word_len] = s[i];
                word_len = word_len + 1;
            }
        }
    }

    for (int i = 0; i < item_count; i = i + 1) {
        if (!visited[i]) {
            int stack[32];
            int stack_ptr = 0;
            stack[stack_ptr] = i;
            stack_ptr = stack_ptr + 1;
            visited[i] = 1;

            while (stack_ptr > 0) {
                int current = stack[stack_ptr - 1];
                int all_visited = 1;

                for (int j = 0; j < dep_counts[current]; j = j + 1) {
                    int dep = deps[current][j];
                    if (!visited[dep]) {
                        stack[stack_ptr] = dep;
                        stack_ptr = stack_ptr + 1;
                        visited[dep] = 1;
                        all_visited = 0;
                        break;
                    }
                }

                if (all_visited) {
                    int max_depth = 1;
                    for (int j = 0; j < dep_counts[current]; j = j + 1) {
                        int dep = deps[current][j];
                        if (depths[dep] + 1 > max_depth) {
                            max_depth = depths[dep] + 1;
                        }
                    }
                    depths[current] = max_depth;
                    stack_ptr = stack_ptr - 1;
                }
            }
        }
    }

    return;
}
