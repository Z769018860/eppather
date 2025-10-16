int action_bubble(int size) {
    int tobesorted[5];
    int i;
    int j;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5 - i - 1; j = j + 1) {
            if (tobesorted[j] > tobesorted[j + 1]) {
                int temp = tobesorted[j];
                tobesorted[j] = tobesorted[j + 1];
                tobesorted[j + 1] = temp;
            }
        }
    }
    return 0;
}

int action_shell(int size) {
    int tobesorted[5];
    int gap;
    int i;
    int j;
    int temp;
    for (gap = 5 / 2; gap > 0; gap = gap / 2) {
        for (i = gap; i < 5; i = i + 1) {
            temp = tobesorted[i];
            for (j = i; j >= gap && tobesorted[j - gap] > temp; j = j - gap) {
                tobesorted[j] = tobesorted[j - gap];
            }
            tobesorted[j] = temp;
        }
    }
    return 0;
}

int action_quick(int size) {
    int tobesorted[5];
    int partition(int arr[5], int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        int j;
        for (j = low; j <= high - 1; j = j + 1) {
            if (arr[j] < pivot) {
                i = i + 1;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        return i + 1;
    }
    void quickSort(int arr[5], int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    quickSort(tobesorted, 0, 5 - 1);
    return 0;
}

int action_insertion(int size) {
    int tobesorted[5];
    int i;
    int key;
    int j;
    for (i = 1; i < 5; i = i + 1) {
        key = tobesorted[i];
        j = i - 1;
        while (j >= 0 && tobesorted[j] > key) {
            tobesorted[j + 1] = tobesorted[j];
            j = j - 1;
        }
        tobesorted[j + 1] = key;
    }
    return 0;
}

int action_merge(int size) {
    int tobesorted[5];
    void merge(int arr[5], int l, int m, int r) {
        int i;
        int j;
        int k;
        int n1 = m - l + 1;
        int n2 = r - m;
        int L[5];
        int R[5];
        for (i = 0; i < n1; i = i + 1) {
            L[i] = arr[l + i];
        }
        for (j = 0; j < n2; j = j + 1) {
            R[j] = arr[m + 1 + j];
        }
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
    void mergeSort(int arr[5], int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }
    mergeSort(tobesorted, 0, 5 - 1);
    return 0;
}

int doublecompare(const void *a, const void *b) {
    int x[5];
    int y[5];
    if (x[0] < y[0]) {
        return -1;
    }
    if (x[0] > y[0]) {
        return 1;
    }
    return 0;
}

int action_qsort(int size) {
    int tobesorted[5];
    qsort(tobesorted, 5, sizeof(int), doublecompare);
    return 0;
}

int get_the_longest(int *a) {
    int max_len = 0;
    int current_len = 0;
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (a[i] != 0) {
            current_len = current_len + 1;
            if (current_len > max_len) {
                max_len = current_len;
            }
        } else {
            current_len = 0;
        }
    }
    return max_len;
}

return;
