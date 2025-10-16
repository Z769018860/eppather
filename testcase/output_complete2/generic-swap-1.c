void swap(int* va, int* vb, int s) {
    int a[5];
    int b[5];
    int t[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (i < s) {
            t[0] = va[i];
            va[i] = vb[i];
            vb[i] = t[0];
        }
    }
    return;
}
