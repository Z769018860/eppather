int list_cmp(int* a, int* b, int c, int d) {
    int i;
    for (i = 0; i < c && i < d; i = i + 1) {
        if (a[i] < b[i]) {
            return -1;
        }
        if (a[i] > b[i]) {
            return 1;
        }
    }
    if (c < d) {
        return -1;
    }
    if (c > d) {
        return 1;
    }
    return 0;
}

int list_less_or_eq(int* a, int* b, int c, int d) {
    if (list_cmp(a, b, c, d) != 1) {
        return 1;
    } else {
        return 0;
    }
}
