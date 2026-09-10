int probmems_array_nested_two_three(int a[6]) {
    int i = 0;
    int j = 0;
    int sum = 0;
    while (i < 2) {
        j = 0;
        while (j < 3) {
            sum = sum + a[i * 3 + j];
            j = j + 1;
        }
        i = i + 1;
    }
    return sum;
}
