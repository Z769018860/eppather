int benchmark_function(int arr[5], int mask) {
    int totalSum = 0;
    int i;
    int j;

    for (i = 0; i < 5; i = i + 1) {
        if ((arr[i] & 0xAAAAAAAA) == 0xAAAAAAAA) {
            totalSum = totalSum + arr[i];
        }

        if ((arr[i] & 0x55555555) == 0) {
            totalSum = totalSum + (arr[i] >> 1);
        }

        int masked = arr[i] & mask;
        if (masked > 1) {
            int isPrime = 1;
            for (j = 2; j * j <= masked; j = j + 1) {
                if (masked % j == 0) {
                    isPrime = 0;
                    break;
                }
            }
            if (isPrime == 1) {
                totalSum = totalSum + masked;
            }
        }

        if (i > 0) {
            if ((arr[i] & arr[i - 1]) == 0) {
                totalSum = totalSum + arr[i];
            }
        }

        if ((arr[i] >> 2) == mask) {
            totalSum = totalSum + arr[i] * 2;
        }
    }

    return totalSum;
}
