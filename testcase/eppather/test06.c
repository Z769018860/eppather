void bubble(int n, int a[10]) {
    int i, j, lx;
    i = n - 1;

    while (i > 0) {
        lx = 0;
        j = 0;
        while (j < i) {
            if (a[j + 1] < a[j]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                lx = j;
            }
            j = j + 1;
        }
        i = lx;
    }
}
