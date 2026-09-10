int probmems_fixed_loop_array(int a[3]) {
    int i = 0;
    int sum = 0;
    while (i < 3) {
        sum = sum + a[i];
        i = i + 1;
    }
    return sum;
}
