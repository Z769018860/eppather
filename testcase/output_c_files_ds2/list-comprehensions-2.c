int func(int f, int t, int* e, int* nx) {
    int i;
    int arr[5];
    arr[0] = f + 1;
    for (i = arr[0]; i <= t; i = i + 1) {
        e[0] = nx[0];
        nx[0] = i;
    }
    return;
}
