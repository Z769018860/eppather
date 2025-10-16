void counting_sort_mm_min_max(int array[5], int n, int min[5], int max[5]) {
    int count[5];
    int i;
    int j;
    int z;
    int range;
    int n1;
    int n2;
    
    min[0] = array[0];
    max[0] = array[0];
    for (i = 1; i < 5; i = i + 1) {
        if (array[i] < min[0]) {
            min[0] = array[i];
        } else {
            if (array[i] > max[0]) {
                max[0] = array[i];
            }
        }
    }
    
    range = max[0] - min[0] + 1;
    for (i = 0; i < 5; i = i + 1) {
        count[i] = 0;
    }
    for (i = 0; i < 5; i = i + 1) {
        n1 = array[i] - min[0];
        count[n1] = count[n1] + 1;
    }
    
    z = 0;
    for (i = min[0]; i <= max[0]; i = i + 1) {
        n2 = i - min[0];
        for (j = 0; j < count[n2]; j = j + 1) {
            array[z] = i;
            z = z + 1;
        }
    }
    
    return;
}
