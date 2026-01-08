void bubbleSort(int arr[5]) {
    int i, j, temp;
    for (i = 0; i < 4; i = i + 1) {
        for (j = 0; j < 4 - i; j = j + 1) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            ;
        }
        ;
    }
}
