int partial_calculations(int arr[8]) {
    int i;
    for (i = 0; i < 4; i = i + 1) {
        arr[i] = (i + 1) * (i + 1);
    }
    for (i = 4; i < 8; i = i + 1) {
        arr[i] = (i - 3) * 2;
    }
    return;
}
