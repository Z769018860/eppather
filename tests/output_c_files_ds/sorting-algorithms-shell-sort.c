void shell_sort(int *a, int n) {
    int h;
    int i;
    int j;
    int t;
    for (h = n; h = h / 2;) {
        for (i = h; i < n; i = i + 1) {
            t = a[i];
            for (j = i; j >= h && t < a[j - h]; j = j - h) {
                a[j] = a[j - h];
            }
            a[j] = t;
        }
    }
    return;
}
