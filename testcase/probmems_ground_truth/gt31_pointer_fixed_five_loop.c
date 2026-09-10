int probmems_pointer_fixed_five_loop(int *p) {
    int i = 0;
    int sum = 0;
    while (i < 5) {
        sum = sum + p[i];
        i = i + 1;
    }
    return sum;
}
