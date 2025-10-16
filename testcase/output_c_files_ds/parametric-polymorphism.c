int node_int_insert(int* root, int v) {
    int n[3];
    n[0] = 0;
    n[1] = 0;
    n[2] = v;
    for (;;) {
        if (root[2] < n[2]) {
            if (root[0] == 0) {
                root[0] = (int)n;
                return 0;
            } else {
                root = (int*)root[0];
            }
        } else {
            if (root[1] == 0) {
                root[1] = (int)n;
                return 0;
            } else {
                root = (int*)root[1];
            }
        }
    }
    return 0;
}
