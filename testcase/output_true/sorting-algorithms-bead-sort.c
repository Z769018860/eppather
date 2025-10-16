void bead_sort(int *a, int len) {
    int i;
    int j;
    int max;
    int sum;
    int beads[5][5];
    int n1;
    int n2;
    
    max = a[0];
    for (i = 1; i < len; i = i + 1) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            beads[i][j] = 0;
        }
    }
    
    for (i = 0; i < len; i = i + 1) {
        for (j = 0; j < a[i]; j = j + 1) {
            if (i < 5 && j < 5) {
                beads[i][j] = 1;
            }
        }
    }
    
    for (j = 0; j < max; j = j + 1) {
        sum = 0;
        for (i = 0; i < len; i = i + 1) {
            if (i < 5 && j < 5) {
                sum = sum + beads[i][j];
                beads[i][j] = 0;
            }
        }
        n1 = len - sum;
        for (i = n1; i < len; i = i + 1) {
            if (i < 5 && j < 5) {
                beads[i][j] = 1;
            }
        }
    }
    
    for (i = 0; i < len; i = i + 1) {
        j = 0;
        while (j < max && i < 5 && j < 5 && beads[i][j] != 0) {
            j = j + 1;
        }
        a[i] = j;
    }
    
    return;
}
