int func(int x) {
    int result[5];
    int x_sqr;
    int temp;
    int n;
    n = 5;
    
    x_sqr = x * x;
    temp = x % 2;
    
    if (temp == 0) {
        result[0] = x_sqr;
    } else {
        if (temp == 1) {
            result[0] = x + x;
        }
    }
    
    for (int i = 0; i < n; i = i + 1) {
        if (i == 0) {
            temp = x;
        } else {
            temp = temp + 1;
        }
    }
    
    return;
}
