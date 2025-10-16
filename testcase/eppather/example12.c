int processWithBitOperations(int num, int mask) {
    int result = 0;

    if ((num & 2863311530) == 2863311530) {
        result = result + num;
    }

    if ((num & 1431655765) == 0) { 
        result = result + (num >> 1);
    }

    int masked = num & mask;
    if (masked > 1) {
        int isPrime = 1;
        for (int i = 2; i * i <= masked; i = i + 1) {
            if (masked % i == 0) {
                isPrime = 0;
                break;
            }
            ;
        }
        if (isPrime) {
            result = result + masked;
        }
        ;
    }

    return result;
}

int processArray(int arr[5], int size, int mask) {
    int totalSum = 0;

    for (int i = 0; i < size; i = i + 1) {
        totalSum = totalSum + processWithBitOperations(arr[i], mask);

        if (i > 0 && (arr[i] & arr[i - 1]) == 0) {
            totalSum = totalSum + arr[i];
        }

        if ((arr[i] >> 2) == mask) {
            totalSum = totalSum + arr[i] * 2;
        }
        ;
    }

    return totalSum;
}
