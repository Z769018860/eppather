void quickSort(int arr[10]) {
    int low = 0;
    int high = 10;
    int pivot = arr[high];
    int j = low;
    while (j < high) {
        if (arr[j] <= pivot) {
            int temp = arr[j];
            arr[j] = pivot;
            pivot = temp;
        }
        j = j + 1;
    }
}
