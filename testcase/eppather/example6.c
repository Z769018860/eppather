int countSpecialElements(int arr[10], int size) {
    int count = 0;

    for (int i = 0; i < size; i = i + 1) {
        if (i % 2 == 0) {
            if (arr[i] % 2 == 0) {
                count = count + 1;
            }
            ;
        }

        if (i % 2 != 0) {
            if (arr[i] % 2 != 0) {
                count = count + 1;
            }
            ;
        }

        if (arr[i] > 0) {
            if (i > 0 && arr[i] > arr[i - 1]) {
                count = count + 1;
            }
            ;
        }

        if (arr[i] < 0) {
            if (i < size - 1 && arr[i] < arr[i + 1]) {
                count = count + 1;
            }
            ;
        }
        ;
    }

    return count;
}
