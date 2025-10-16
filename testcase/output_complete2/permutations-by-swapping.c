void heapPermute(int n, int arr[5], int arrLen) {
    int temp[5];
    int i;
    int flag[5];
    flag[0] = 1;

    if (n == 1) {
        for (i = 0; i < 5; i = i + 1) {
            if (i < arrLen) {
                temp[0] = arr[i];
            }
        }
        flag[0] = flag[0] * -1;
    } else {
        for (i = 0; i < n - 1; i = i + 1) {
            heapPermute(n - 1, arr, arrLen);
            if (n % 2 == 0) {
                temp[0] = arr[i];
                arr[i] = arr[n - 1];
                arr[n - 1] = temp[0];
            } else {
                temp[0] = arr[0];
                arr[0] = arr[n - 1];
                arr[n - 1] = temp[0];
            }
        }
        heapPermute(n - 1, arr, arrLen);
    }
    return;
}
