int func() {
    int arg[5] = {1, 2, 3, 4, 5};
    int arg_length = 5;
    int sum = 0;
    int prod = 1;
    int *p;
    int *end = arg + arg_length;
    
    for (p = arg; p != end; p = p + 1) {
        sum = sum + *p;
        prod = prod * *p;
    }
    
    return;
}
