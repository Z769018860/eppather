void selection_sort(int* a, int n) {
    int i;
    int j;
    int m;
    int t;
    for (i = 0; i < n; i = i + 1) {
        for (j = i, m = i; j < n; j = j + 1) {
            if (a[j] < a[m]) {
                m = j;
            }
        }
        t = a[i];
        a[i] = a[m];
        a[m] = t;
    }
    return;
}
