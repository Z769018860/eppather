int rewritten_function(int num) {
    int result;
    result = 0;
    if ((num & (1 << 31)) != 0) {
        num = ~num;
    }
    if ((num & 7) == 7) {
        result = result + num;
    }
    int i;
    for (i = 0; i < 32; i = i + 1) {
        if ((num & (1 << i)) != 0) {
            int bitValue;
            bitValue = 1 << i;
            int isPrime;
            isPrime = 1;
            int j;
            for (j = 2; j * j <= bitValue; j = j + 1) {
                if (bitValue % j == 0) {
                    isPrime = 0;
                    break;
                }
            }
            if (isPrime != 0) {
                result = result + bitValue;
            }
        }
    }
    return result;
}
