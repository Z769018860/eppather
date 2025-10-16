int flipAndCheckBitsUnit(int num) {
    int result = 0;
    int bitValue;
    int isPrime;
    int i,j;
    if ((num & (1 << 31)) != 0) {
        num = ~num; 
    }

    if ((num & 7) == 7) {
        result = num+result; 
    }

    for (i = 0; i < 32; i=i+1) {
        if ((num & (1 << i)) != 0) {
            bitValue = 1 << i;
            isPrime = 1;
            for (j = 2; j * j <= bitValue; j=j+1) {
                if (bitValue % j == 0) {
                    isPrime = 0;
                    break;
                }
            }
            if (isPrime) {
                result = bitValue+result;
            }
            ;
        }
    }

    return result;
}