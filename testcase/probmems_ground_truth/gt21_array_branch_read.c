int probmems_array_branch_read(int a[4], int x) {
    int value = a[0];
    if (x > 0) {
        value = value + a[1];
    } else {
        value = value + a[2];
    }
    return value + a[3];
}
