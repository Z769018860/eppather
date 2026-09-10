int probmems_array_pointer_copy(int a[4], int b[4]) {
    int *src = a;
    int *dst = b;
    int i = 0;
    while (i < 4) {
        dst[i] = src[i];
        i = i + 1;
    }
    return dst[0];
}
