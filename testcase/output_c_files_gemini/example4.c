int countPeaksAndValleys(int* arr, int size) {
    int count;
    int i;
    if (size < 3) {
        return 0;
    }
    count = 0;
    for (i = 1; i < size - 1; i = i + 1) {
        if (arr[i] > arr[i - 1]) {
            if (arr[i] > arr[i + 1]) {
                count = count + 1;
            }
        } else {
            if (arr[i] < arr[i - 1]) {
                if (arr[i] < arr[i + 1]) {
                    count = count + 1;
                }
            }
        }
    }
    return count;
}
