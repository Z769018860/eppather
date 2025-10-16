int func() {
    int num;
    int result;
    char str1[7] = {'1','2','3','4','5','9','\0'};
    char str2[9] = {'0','x','a','b','c','f','1','2','3'};
    char str3[6] = {'0','7','6','5','1','\0'};
    int i;
    int len;
    int base;
    int digit;
    int is_hex;
    
    num = 0;
    len = 6;
    base = 10;
    is_hex = 0;
    for (i = 0; i < len; i = i + 1) {
        if (str1[i] >= '0' && str1[i] <= '9') {
            digit = str1[i] - '0';
        } else {
            digit = 0;
        }
        num = num * base + digit;
    }
    result = num;
    
    num = 0;
    len = 9;
    base = 16;
    is_hex = 1;
    for (i = 2; i < len; i = i + 1) {
        if (str2[i] >= '0' && str2[i] <= '9') {
            digit = str2[i] - '0';
        } else if (str2[i] >= 'a' && str2[i] <= 'f') {
            digit = str2[i] - 'a' + 10;
        } else {
            digit = 0;
        }
        num = num * base + digit;
    }
    result = num;
    
    num = 0;
    len = 5;
    base = 8;
    is_hex = 0;
    for (i = 1; i < len; i = i + 1) {
        if (str3[i] >= '0' && str3[i] <= '7') {
            digit = str3[i] - '0';
        } else {
            digit = 0;
        }
        num = num * base + digit;
    }
    result = num;
    
    return;
}
