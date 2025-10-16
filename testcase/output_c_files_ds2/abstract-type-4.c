int func(int arg1, int arg2) {
    int arr[5];
    arr[0] = arg1;
    arr[1] = arg2;
    for (int i = 0; i < 5; i = i + 1) {
        if (i < 2) {
            arr[i] = arr[i] + 1;
        } else {
            arr[i] = 0;
        }
    }
    return;
}
