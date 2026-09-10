int probmems_pointer_alias_candidate(int *p, int *q, int x) {
    p[0] = x;
    if (q[0] > p[0]) {
        q[0] = q[0] - p[0];
    }
    return q[0];
}
