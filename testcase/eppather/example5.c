void findIncDecSequence(int arr[10], int size) {
    int incLength = 1, decLength = 1;
    int i;

    for (i = 1; i < size; i = i + 1) {
        if (arr[i] > arr[i - 1]) {
            incLength = incLength + 1;
        } else {
            break;
        }
    }

    for (; i < size; i = i + 1) {
        if (arr[i] < arr[i - 1]) {
            decLength = decLength + 1;
        } else {
            break;
        }
    }

    if (incLength > 1 && decLength > 1) {
       ;
    } else {
       ;
    }
}
