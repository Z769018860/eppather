int vla_unsized_parameter(int a[], int n) {
    int i = 0;
    int sum = 0;
    while (i < n) {
        sum = sum + a[i];
        i = i + 1;
    }
    return sum;
}
