unsigned long long aliquotClassifier(unsigned long long n){
    unsigned long long arr[16];
    int i;
    int j;
    unsigned long long sum;
    
    arr[0] = n;
    
    for (i = 1; i < 16; i = i + 1) {
        sum = 0;
        for (unsigned long long k = 1; k < (arr[i - 1] + 1) / 2; k = k + 1) {
            if (arr[i - 1] % k == 0 && arr[i - 1] != k) {
                sum = sum + k;
            }
        }
        arr[i] = sum;
        
        if (arr[i] == 0 || arr[i] == n || (arr[i] == arr[i - 1] && arr[i] != n)) {
            return arr[i];
        }
        
        for (j = 1; j < i; j = j + 1) {
            if (arr[j] == arr[i]) {
                return arr[i];
            }
        }
    }
    
    return arr[15];
}
