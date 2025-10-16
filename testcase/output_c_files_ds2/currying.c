long int sumOfFactorials(int num, int arg1, int arg2, int arg3, int arg4, int arg5) {
    long int sum[5];
    sum[0] = 0;
    int args[5];
    args[0] = arg1;
    args[1] = arg2;
    args[2] = arg3;
    args[3] = arg4;
    args[4] = arg5;
    
    for (int i = 0; i < num; i = i + 1) {
        long int fact[5];
        fact[0] = 1;
        for (int j = 1; j <= args[i]; j = j + 1) {
            fact[0] = fact[0] * j;
        }
        sum[0] = sum[0] + fact[0];
    }
    
    return sum[0];
}
