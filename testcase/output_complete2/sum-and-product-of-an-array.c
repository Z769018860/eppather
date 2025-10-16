int func(int arg_length) {
    int arg[5];
    arg[0] = 1;
    arg[1] = 2;
    arg[2] = 3;
    arg[3] = 4;
    arg[4] = 5;
    int sum[5];
    sum[0] = 0;
    int prod[5];
    prod[0] = 1;
    int p;
    
    for (p = 0; p < arg_length; p = p + 1) {
        sum[0] = sum[0] + arg[p];
        prod[0] = prod[0] * arg[p];
    }
    
    return;
}
