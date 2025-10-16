int properDivisorSum(int n) {
    int prod = 1;
    int temp = n;
    int count = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int result = 1;

    while (n % 2 == 0) {
        count = count + 1;
        n = n / 2;
    }

    if (count != 0) {
        for (i = 0; i < count + 1; i = i + 1) {
            result = result * 2;
        }
        prod = prod * (result - 1);
    }

    for (i = 3; i * i <= n; i = i + 2) {
        count = 0;
        while (n % i == 0) {
            count = count + 1;
            n = n / i;
        }
        if (count == 1) {
            prod = prod * (i + 1);
        } else if (count > 1) {
            result = 1;
            for (j = 0; j < count + 1; j = j + 1) {
                result = result * i;
            }
            prod = prod * ((result - 1) / (i - 1));
        }
    }

    if (n > 2) {
        prod = prod * (n + 1);
    }

    return prod - temp;
}

void aliquotClassifier(int n) {
    int arr[5];
    int i = 0;
    int j = 0;
    int k = 0;
    int temp = 0;

    arr[0] = n;

    for (i = 1; i < 5; i = i + 1) {
        arr[i] = properDivisorSum(arr[i - 1]);

        if (arr[i] == 0 || arr[i] == n || (arr[i] == arr[i - 1] && arr[i] != n)) {
            return;
        }

        for (j = 1; j < i; j = j + 1) {
            if (arr[j] == arr[i]) {
                return;
            }
        }
    }

    return;
}
