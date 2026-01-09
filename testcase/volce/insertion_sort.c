void insertionSort(int arr[10]) {
    int i = 1;
    while (i < 10) {
        int key = arr[i];
        if (arr[i - 1] > key) {
            arr[i] = arr[i - 1];
            arr[i - 1] = key;
        }
        i = i + 1;
    }
}
