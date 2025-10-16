void mergeSortAndMerge(int arr[5], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;
        int L[5], R[5];

        for (i = 0; i < n1; i = i + 1) {
            L[i] = arr[l + i];
        }
        for (j = 0; j < n2; j = j + 1) {
            R[j] = arr[m + 1 + j];
        }

        mergeSortAndMerge(arr, l, m);
        mergeSortAndMerge(arr, m + 1, r);

        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i = i + 1;
            } else {
                arr[k] = R[j];
                j = j + 1;
            }
            k = k + 1;
        }

        while (i < n1) {
            arr[k] = L[i];
            i = i + 1;
            k = k + 1;
        }

        while (j < n2) {
            arr[k] = R[j];
            j = j + 1;
            k = k + 1;
        }
    }
    return;
}
