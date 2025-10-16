int parse(const char *s) {
    int l_queue = 0;
    int l_stack = 0;
    int prec_booster = 0;
    int stack_len[256];
    const char *stack_s[256];
    int queue_len[256];
    const char *queue_s[256];
    int matched = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int m = 0;
    int n = 0;
    int op_prec = 0;
    int op_assoc = 0;
    int t_prec = 0;
    int t_assoc = 0;
    int len = 0;
    const char *e = 0;
    const char *tok_s = 0;
    int tok_len = 0;
    int tok_assoc = 0;
    int tok_prec = 0;
    int paren_count = 0;
    int is_op = 0;
    int is_arg = 0;
    int is_eos = 0;

    for (i = 0; s[i] != '\0'; i = i + 1) {
        if (s[i] == ' ') {
            continue;
        }
        if (s[i] == '(') {
            paren_count = paren_count + 1;
            prec_booster = prec_booster + 100;
            continue;
        }
        if (s[i] == ')') {
            if (prec_booster < 100) {
                return 0;
            }
            prec_booster = prec_booster - 100;
            paren_count = paren_count - 1;
            continue;
        }
        if ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
            len = 1;
            for (j = i + 1; s[j] != '\0'; j = j + 1) {
                if ((s[j] >= '0' && s[j] <= '9') || (s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z')) {
                    len = len + 1;
                } else {
                    break;
                }
            }
            queue_s[l_queue] = s + i;
            queue_len[l_queue] = len;
            l_queue = l_queue + 1;
            i = i + len - 1;
            continue;
        }
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') {
            op_prec = 0;
            op_assoc = 0;
            if (s[i] == '*' && s[i + 1] == '*') {
                op_prec = 3;
                op_assoc = 1;
                i = i + 1;
            } else if (s[i] == '^') {
                op_prec = 3;
                op_assoc = 1;
            } else if (s[i] == '*' || s[i] == '/') {
                op_prec = 2;
                op_assoc = 0;
            } else if (s[i] == '+' || s[i] == '-') {
                op_prec = 1;
                op_assoc = 0;
            }
            op_prec = op_prec + prec_booster;
            tok_s = s + i;
            tok_len = (op_prec == 3 && op_assoc == 1) ? 2 : 1;
            tok_assoc = op_assoc;
            tok_prec = op_prec;
            for (k = l_stack - 1; k >= 0; k = k - 1) {
                t_prec = stack_len[k];
                t_assoc = (stack_s[k][0] == '*' && stack_s[k][1] == '*') ? 1 : 0;
                if (!(t_prec == tok_prec && t_assoc == 0) && t_prec <= tok_prec) {
                    break;
                }
                queue_s[l_queue] = stack_s[k];
                queue_len[l_queue] = (stack_s[k][0] == '*' && stack_s[k][1] == '*') ? 2 : 1;
                l_queue = l_queue + 1;
                l_stack = l_stack - 1;
            }
            stack_s[l_stack] = tok_s;
            stack_len[l_stack] = tok_prec;
            l_stack = l_stack + 1;
            i = i + tok_len - 1;
            continue;
        }
    }
    for (m = l_stack - 1; m >= 0; m = m - 1) {
        queue_s[l_queue] = stack_s[m];
        queue_len[l_queue] = (stack_s[m][0] == '*' && stack_s[m][1] == '*') ? 2 : 1;
        l_queue = l_queue + 1;
    }
    if (paren_count != 0) {
        return 0;
    }
    return 1;
}
