int probmems_array_prefix_conditional(int a[4], int n) {
    int i = 0;
    int sum = 0;
    while ((i < n) && (i < 4)) {
        if (a[i] > 0) {
            sum = sum + a[i];
        }
        i = i + 1;
    }
    return sum;
}
