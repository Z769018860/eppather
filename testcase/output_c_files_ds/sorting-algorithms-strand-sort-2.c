void sort(int arr[15]) {
    int i;
    int j;
    int temp;
    for (i = 0; i < 15; i = i + 1) {
        for (j = 0; j < 14; j = j + 1) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return;
}
