int processArrayAndBitOperations(int arr[5], int mask) {
    int totalSum = 0;
    int i = 0;
    for (i = 0; i < 5; i = i + 1) {
        int num = arr[i];
        int result = 0;

        if ((num & 0xAAAAAAAA) == 0xAAAAAAAA) {
            result = result + num;
        }

        if ((num & 0x55555555) == 0) {
            result = result + (num >> 1);
        }

        int masked = num & mask;
        if (masked > 1) {
            int isPrime = 1;
            int j = 2;
            for (j = 2; j * j <= masked; j = j + 1) {
                if (masked % j == 0) {
                    isPrime = 0;
                    break;
                }
            }
            if (isPrime == 1) {
                result = result + masked;
            }
        }

        totalSum = totalSum + result;

        if (i > 0 && (arr[i] & arr[i - 1]) == 0) {
            totalSum = totalSum + arr[i];
        }

        if ((arr[i] >> 2) == mask) {
            totalSum = totalSum + (arr[i] * 2);
        }
    }
    return totalSum;
}
