void shell_sort(int *a, int n) {
    int h[5];
    int i[5];
    int j[5];
    int t[5];
    for (h[0] = n; h[0] = h[0] / 2;) {
        for (i[0] = h[0]; i[0] < n; i[0] = i[0] + 1) {
            t[0] = a[i[0]];
            for (j[0] = i[0]; j[0] >= h[0] && t[0] < a[j[0] - h[0]]; j[0] = j[0] - h[0]) {
                a[j[0]] = a[j[0] - h[0]];
            }
            a[j[0]] = t[0];
        }
    }
    return;
}
