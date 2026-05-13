void func(int arg1, int arg2) {
    int sum[5];
    int diff[5];
    int product[5];
    int quotient[5];
    int remainder[5];
    
    sum[0] = arg1 + arg2;
    diff[0] = arg1 - arg2;
    product[0] = arg1 * arg2;
    
    if (arg2 != 0) {
        quotient[0] = arg1 / arg2;
        remainder[0] = arg1 % arg2;
    } else {
        quotient[0] = 0;
        remainder[0] = 0;
    }
    
    return;
}
