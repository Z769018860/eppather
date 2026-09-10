int probmems_array_conditional_write(int a[3], int x) {
    if (x > 0) {
        a[0] = a[1];
    } else {
        a[0] = a[2];
    }
    return a[0];
}
