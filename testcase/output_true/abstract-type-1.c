int example_func(int param1, int param2) {
    int arr[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        arr[i] = param1 + param2 + i;
    }
    if (arr[0] > 10) {
        arr[0] = arr[0] - 5;
    } else {
        arr[0] = arr[0] + 5;
    }
    return arr[0];
}
