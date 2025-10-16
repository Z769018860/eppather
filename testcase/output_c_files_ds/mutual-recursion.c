int F_M(int n, int is_F) {
    if (is_F == 1) {
        if (n == 0) {
            return 1;
        } else {
            return n - F_M(F_M(n - 1, 1), 0);
        }
    } else {
        if (n == 0) {
            return 0;
        } else {
            return n - F_M(F_M(n - 1, 0), 1);
        }
    }
    return;
}
