void sort_and_print(int argc, char* argv[]) {
    int arr[5];
    int i;
    int j;
    int temp;
    int n;
    n = 5;
    
    for (i = 0; i < n; i = i + 1) {
        arr[i] = 0;
    }
    
    for (i = 1; i < argc; i = i + 1) {
        if (i - 1 < n) {
            arr[i - 1] = 0;
            for (j = 0; argv[i][j] != 0; j = j + 1) {
                arr[i - 1] = arr[i - 1] * 10 + (argv[i][j] - '0');
            }
        }
    }
    
    for (i = 0; i < n; i = i + 1) {
        for (j = i + 1; j < n; j = j + 1) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    
    return;
}
