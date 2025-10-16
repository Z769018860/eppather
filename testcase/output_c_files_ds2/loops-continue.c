void func() {
    int i;
    int arr[5];
    for (i = 1; i <= 5; i = i + 1) {
        arr[0] = i;
        if (arr[0] % 5 == 0) {
            continue;
        }
    }
    return;
}
