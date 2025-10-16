void bubble_sort(int *a, int n) {
    int i[5];
    int t[5];
    int j[5];
    int s[5];
    j[0] = n;
    s[0] = 1;
    for (; s[0] != 0; ) {
        s[0] = 0;
        for (i[0] = 1; i[0] < j[0]; i[0] = i[0] + 1) {
            if (a[i[0]] < a[i[0] - 1]) {
                t[0] = a[i[0]];
                a[i[0]] = a[i[0] - 1];
                a[i[0] - 1] = t[0];
                s[0] = 1;
            }
        }
        j[0] = j[0] - 1;
    }
    return;
}
