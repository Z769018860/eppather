int luhn(int cc_len, const char* cc) {
    int m[10] = {0,2,4,6,8,1,3,5,7,9};
    int odd = 1;
    int sum = 0;
    int i;
    int digit;
    
    for (i = cc_len; i > 0; i = i - 1) {
        digit = cc[i - 1] - 48;
        if (odd) {
            sum = sum + digit;
        } else {
            sum = sum + m[digit];
        }
        odd = !odd;
    }
    
    if (sum % 10 == 0) {
        return 1;
    } else {
        return 0;
    }
    return;
}
