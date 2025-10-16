void heapPermute(int n, int arr[5], int arrLen) {
    int temp;
    int i;
    int flag = 1;
    
    if (n == 1) {
        flag = flag * -1;
    } else {
        for (i = 0; i < n - 1; i = i + 1) {
            heapPermute(n - 1, arr, arrLen);
            
            if (n % 2 == 0) {
                temp = arr[i];
                arr[i] = arr[n - 1];
                arr[n - 1] = temp;
            } else {
                temp = arr[0];
                arr[0] = arr[n - 1];
                arr[n - 1] = temp;
            }
        }
        heapPermute(n - 1, arr, arrLen);
    }
    return;
}
