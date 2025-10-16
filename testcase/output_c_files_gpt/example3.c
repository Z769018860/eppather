int maxProductSubarray(int arr[5]) {
    int size = 5;
    int maxProd = arr[0];
    int minProd = arr[0];
    int result = arr[0];
    int temp;
    int i = 1;

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
