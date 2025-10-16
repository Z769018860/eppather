int func() {
    int i;
    int j;
    int n;
    int arr[13][13];
    n = 12;
    
    for (j = 1; j <= n; j = j + 1) {
        arr[0][j] = j;
    }
    
    for (i = 1; i <= n; i = i + 1) {
        for (j = 1; j <= n; j = j + 1) {
            if (j < i) {
                arr[i][j] = 0;
            } else {
                arr[i][j] = i * j;
            }
        }
    }
    
    return;
}
