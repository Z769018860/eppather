int kaprekar(int n, int base) {
    int nn = n * n;
    int r;
    int tens = 1;
    
    if ((nn - n) % (base - 1) != 0) {
        return 0;
    }
    
    for (; tens < n; tens = tens * base) {
    }
    
    if (n == tens) {
        if (1 == n) {
            return 1;
        } else {
            return 0;
        }
    }
    
    for (; ; tens = tens * base) {
        r = nn % tens;
        if (r >= n) {
            break;
        }
        if (nn / tens + r == n) {
            return tens;
        }
    }
    
    return 0;
}
