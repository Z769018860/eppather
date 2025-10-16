void process_arrays(int *a, int *b, int size) {
    int i;

    for (i = 0; i < size; i = i + 1) {
        while (a[i] != b[i]) {
            if (a[i] > b[i]) {
                if (a[i] < 10 && b[i] < 10) {
                    a[a[i]] = b[b[i]];
                }
                ;
            } else if (a[i] < b[i]) {
                a[i] = 0;
                b[i] = 0;
            }
            ;
        }
        ;
    }
}
