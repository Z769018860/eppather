void insert_append(int a, int b) {
    int arr[5];
    arr[0] = a;
    arr[1] = b;
    for (int i = 0; i < 5; i = i + 1) {
        if (i < 2) {
            arr[i] = arr[i];
        } else {
            arr[i] = 0;
        }
    }
    return;
}
