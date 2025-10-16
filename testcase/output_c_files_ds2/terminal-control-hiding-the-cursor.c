void dummy_function(int n) {
    int arr[5];
    for (arr[0] = 0; arr[0] < 5; arr[0] = arr[0] + 1) {
        if (arr[0] < 3) {
            arr[1] = arr[0];
        } else {
            arr[2] = arr[0];
        }
    }
    return;
}
