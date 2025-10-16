int func(int arr[10]) {
    int i;
    for (i = 0; i < 10; i = i + 1) {
        arr[i] = -4 + i;
        if (i > 5) {
            arr[i] = arr[i] + 95;
        }
    }
    return;
}
