int func(int n) {
    int arr[5];
    arr[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        arr[i] = arr[0] + i;
    }
    return;
}
