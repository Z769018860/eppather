int probmems_array_pointer_alias_read(int a[4], int x) {
    int *p = a;
    int sum = p[0];
    if (x > 0) {
        sum = sum + a[1];
    } else {
        sum = sum + p[2];
    }
    return sum + a[3];
}
