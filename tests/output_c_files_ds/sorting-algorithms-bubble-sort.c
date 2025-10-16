void bubble_sort(int a[10], int n) {
    int i;
    int t;
    int j = n;
    int s = 1;
    for (; s != 0; ) {
        s = 0;
        for (i = 1; i < j; i = i + 1) {
            if (a[i] < a[i - 1]) {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                s = 1;
            }
        }
        j = j - 1;
    }
    return;
}
