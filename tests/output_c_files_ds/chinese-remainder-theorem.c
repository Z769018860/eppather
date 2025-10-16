int chinese_remainder(int n[3], int a[3], int len) {
    int p;
    int i;
    int prod;
    int sum;
    int b0;
    int t;
    int q;
    int x0;
    int x1;
    int inv;
    
    prod = 1;
    for (i = 0; i < len; i = i + 1) {
        prod = prod * n[i];
    }
    
    sum = 0;
    for (i = 0; i < len; i = i + 1) {
        p = prod / n[i];
        
        b0 = n[i];
        x0 = 0;
        x1 = 1;
        if (b0 == 1) {
            inv = 1;
        } else {
            a = p;
            b = n[i];
            while (a > 1) {
                q = a / b;
                t = b;
                b = a % b;
                a = t;
                t = x0;
                x0 = x1 - q * x0;
                x1 = t;
            }
            if (x1 < 0) {
                x1 = x1 + b0;
            }
            inv = x1;
        }
        
        sum = sum + a[i] * inv * p;
    }
    
    return sum % prod;
}
