int maxProductSubarray(int arr[5], int size) {
    int maxProd;
    int minProd;
    int result;
    int temp;
    int i;

    if (size <= 0) {
        return 0;
    } else {
        maxProd = arr[0];
        minProd = arr[0];
        result = arr[0];
    }

    for (i = 1; i < size; i = i + 1) {
        if (arr[i] < 0) {
            temp = maxProd;
            maxProd = minProd;
            minProd = temp;
        }

        if (arr[i] * maxProd > arr[i]) {
            maxProd = arr[i] * maxProd;
        } else {
            maxProd = arr[i];
        }

        if (arr[i] * minProd < arr[i]) {
            minProd = arr[i] * minProd;
        } else {
            minProd = arr[i];
        }

        if (maxProd > result) {
            result = maxProd;
        }
    }

    return result;
}
