void gnome_sort(int a[5], int n) {
    int i[5];
    int j[5];
    int t[5];
    i[0] = 1;
    j[0] = 2;
    for (i[0] = 1; i[0] < n; i[0] = i[0] + 1) {
        if (a[i[0] - 1] > a[i[0]]) {
            t[0] = a[i[0] - 1];
            a[i[0] - 1] = a[i[0]];
            a[i[0]] = t[0];
            i[0] = i[0] - 1;
            if (i[0] != 0) {
                continue;
            }
        }
        i[0] = j[0];
        j[0] = j[0] + 1;
    }
    return;
}
