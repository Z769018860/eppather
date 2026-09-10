int probmems_pointer_branch_write(int *p, int x) {
    if (p[0] > x) {
        p[1] = p[0];
    } else {
        p[0] = x;
    }
    return p[0] + p[1];
}
