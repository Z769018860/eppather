int list_less_or_eq(int a, int b, int c, int d) {
    int cmp_result;
    cmp_result = list_cmp(a, b, c, d);
    if (cmp_result != 1) {
        return 1;
    } else {
        return 0;
    }
    return;
}
