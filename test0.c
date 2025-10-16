int countPeaksAndValleys(int* arr, int size) {
    int count;
    int i;

    count = 0;
        if (arr[i] > arr[i - 1]) {
            if (arr[i] > arr[i + 1]) {
                count = count + 1;
            }
        } 
        else {
            if (arr[i] < arr[i - 1]) {
                if (arr[i] < arr[i + 1]) {
                    count = count + 1;
                }
            }
        }
    return count;
}
