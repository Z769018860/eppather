void counting_sort_mm(int ages[100], int n, int min, int max) {
    int count[140];
    int i;
    int j;
    int z;
    for (i = 0; i < 140; i = i + 1) {
        count[i] = 0;
    }
    for (i = 0; i < 100; i = i + 1) {
        count[ages[i]] = count[ages[i]] + 1;
    }
    z = 0;
    for (i = 0; i < 140; i = i + 1) {
        for (j = 0; j < count[i]; j = j + 1) {
            ages[z] = i;
            z = z + 1;
        }
    }
    return;
}
