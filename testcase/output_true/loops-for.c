void func() {
    int i;
    int j;
    int arr[5];
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j <= i; j = j + 1) {
            arr[0] = 42;
        }
        arr[0] = 10;
    }
    return;
}
