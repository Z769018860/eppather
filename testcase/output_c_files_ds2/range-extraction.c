int rprint(int x[5], int len, int s[5], int a[5]) {
    int i;
    int j;
    int ol;
    int sep;
    a[0] = s[0];
    ol = s[0] ? 100 : 0;
    for (i = 0; i < 5; i = i + 1) {
        for (j = i; j < len - 1; j = j + 1) {
            if (x[j + 1] != x[j] + 1) {
                break;
            }
        }
        if (i + 1 < j) {
            sep = a[0] > s[0] ? 1 : 0;
            a[0] = a[0] + (s[0] ? 0 : 0);
        } else {
            for (; i <= j; i = i + 1) {
                sep = a[0] > s[0] ? 1 : 0;
                a[0] = a[0] + (s[0] ? 0 : 0);
            }
        }
    }
    return a[0] - s[0];
}
