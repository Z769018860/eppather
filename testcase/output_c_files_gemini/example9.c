int countOddEvenIndexRelations(int* arr, int size) {
    int count;
    int i;
    if (size < 2) {
        return 0;
    }
    count = 0;
    for (i = 1; i < size - 1; i = i + 1) {
        if (i % 2 != 0) {
            if (arr[i] % 2 == 0) {
                if (arr[i] < arr[i - 1]) {
                    if (arr[i] != 0) {
                        count = count + 1;
                    }
                }
            }
        }
        if (i % 2 == 0) {
            if (arr[i] % 2 != 0) {
                if (arr[i] > arr[i + 1]) {
                    if (arr[i] != 0) {
                        count = count + 1;
                    }
                }
            }
        }
    }
    return count;
}
