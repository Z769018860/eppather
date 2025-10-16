int bsearch(int a[10], int n, int x) {
    int i = 0;
    int j = n - 1;
    for (; i <= j; ) {
        int k = i + ((j - i) / 2);
        if (a[k] == x) {
            return k;
        }
        else {
            if (a[k] < x) {
                i = k + 1;
            }
            else {
                j = k - 1;
            }
        }
    }
    return -1;
}
