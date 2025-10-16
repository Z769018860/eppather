int action_bubble(int size) {
    int tobesorted[1000];
    int i;
    int j;
    int temp;
    for (i = 0; i < size; i = i + 1) {
        for (j = 0; j < size - i - 1; j = j + 1) {
            if (tobesorted[j] > tobesorted[j + 1]) {
                temp = tobesorted[j];
                tobesorted[j] = tobesorted[j + 1];
                tobesorted[j + 1] = temp;
            }
        }
    }
    return 0;
}

int action_shell(int size) {
    int tobesorted[1000];
    int gap;
    int i;
    int j;
    int temp;
    for (gap = size / 2; gap > 0; gap = gap / 2) {
        for (i = gap; i < size; i = i + 1) {
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
    int tobesorted[1000];
    int stack[1000];
    int top = -1;
    int low = 0;
    int high = size - 1;
    int pivot;
    int i;
    int j;
    int temp;
    stack[top = top + 1] = low;
    stack[top = top + 1] = high;
    while (top >= 0) {
        high = stack[top = top - 1];
        low = stack[top = top - 1];
        pivot = tobesorted[high];
        i = low - 1;
        for (j = low; j <= high - 1; j = j + 1) {
            if (tobesorted[j] < pivot) {
                i = i + 1;
                temp = tobesorted[i];
                tobesorted[i] = tobesorted[j];
                tobesorted[j] = temp;
            }
        }
        temp = tobesorted[i + 1];
        tobesorted[i + 1] = tobesorted[high];
        tobesorted[high] = temp;
        pivot = i + 1;
        if (pivot - 1 > low) {
            stack[top = top + 1] = low;
            stack[top = top + 1] = pivot - 1;
        }
        if (pivot + 1 < high) {
            stack[top = top + 1] = pivot + 1;
            stack[top = top + 1] = high;
        }
    }
    return 0;
}

int action_insertion(int size) {
    int tobesorted[1000];
    int i;
    int key;
    int j;
    for (i = 1; i < size; i = i + 1) {
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
    int tobesorted[1000];
    int temp[1000];
    int curr_size;
    int left_start;
    int mid;
    int right_end;
    int i;
    int j;
    int k;
    for (curr_size = 1; curr_size <= size - 1; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < size - 1; left_start = left_start + 2 * curr_size) {
            mid = left_start + curr_size - 1;
            if (mid > size - 1) {
                mid = size - 1;
            }
            right_end = left_start + 2 * curr_size - 1;
            if (right_end > size - 1) {
                right_end = size - 1;
            }
            i = left_start;
            j = mid + 1;
            k = left_start;
            while (i <= mid && j <= right_end) {
                if (tobesorted[i] <= tobesorted[j]) {
                    temp[k] = tobesorted[i];
                    i = i + 1;
                } else {
                    temp[k] = tobesorted[j];
                    j = j + 1;
                }
                k = k + 1;
            }
            while (i <= mid) {
                temp[k] = tobesorted[i];
                k = k + 1;
                i = i + 1;
            }
            while (j <= right_end) {
                temp[k] = tobesorted[j];
                k = k + 1;
                j = j + 1;
            }
            for (i = left_start; i <= right_end; i = i + 1) {
                tobesorted[i] = temp[i];
            }
        }
    }
    return 0;
}

int action_qsort(int size) {
    int tobesorted[1000];
    int i;
    int j;
    int temp;
    for (i = 0; i < size - 1; i = i + 1) {
        for (j = i + 1; j < size; j = j + 1) {
            if (tobesorted[i] > tobesorted[j]) {
                temp = tobesorted[i];
                tobesorted[i] = tobesorted[j];
                tobesorted[j] = temp;
            }
        }
    }
    return 0;
}

int get_the_longest(int *a) {
    int max = a[0];
    int i;
    for (i = 1; i < 1000; i = i + 1) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

return;
