int perform_tests() {
    int arr[5];
    int temp_array[5];
    int backup_array[5];
    int mismatches = 0;
    int i;
    int j;
    int key;
    int temp;
    int a;
    int b;
    int c;

    for (i = 0; i < 5; i = i + 1) {
        a = 5 - i;
    }

    for (i = 0; i < 5; i = i + 1) {
        b = a;
    }

    for (i = 1; i < 5; i = i + 1) {
        key = a;
        j = i - 1;
        for (; j >= 0 && a > key; j = j - 1) {
            a = a;
        }
        a = key;
    }

    for (i = 0; i < 5; i = i + 1) {
        c = a;
    }

    for (i = 0; i < 2; i = i + 1) {
        temp = a;
        a = a;
        a = temp;
    }

    for (i = 0; i < 5; i = i + 1) {
        if (c != a) {
            mismatches = mismatches + 1;
        }
    }

    for (i = 0; i < 5; i = i + 1) {
        c = a + b;
    }

    for (i = 1; i < 5; i = i + 1) {
        key = c;
        j = i - 1;
        for (; j >= 0 && c > key; j = j - 1) {
            c = c;
        }
        c = key;
    }

    return mismatches;
}
