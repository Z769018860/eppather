void sort(int n, int a[10]) {
    int cur, j, low_ind, temp;

    for (cur = 0; cur < n - 1; cur = cur + 1) {
        low_ind = cur;
        for (j = cur + 1; j < n; j = j + 1) {
            if (a[j] < a[low_ind]) {
                low_ind = j;
            }
            ;
        }

        temp = a[cur];
        a[cur] = a[low_ind];
        a[low_ind] = temp;
    }

    return;
}
