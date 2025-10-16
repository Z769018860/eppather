int sort_strings(int arr[7][100]) {
    int i;
    int j;
    int temp[100];
    for (i = 0; i < 7; i = i + 1) {
        for (j = i + 1; j < 7; j = j + 1) {
            int k;
            int cmp;
            cmp = 0;
            for (k = 0; k < 100; k = k + 1) {
                if (arr[i][k] != arr[j][k]) {
                    cmp = arr[i][k] - arr[j][k];
                    break;
                }
            }
            if (cmp > 0) {
                for (k = 0; k < 100; k = k + 1) {
                    temp[k] = arr[i][k];
                }
                for (k = 0; k < 100; k = k + 1) {
                    arr[i][k] = arr[j][k];
                }
                for (k = 0; k < 100; k = k + 1) {
                    arr[j][k] = temp[k];
                }
            }
        }
    }
    return;
}
