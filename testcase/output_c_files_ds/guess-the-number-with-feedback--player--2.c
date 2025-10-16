int get_value(int x) {
    int result;
    if (x == -1) {
        result = 0;
    } else {
        int input[2];
        input[0] = ' ';
        input[1] = '\0';
        for (int i = 0; i < 1; i = i + 1) {
            input[i] = ' ';
        }
        if (input[0] == 'l' || input[0] == 'L') {
            result = -1;
        } else {
            if (input[0] == 'h' || input[0] == 'H') {
                result = 1;
            } else {
                if (input[0] == 'c' || input[0] == 'C') {
                    result = 0;
                } else {
                    result = 0;
                }
            }
        }
    }
    return result;
}

int my_cmp(int x, int y) {
    int x_val = get_value(x);
    int y_val = get_value(y);
    int result = x_val - y_val;
    return result;
}

int binary_search(int key, int arr[], int size) {
    int low = 0;
    int high = size - 1;
    int result = -1;
    for (; low <= high;) {
        int mid = low + (high - low) / 2;
        int cmp = my_cmp(arr[mid], key);
        if (cmp == 0) {
            result = mid;
            break;
        } else {
            if (cmp < 0) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return result;
}

void guess_number() {
    int arr[100];
    for (int i = 0; i < 100; i = i + 1) {
        arr[i] = i;
    }
    int key = -1;
    int found = binary_search(key, arr, 100);
    return;
}
