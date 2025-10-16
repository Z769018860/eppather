int fruits(int x) {
    int arr[5];
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;
    for (int i = 0; i < 5; i = i + 1) {
        if (x == arr[i]) {
            return arr[i];
        }
    }
    return;
}
