int probmems_array_pointer_loop_branch(int a[5], int n) {
    int *p = a;
    int i = 0;
    int sum = 0;
    while ((i < n) && (i < 5)) {
        if (p[i] != 0) {
            sum = sum + a[i];
        }
        i = i + 1;
    }
    return sum;
}
