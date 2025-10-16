int counting_sort(int array[100], int n, int min, int max) {
    int count[100];
    int i;
    int j;
    int z;
    int range;
    
    range = max - min + 1;
    for (i = 0; i < range; i = i + 1) {
        count[i] = 0;
    }
    for (i = 0; i < n; i = i + 1) {
        count[array[i] - min] = count[array[i] - min] + 1;
    }
    z = 0;
    for (i = min; i <= max; i = i + 1) {
        for (j = 0; j < count[i - min]; j = j + 1) {
            array[z] = i;
            z = z + 1;
        }
    }
    
    for (i = 0; i < n; i = i + 1) {
        if (array[i] < min) {
            min = array[i];
        }
        if (array[i] > max) {
            max = array[i];
        }
    }
    return;
}
