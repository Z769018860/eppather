void findIncDecSequence() {
    int arr[7];
    int size = 7;
    int incLength = 1;
    int decLength = 1;
    int i;

    for (i = 1; i < size; i = i + 1) {
        if (arr[i] > arr[i - 1]) {
            incLength = incLength + 1;
        } else {
            break;
        }
    }

    for (i = i + 1; i < size; i = i + 1) {
        if (arr[i] < arr[i - 1]) {
            decLength = decLength + 1;
        } else {
            break;
        }
    }

    return;
}
