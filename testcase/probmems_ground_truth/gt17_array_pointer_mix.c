int probmems_array_pointer_mix(int a[3], int *p, int x) {
    int result = a[0];
    if (x > a[1]) {
        p[0] = a[2];
        result = result + p[0];
    } else {
        result = result + a[1];
    }
    return result;
}
