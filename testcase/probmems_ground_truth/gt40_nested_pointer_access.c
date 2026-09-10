int probmems_nested_pointer_access(int *p) {
    int i = 0;
    int j = 0;
    int sum = 0;
    while (i < 2) {
        j = 0;
        while (j < 3) {
            sum = sum + p[i * 3 + j];
            j = j + 1;
        }
        i = i + 1;
    }
    return sum;
}
