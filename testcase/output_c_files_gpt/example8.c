int countAlternatingPeaksAndValleys(int arr[5], int size) {
    int count = 0;
    int isPeak = 0;
    int i = 1;

    if (size < 3) {
        return 0;
    }

    for (i = 1; i < size - 1; i = i + 1) {
        if (arr[i] > arr[i - 1]) {
            if (arr[i] > arr[i + 1]) {
                if (isPeak == 0) {
                    count = count + 1;
                    isPeak = 1;
                }
            }
        }

        if (arr[i] < arr[i - 1]) {
            if (arr[i] < arr[i + 1]) {
                if (isPeak == 1) {
                    count = count + 1;
                    isPeak = 0;
                }
            }
        }
    }

    return count;
}
