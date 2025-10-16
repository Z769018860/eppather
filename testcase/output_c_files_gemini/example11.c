int complexArrayUnitFunction(int* arr, int size) {
    int result;
    int sumPositive;
    int sumNegative;
    int i;

    result = 0;
    sumPositive = 0;
    sumNegative = 0;

    for (i = 0; i < size; i = i + 1) {
        if (arr[i] > 0) {
            sumPositive = sumPositive + arr[i];
            if (arr[i] % 2 == 0) {
                result = result + arr[i] * 2;
            }
            if (i > 0 && arr[i] > arr[i - 1]) {
                result = result + (arr[i] - arr[i - 1]);
            }
        } else {
            if (arr[i] < 0) {
                sumNegative = sumNegative + arr[i];
                if (arr[i] % 2 != 0) {
                    result = result + arr[i] * 3;
                }
                if (i < size - 1 && arr[i] < arr[i + 1]) {
                    result = result - arr[i];
                }
            }
        }
        if (i > 0 && i < size - 1 && arr[i] > arr[i - 1] + arr[i + 1]) {
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
