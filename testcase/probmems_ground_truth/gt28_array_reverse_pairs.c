int probmems_array_reverse_pairs(int a[6]) {
    int i = 0;
    int sum = 0;
    while (i < 3) {
        sum = sum + a[i] + a[5 - i];
        i = i + 1;
    }
    return sum;
}
