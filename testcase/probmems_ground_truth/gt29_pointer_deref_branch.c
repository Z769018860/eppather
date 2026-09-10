int probmems_pointer_deref_branch(int *p, int x) {
    int value = *p;
    if (x > value) {
        value = value + p[1];
    } else {
        value = value + p[2];
    }
    return value;
}
