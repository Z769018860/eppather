int probmems_pointer_loop_branch(int *p, int n) {
    int i = 0;
    int sum = 0;
    while ((i < n) && (i < 5)) {
        if (p[i] > 0) {
            sum = sum + p[i];
        } else {
            sum = sum - p[i];
        }
        i = i + 1;
    }
    return sum;
}
