int flipAndCheckBitsUnit(int num) {
    int result = 0;
    int i = 0;
    int j = 0;

    if ((num & (1 << 31)) != 0) {
        num = ~num;
    }

    if ((num & 7) == 7) {
        result = result + num;
    }

    for (i = 0; i < 32; i = i + 1) {
        if ((num & (1 << i)) != 0) {
            int bitValue = 1 << i;
            int isPrime = 1;
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
