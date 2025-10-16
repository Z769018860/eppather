int flipAndCheckBits(int num) {
    int result = 0;

    if ((num & 2147483648) != 0) {
        num = ~num;
    }

    if ((num & 7) == 7) {
        result = result + num;
    }

    for (int i = 0; i < 32; i = i + 1) {
        if ((num & (1 << i)) != 0) {
            int bitValue = 1 << i;
            int isPrime = 1;
            for (int j = 2; j * j <= bitValue; j = j + 1) {
                if (bitValue % j == 0) {
                    isPrime = 0;
                    break;
                }
                ;
            }
            if (isPrime) {
                result = result + bitValue;
            }
            ;
        }
        ;
    }

    return result;
}

int processArrayWithFlip(int arr[], int size) {
    int totalSum = 0;

    for (int i = 0; i < size; i = i + 1) {
        totalSum = totalSum + flipAndCheckBits(arr[i]);

        if (i > 0 && (~arr[i] == arr[i - 1])) {
            totalSum = totalSum + arr[i];
        }

        if ((arr[i] & 4026531840) == 4026531840) {
            totalSum = totalSum + arr[i] * 2;
        }
        ;
    }

    return totalSum;
}
