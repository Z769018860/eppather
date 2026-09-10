int probmems_two_array_dot(int a[4], int b[4]) {
    int i = 0;
    int sum = 0;
    while (i < 4) {
        sum = sum + a[i] * b[i];
        i = i + 1;
    }
    return sum;
}
