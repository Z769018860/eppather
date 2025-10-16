int raiseTo(int base, int power) {
    int result[5];
    result[0] = 1;
    int i;
    for (i = 0; i < power; i = i + 1) {
        result[0] = result[0] * base;
    }
    return result[0];
}

int properDivisorSum(int n) {
    int prod[5];
    prod[0] = 1;
    int temp[5];
    temp[0] = n;
    int count[5];
    count[0] = 0;
    int i;

    while (n % 2 == 0) {
        count[0] = count[0] + 1;
        n = n / 2;
    }

    if (count[0] != 0) {
        prod[0] = prod[0] * (raiseTo(2, count[0] + 1) - 1);
    }

    for (i = 3; i * i <= n; i = i + 2) {
        count[0] = 0;
        while (n % i == 0) {
            count[0] = count[0] + 1;
            n = n / i;
        }
        if (count[0] == 1) {
            prod[0] = prod[0] * (i + 1);
        } else {
            if (count[0] > 1) {
                prod[0] = prod[0] * ((raiseTo(i, count[0] + 1) - 1) / (i - 1));
            }
        }
    }

    if (n > 2) {
        prod[0] = prod[0] * (n + 1);
    }

    return prod[0] - temp[0];
}

void aliquotClassifier(int n) {
    int arr[16];
    int i;
    int j;
    arr[0] = n;

    for (i = 1; i < 16; i = i + 1) {
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
