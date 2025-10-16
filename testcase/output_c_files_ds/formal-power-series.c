double term(int type, double a0, int s1_type, double s1_a0, int s2_type, double s2_a0, int n) {
    double ret = 0;
    int i;
    
    if (type == 0) {
        if (n > 0) {
            return 0;
        } else {
            return a0;
        }
    } else if (type == 1) {
        ret = term(s1_type, s1_a0, 0, 0, 0, 0, n) + term(s2_type, s2_a0, 0, 0, 0, 0, n);
    } else if (type == 2) {
        ret = term(s1_type, s1_a0, 0, 0, 0, 0, n) - term(s2_type, s2_a0, 0, 0, 0, 0, n);
    } else if (type == 3) {
        for (i = 0; i <= n; i = i + 1) {
            ret = ret + term(s1_type, s1_a0, 0, 0, 0, 0, i) * term(s2_type, s2_a0, 0, 0, 0, 0, n - i);
        }
    } else if (type == 4) {
        if (term(s2_type, s2_a0, 0, 0, 0, 0, 0) == 0) {
            return 0;
        }
        ret = term(s1_type, s1_a0, 0, 0, 0, 0, n);
        for (i = 1; i <= n; i = i + 1) {
            ret = ret - term(s2_type, s2_a0, 0, 0, 0, 0, i) * term(type, a0, s1_type, s1_a0, s2_type, s2_a0, n - i) / term(s2_type, s2_a0, 0, 0, 0, 0, 0);
        }
    } else if (type == 5) {
        ret = n * term(s1_type, s1_a0, 0, 0, 0, 0, n + 1);
    } else if (type == 6) {
        if (n == 0) {
            return a0;
        }
        ret = term(s1_type, s1_a0, 0, 0, 0, 0, n - 1) / n;
    }
    return ret;
}
