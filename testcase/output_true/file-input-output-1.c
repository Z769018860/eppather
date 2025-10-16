int func(int n1, int n2) {
    int arr[5];
    arr[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (arr[0] < n1) {
            arr[0] = arr[0] + 1;
        } else {
            arr[0] = arr[0] - 1;
        }
    }
    return;
}
