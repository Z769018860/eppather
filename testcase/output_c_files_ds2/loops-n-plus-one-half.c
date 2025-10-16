int func(int n) {
    int i;
    int arr[5];
    arr[0] = 1;
    for (i = 0; i < 5; i = i + 1) {
        arr[0] = arr[0] + i;
        if (arr[0] == 10) {
            arr[1] = 0;
        } else {
            arr[1] = 1;
        }
    }
    return;
}
