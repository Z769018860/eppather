void quickSort(int arr[5]) {
    int low = 0;
    int high = 2;
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
