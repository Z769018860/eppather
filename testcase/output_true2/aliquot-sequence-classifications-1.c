int bruteForceProperDivisorSum(int n){
    int sum[5];
    int i;
    sum[0] = 0;
    for(i = 1; i < (n + 1) / 2; i = i + 1){
        if(n % i == 0 && n != i){
            sum[0] = sum[0] + i;
        }
    }
    return sum[0];
}

void aliquotClassifier(int n){
    int arr[16];
    int i;
    int j;
    arr[0] = n;
    for(i = 1; i < 5; i = i + 1){
        arr[i] = bruteForceProperDivisorSum(arr[i - 1]);
        if(arr[i] == 0 || arr[i] == n || (arr[i] == arr[i - 1] && arr[i] != n)){
            return;
        }
        for(j = 1; j < i; j = j + 1){
            if(arr[j] == arr[i]){
                return;
            }
        }
    }
    return;
}
