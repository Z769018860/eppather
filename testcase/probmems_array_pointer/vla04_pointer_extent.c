int vla_pointer_extent(int *p, int n) {
    int i = 0;
    int sum = 0;
    while (i < n) {
        sum = sum + p[i];
        i = i + 1;
    }
    return sum;
}
