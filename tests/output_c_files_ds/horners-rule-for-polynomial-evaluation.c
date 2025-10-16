int horner(int* coeffs, int s, int x) {
    int res = 0;
    int i;
    for (i = s - 1; i >= 0; i = i - 1) {
        res = res * x + coeffs[i];
    }
    return res;
}
