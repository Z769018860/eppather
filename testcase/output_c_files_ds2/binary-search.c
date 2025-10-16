int bsearch_merged(int a[10], int n, int x, int i, int j, int is_recursive) {
    if (is_recursive == 0) {
        i = 0;
        j = n - 1;
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
    else {
        if (j < i) {
            return -1;
        }
        int k = i + ((j - i) / 2);
        if (a[k] == x) {
            return k;
        }
        else {
            if (a[k] < x) {
                return bsearch_merged(a, n, x, k + 1, j, 1);
            }
            else {
                return bsearch_merged(a, n, x, i, k - 1, 1);
            }
        }
    }
    return;
}
