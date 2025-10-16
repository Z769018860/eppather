int func(int n) {
    int i;
    int arr[5];
    arr[0] = 1;
    for (i = 0; i < 5; i = i + 1) {
        if (arr[0] * arr[0] <= n) {
            arr[0] = arr[0] + 1;
        }
    }
    return;
}
