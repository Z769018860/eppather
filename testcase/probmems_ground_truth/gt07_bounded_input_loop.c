int probmems_bounded_input_loop(int a[4], int n) {
    int i = 0;
    int sum = 0;
    if (n < 0) {
        n = 0;
    }
    if (n > 4) {
        n = 4;
    }
    while (i < n) {
        sum = sum + a[i];
        i = i + 1;
    }
    return sum;
}
