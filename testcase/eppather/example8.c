int countAlternatingPeaksAndValleys(int arr[10], int size) {
    int count = 0;
    int isPeak = 0;

    for (int i = 1; i < size - 1; i = i + 1) {
        if (arr[i] > 0) {
            if (arr[i] > arr[i - 1]) {
                if (arr[i] > arr[i + 1]) {
                    if (!isPeak) {
                        count = count + 1;
                        isPeak = 1;
                    }
                    ;
                }
                ;
            }

            if (arr[i] < arr[i - 1]) {
                if (arr[i] < arr[i + 1]) {
                    if (isPeak) {
                        count = count + 1;
                        isPeak = 0;
                    }
                    ;
                }
                ;
            }
            ;
        }
        ;
    }

    return count;
}
