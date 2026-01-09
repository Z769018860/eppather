void bubbleSort(int arr[10]) {
    int i = 0;
    while (i < 10) {
        if (arr[i] > arr[i + 1]) {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
        i = i + 1;
    }
}
