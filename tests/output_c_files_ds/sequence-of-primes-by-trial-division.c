int isPrime(int n) {
    int num;
    
    if (n < 2 || (n & 1) == 0) {
        if (n == 2) {
            return 1;
        }
        else {
            return 0;
        }
    }
    
    for (num = 3; num <= n / num; num = num + 2) {
        if ((n % num) == 0) {
            return 0;
        }
    }
    
    return 1;
}

return;
