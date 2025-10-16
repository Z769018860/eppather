int mergedFunction(int arr[5], int size) {
    int totalSum;
    int i;
    int j;
    int k;
    int num;
    int result;
    int bitValue;
    int isPrime;
    totalSum = 0;
    
    for (i = 0; i < size; i = i + 1) {
        num = arr[i];
        result = 0;
        
        if ((num & (1 << 31)) != 0) {
            num = ~num;
        }
        
        if ((num & 7) == 7) {
            result = result + num;
        }
        
        for (j = 0; j < 32; j = j + 1) {
            if ((num & (1 << j)) != 0) {
                bitValue = 1 << j;
                isPrime = 1;
                
                for (k = 2; k * k <= bitValue; k = k + 1) {
                    if (bitValue % k == 0) {
                        isPrime = 0;
                        break;
                    }
                }
                
                if (isPrime != 0) {
                    result = result + bitValue;
                }
            }
        }
        
        totalSum = totalSum + result;
        
        if (i > 0) {
            if ((~arr[i]) == arr[i - 1]) {
                totalSum = totalSum + arr[i];
            }
        }
        
        if ((arr[i] & 0xF0000000) == 0xF0000000) {
            totalSum = totalSum + arr[i] * 2;
        }
    }
    
    return totalSum;
}
