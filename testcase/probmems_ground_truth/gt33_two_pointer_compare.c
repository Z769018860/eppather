int probmems_two_pointer_compare(int *p, int *q) {
    int left = *p;
    int right = *q;
    if (left > right) {
        return left + p[1];
    }
    return right + q[1];
}
