int func(int k) {
    int f1 = 1;
    int fn1 = -1;
    int f0 = 0;
    int result = 0;
    
    for (;;) {
        if (k <= 0) {
            result = f1 + f0;
            break;
        }
        else {
            k = k - 1;
            continue;
        }
    }
    
    return result;
}
