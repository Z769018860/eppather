int vla_local_bounded(int n) {
    int temp[n];
    int i = 0;
    int sum = 0;
    while (i < n) {
        temp[i] = i;
        sum = sum + temp[i];
        i = i + 1;
    }
    return sum;
}
