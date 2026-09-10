int probmems_array_sum_threshold(int a[3], int threshold) {
    int sum = a[0] + a[1];
    sum = sum + a[2];
    if (sum > threshold) {
        return a[2];
    }
    return a[0];
}
