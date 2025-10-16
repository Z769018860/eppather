int uniq(int *a, int len) {
    int i;
    int j;
    int temp;
    for (i = 0; i < len; i = i + 1) {
        for (j = i + 1; j < len; j = j + 1) {
            if (a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    j = 0;
    for (i = 0; i < len; i = i + 1) {
        if (a[i] != a[j]) {
            j = j + 1;
            a[j] = a[i];
        }
    }
    return j + 1;
}
