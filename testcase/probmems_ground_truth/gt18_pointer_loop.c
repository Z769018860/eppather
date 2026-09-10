int probmems_pointer_loop(int *p, int n) {
    int i = 0;
    int sum = 0;
    while ((i < n) && (i < 3)) {
        sum = sum + p[i];
        i = i + 1;
    }
    return sum;
}
