long int sumOfFactorials(int num, int arg1, int arg2, int arg3, int arg4, int arg5) {
    long int sum = 0;
    int args[5] = {arg1, arg2, arg3, arg4, arg5};
    
    for (int i = 0; i < num; i = i + 1) {
        long int fact = 1;
        int n = args[i];
        for (int j = 1; j <= n; j = j + 1) {
            fact = fact * j;
        }
        sum = sum + fact;
    }
    
    return sum;
}
