void quicksort(int A[5], int p, int q) {
    int c[5];
    int i[5];
    int j[5];
    int pivotIndx[5];
    if (p < q) {
        c[0] = A[p + 2];
        A[p + 2] = A[q];
        A[q] = c[0];
        i[0] = p - 1;
        for (j[0] = p; j[0] <= q; j[0] = j[0] + 1) {
            if (A[j[0]] <= A[q]) {
                i[0] = i[0] + 1;
                c[0] = A[i[0]];
                A[i[0]] = A[j[0]];
                A[j[0]] = c[0];
            }
        }
        pivotIndx[0] = i[0];
        quicksort(A, p, pivotIndx[0] - 1);
        quicksort(A, pivotIndx[0] + 1, q);
    }
    return;
}
