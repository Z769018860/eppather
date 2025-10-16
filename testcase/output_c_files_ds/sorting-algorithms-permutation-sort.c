void perm_sort(int a[5], int n, int msize, int (*_cmp)(int, int)) {
    int tmp;
    int i;
    int j;
    int k;
    int l;
    int p;
    int q;
    for (k = n - 1; k > 0; k = k - 1) {
        if (_cmp(a[k - 1], a[k]) > 0) {
            break;
        }
    }
    if (k <= 0) {
        return;
    }
    for (l = n - 1; l > k - 1; l = l - 1) {
        if (_cmp(a[k - 1], a[l]) > 0) {
            break;
        }
    }
    tmp = a[k - 1];
    a[k - 1] = a[l];
    a[l] = tmp;
    for (i = k, j = n - 1; i < j; i = i + 1, j = j - 1) {
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
    return;
}
