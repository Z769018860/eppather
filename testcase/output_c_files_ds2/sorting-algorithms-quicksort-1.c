void quicksort(int A[10], int len) {
    if (len < 2) {
        return;
    }

    int pivot = A[len / 2];
    int i = 0;
    int j = len - 1;
    int temp;

    for (; ; i = i + 1, j = j - 1) {
        for (; A[i] < pivot; i = i + 1) {
        }
        for (; A[j] > pivot; j = j - 1) {
        }

        if (i >= j) {
            break;
        }

        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    quicksort(A, i);
    quicksort(A + i, len - i);
    return;
}
