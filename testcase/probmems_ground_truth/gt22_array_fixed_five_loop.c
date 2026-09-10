int probmems_array_fixed_five_loop(int a[5]) {
    int i = 0;
    int sum = 0;
    while (i < 5) {
        sum = sum + a[i];
        i = i + 1;
    }
    return sum;
}
