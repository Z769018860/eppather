int complexArrayOperation(int arr[5], int size) {
    int result = 0;
    int sumPositive = 0;
    int sumNegative = 0;
    int i = 0;

    for (i = 0; i < size; i = i + 1) {
        if (arr[i] > 0) {
            sumPositive = sumPositive + arr[i];
            if (arr[i] % 2 == 0) {
                result = result + arr[i] * 2;
            }
            if (i > 0 && arr[i] > arr[i - 1]) {
                result = result + (arr[i] - arr[i - 1]);
            }
        } else if (arr[i] < 0) {
            sumNegative = sumNegative + arr[i];
            if (arr[i] % 2 != 0) {
                result = result + arr[i] * 3;
            }
            if (i < size - 1 && arr[i] < arr[i + 1]) {
                result = result - arr[i];
            }
        }
        if (i > 0 && i < size - 1 && arr[i] > (arr[i - 1] + arr[i + 1])) {
            result = result + arr[i] * 5;
        }
    }

    if (sumPositive > -sumNegative) {
        result = result + sumPositive;
    } else {
        result = result + sumNegative;
    }

    return result;
}
