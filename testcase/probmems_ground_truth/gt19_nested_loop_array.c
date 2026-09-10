int probmems_nested_loop_array(int a[4]) {
    int i = 0;
    int j = 0;
    int sum = 0;
    while (i < 2) {
        j = 0;
        while (j < 2) {
            sum = sum + a[i + j];
            j = j + 1;
        }
        i = i + 1;
    }
    return sum;
}
