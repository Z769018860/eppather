int raiseTo(int base, int power) {
    int result = 1;
    int i;
    for (i = 0; i < power; i = i + 1) {
        result = result * base;
    }
    return result;
}

int properDivisorSum(int n) {
    int prod = 1;
    int temp = n;
    int count = 0;
    int i;
    
    while (n % 2 == 0) {
        count = count + 1;
        n = n / 2;
    }
    
    if (count != 0) {
        prod = prod * (raiseTo(2, count + 1) - 1);
    }
    
    for (i = 3; i * i <= n; i = i + 2) {
        count = 0;
        
        while (n % i == 0) {
            count = count + 1;
            n = n / i;
        }
        
        if (count == 1) {
            prod = prod * (i + 1);
        } else {
            if (count > 1) {
                prod = prod * ((raiseTo(i, count + 1) - 1) / (i - 1));
            }
        }
    }
    
    if (n > 2) {
        prod = prod * (n + 1);
    }
    
    return prod - temp;
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
