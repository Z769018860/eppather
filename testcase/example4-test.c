int countPeaksAndValleys(int arr[6], int size) {
    if (size < 3) 
        return 0;
    int count = 0;

    for (int i = 1; i < size - 1; i=i+1) {
        if (arr[i] > arr[i - 1]) {
            if (arr[i] > arr[i + 1]) {
                count=count+1; 
            }
            ;
        }

        else if (arr[i] < arr[i - 1]) {
            if (arr[i] < arr[i + 1]) {
                count=count+1; 
            }
            ;
        }
    }

    return count;
}
