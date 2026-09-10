int probmems_array_input_bounded_five(int a[5], int n) {
    int i = 0;
    int sum = 0;
    while ((i < n) && (i < 5)) {
        sum = sum + a[i];
        i = i + 1;
    }
    return sum;
}
