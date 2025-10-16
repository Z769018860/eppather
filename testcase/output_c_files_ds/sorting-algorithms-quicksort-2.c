void quicksort(int A[100], int p, int q) {
    if (p < q) {
        int temp = A[q];
        int pivotIndx = p - 1;
        for (int j = p; j <= q; j = j + 1) {
            if (A[j] <= temp) {
                pivotIndx = pivotIndx + 1;
                int c = A[pivotIndx];
                A[pivotIndx] = A[j];
                A[j] = c;
            }
        }
        if (p < pivotIndx - 1) {
            quicksort(A, p, pivotIndx - 1);
        }
        if (pivotIndx + 1 < q) {
            quicksort(A, pivotIndx + 1, q);
        }
    }
    return;
}
