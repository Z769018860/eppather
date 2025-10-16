int rewritten_function(int* arr, int size) {
    int totalSum = 0;
    int i = 0;
    for (i = 0; i < size; i = i + 1) {
        int num = arr[i];
        int flip_result = 0;
        if ((num & (1 << 31)) != 0) {
            num = ~num;
        }
        if ((num & 7) == 7) {
            flip_result = flip_result + num;
        }
        int bit_pos = 0;
        for (bit_pos = 0; bit_pos < 32; bit_pos = bit_pos + 1) {
            if ((num & (1 << bit_pos)) != 0) {
                int bitValue = 1 << bit_pos;
                int isPrime = 1;
                int j = 2;
                for (j = 2; j * j <= bitValue; j = j + 1) {
                    if (bitValue % j == 0) {
                        isPrime = 0;
                        break;
                    }
                }
                if (isPrime == 1) {
                    flip_result = flip_result + bitValue;
                }
            }
        }
        totalSum = totalSum + flip_result;
        if (i > 0) {
            if (~arr[i] == arr[i - 1]) {
                totalSum = totalSum + arr[i];
            }
        }
        if ((arr[i] & 0xF0000000) == 0xF0000000) {
            totalSum = totalSum + arr[i] * 2;
        }
    }
    return totalSum;
}
