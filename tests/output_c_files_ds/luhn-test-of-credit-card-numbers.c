int luhn(const char* cc)
{
    int m[10] = {0,2,4,6,8,1,3,5,7,9};
    int i;
    int odd = 1;
    int sum = 0;
    int len = 0;
    
    for (i = 0; cc[i] != '\0'; i = i + 1) {
        len = len + 1;
    }
    
    for (i = len - 1; i >= 0; i = i - 1) {
        int digit = cc[i] - '0';
        if (odd) {
            sum = sum + digit;
        } else {
            sum = sum + m[digit];
        }
        if (odd) {
            odd = 0;
        } else {
            odd = 1;
        }
    }
    
    if (sum % 10 == 0) {
        return 1;
    } else {
        return 0;
    }
    return;
}
