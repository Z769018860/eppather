void gnome_sort(int *a, int n) {
    int i;
    int j;
    int t;
    i = 1;
    j = 2;
    for (; i < n; ) {
        if (a[i - 1] > a[i]) {
            t = a[i - 1];
            a[i - 1] = a[i];
            a[i] = t;
            i = i - 1;
            if (i != 0) {
                continue;
            }
        }
        i = j;
        j = j + 1;
    }
    return;
}
