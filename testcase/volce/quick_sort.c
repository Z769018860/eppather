static int partition(int arr[5], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int j;
    int temp;
    for (j = low; j <= high - 1; j = j + 1) {
        if (arr[j] <= pivot) {
            i = i + 1;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[5], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
