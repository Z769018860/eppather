void solve24(int n[5], int n_cards, int solve_goal, int max_digit) {
    int ex_value[5];
    int ex_left[5];
    int ex_right[5];
    int ex_op[5];
    int e[5];
    int i;
    int j;
    int k;
    int node_left;
    int node_right;
    int node_op;
    int final_num;
    int final_denom;
    int left_num;
    int left_denom;
    int right_num;
    int right_denom;
    int temp_ex[5];
    int len;
    int result;

    for (i = 0; i < n_cards; i = i + 1) {
        e[i] = i;
        ex_op[i] = 0;
        ex_left[i] = 0;
        ex_right[i] = 0;
        ex_value[i] = n[i];
    }

    len = n_cards;
    if (len == 1) {
        if (ex_op[e[0]] == 0) {
            final_num = ex_value[e[0]];
            final_denom = 1;
        } else {
            left_num = ex_value[ex_left[e[0]]];
            left_denom = 1;
            right_num = ex_value[ex_right[e[0]]];
            right_denom = 1;
            switch (ex_op[e[0]]) {
                case 1: {
                    final_num = left_num * right_denom + left_denom * right_num;
                    final_denom = left_denom * right_denom;
                    break;
                }
                case 2: {
                    final_num = left_num * right_denom - left_denom * right_num;
                    final_denom = left_denom * right_denom;
                    break;
                }
                case 3: {
                    final_num = left_num * right_num;
                    final_denom = left_denom * right_denom;
                    break;
                }
                case 4: {
                    final_num = left_num * right_denom;
                    final_denom = left_denom * right_num;
                    break;
                }
            }
        }
        if (final_num == final_denom * solve_goal && final_denom != 0) {
            result = 1;
        } else {
            result = 0;
        }
        return;
    }

    for (i = 0; i < len - 1; i = i + 1) {
        for (j = i + 1; j < len; j = j + 1) {
            temp_ex[j - 1] = e[j];
        }
        node_left = e[i];
        node_right = e[i + 1];
        for (j = i + 1; j < len; j = j + 1) {
            for (node_op = 1; node_op <= 4; node_op = node_op + 1) {
                ex_op[n_cards] = node_op;
                ex_left[n_cards] = node_left;
                ex_right[n_cards] = node_right;
                temp_ex[i] = n_cards;
                solve24(n, n_cards + 1, solve_goal, max_digit);
            }
            node_left = e[j];
            node_right = e[i];
            ex_op[n_cards] = 2;
            ex_left[n_cards] = node_left;
            ex_right[n_cards] = node_right;
            temp_ex[i] = n_cards;
            solve24(n, n_cards + 1, solve_goal, max_digit);
            ex_op[n_cards] = 4;
            ex_left[n_cards] = node_left;
            ex_right[n_cards] = node_right;
            temp_ex[i] = n_cards;
            solve24(n, n_cards + 1, solve_goal, max_digit);
            temp_ex[j] = e[j];
        }
        temp_ex[i] = e[i];
    }
    return;
}
