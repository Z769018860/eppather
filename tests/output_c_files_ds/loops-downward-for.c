void func() {
    int i;
    int arr[11];
    for (i = 10; i >= 0; i = i - 1) {
        arr[10 - i] = i;
    }
    return;
}
