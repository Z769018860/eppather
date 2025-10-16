int threeSum(int arr[5], int target) {
    int i, j, k;
    for (i = 0; i < 3; i = i + 1) {
        for (j = i + 1; j < 4; j = j + 1) {
            for (k = j + 1; k < 5; k = k + 1) {
                if (arr[i] + arr[j] + arr[k] == target) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
