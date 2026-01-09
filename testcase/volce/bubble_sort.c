void bubbleSort(int arr[100]) {
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
