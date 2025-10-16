void complex_array_manipulations() {
    int arr[10];
    int size = 10;
    int i;
    int j;
    int temp;

    if (arr[0] % 2 == 0) {
        for (i = 0; i < size / 2; i = i + 1) {
            temp = arr[i];
            arr[i] = arr[size - i - 1];
            arr[size - i - 1] = temp;
        }
    } else {
        for (i = 0; i < size; i = i + 1) {
            arr[i] = arr[i] * arr[i];
        }
    }

    if ((arr[0] + arr[size - 1]) > 100) {
        for (i = 0; i < size; i = i + 1) {
            for (j = i + 1; j < size; j = j + 1) {
                if (arr[i] > arr[j]) {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    } else {
        int max = arr[0];
        for (i = 1; i < size; i = i + 1) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        for (i = 0; i < size; i = i + 1) {
            arr[i] = max;
        }
    }

    if (size > 5 && arr[5] % 10 == 0) {
        for (i = 0; i < size / 2; i = i + 1) {
            arr[i] = arr[i] * 2;
        }
    }
    return;
}
