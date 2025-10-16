int countAlternatingPeaksAndValleys(int arr[5]) {
    int count;
    int isPeak;
    int i;
    
    count = 0;
    isPeak = 0;
    
    if (5 < 3) {
        return 0;
    }
    
    for (i = 1; i < 5 - 1; i = i + 1) {
        if (arr[i] > 0) {
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
                    if (isPeak != 0) {
                        count = count + 1;
                        isPeak = 0;
                    }
                }
            }
        }
    }
    
    return count;
}
