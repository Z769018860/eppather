void mergeSort(int arr[], int l, int r) {
    int m;
    int i;
    int j;
    int k;
    int n1;
    int n2;
    int L[5];
    int R[5];
    if (l < r) {
        m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        n1 = m - l + 1;
        n2 = r - m;
        for (i = 0; i < n1; i = i + 1) {
            L[i] = arr[l + i];
        }
        for (j = 0; j < n2; j = j + 1) {
            R[j] = arr[m + 1 + j];
        }
        i = 0;
        j = 0;
        k = l;
        for (; (i < n1) && (j < n2); ) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i = i + 1;
            } else {
                arr[k] = R[j];
                j = j + 1;
            }
            k = k + 1;
        }
        for (; i < n1; ) {
            arr[k] = L[i];
            i = i + 1;
            k = k + 1;
        }
        for (; j < n2; ) {
            arr[k] = R[j];
            j = j + 1;
            k = k + 1;
        }
    }
    return;
}
