int gcd(int m, int n) {
    int t;
    for (; m != 0;) {
        t = m;
        m = n % m;
        n = t;
    }
    return n;
}

void eval_tree(int e_op, int e_val, int e_left_op, int e_left_val, int e_right_op, int e_right_val, int* res_num, int* res_denom) {
    int l_num;
    int l_denom;
    int r_num;
    int r_denom;
    int t;
    if (e_op == 1) {
        *res_num = e_val;
        *res_denom = 1;
        return;
    }
    eval_tree(e_left_op, e_left_val, 0, 0, 0, 0, &l_num, &l_denom);
    eval_tree(e_right_op, e_right_val, 0, 0, 0, 0, &r_num, &r_denom);
    if (e_op == 2) {
        *res_num = l_num * r_denom + l_denom * r_num;
        *res_denom = l_denom * r_denom;
    }
    if (e_op == 3) {
        *res_num = l_num * r_denom - l_denom * r_num;
        *res_denom = l_denom * r_denom;
    }
    if (e_op == 4) {
        *res_num = l_num * r_num;
        *res_denom = l_denom * r_denom;
    }
    if (e_op == 5) {
        *res_num = l_num * r_denom;
        *res_denom = l_denom * r_num;
    }
    t = gcd(*res_denom, *res_num);
    if (t != 0) {
        *res_denom = *res_denom / t;
        *res_num = *res_num / t;
    }
    return;
}
