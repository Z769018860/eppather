void bubble_sort(int *idx, int n_idx, int *buf) {
    int i;
    int j;
    int tmp;
    for (i = 0; i < n_idx; i = i + 1) {
        for (j = i + 1; j < n_idx; j = j + 1) {
            if (idx[j] < idx[i]) {
                tmp = idx[j];
                idx[j] = idx[i];
                idx[i] = tmp;
            }
        }
    }
    for (i = 0; i < n_idx; i = i + 1) {
        for (j = i + 1; j < n_idx; j = j + 1) {
            if (buf[idx[j]] < buf[idx[i]]) {
                tmp = buf[idx[j]];
                buf[idx[j]] = buf[idx[i]];
                buf[idx[i]] = tmp;
            }
        }
    }
    return;
}
