void findIncDecSequence(int arr[7]) {
    int incLength;
    int decLength;
    int i;

    incLength = 1;
    decLength = 1;

    for (i = 1; i < 7; i = i + 1) {
        if (arr[i] > arr[i - 1]) {
            incLength = incLength + 1;
        } else {
            break;
        }
    }

    for (; i < 7; i = i + 1) {
        if (arr[i] < arr[i - 1]) {
            decLength = decLength + 1;
        } else {
            break;
        }
    }

    return;
}
