void bead_sort(int *a, int len) {
    int max;
    int sum;
    int i;
    int j;
    int k;
    int beads[100][100];
    
    max = a[0];
    for (i = 1; i < len; i = i + 1) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    
    for (i = 0; i < len; i = i + 1) {
        for (j = 0; j < max; j = j + 1) {
            beads[i][j] = 0;
        }
    }
    
    for (i = 0; i < len; i = i + 1) {
        for (j = 0; j < a[i]; j = j + 1) {
            beads[i][j] = 1;
        }
    }
    
    for (j = 0; j < max; j = j + 1) {
        sum = 0;
        for (i = 0; i < len; i = i + 1) {
            sum = sum + beads[i][j];
            beads[i][j] = 0;
        }
        for (i = len - sum; i < len; i = i + 1) {
            beads[i][j] = 1;
        }
    }
    
    for (i = 0; i < len; i = i + 1) {
        k = 0;
        for (j = 0; j < max; j = j + 1) {
            if (beads[i][j] != 0) {
                k = k + 1;
            } else {
                break;
            }
        }
        a[i] = k;
    }
    return;
}
