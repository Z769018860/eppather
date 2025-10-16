int parse_number() {
    int num;
    int i;
    int len;
    int base;
    int digit;
    int result;
    char str[8] = {'0','1','2','3','4','5','9','\0'};
    
    result = 0;
    base = 10;
    len = 7;
    for (i = 0; i < len; i = i + 1) {
        digit = str[i] - '0';
        if (digit >= 0 && digit < base) {
            result = result * base + digit;
        }
    }
    num = result;
    
    result = 0;
    base = 16;
    len = 7;
    for (i = 0; i < len; i = i + 1) {
        if (str[i] >= '0' && str[i] <= '9') {
            digit = str[i] - '0';
        } else if (str[i] >= 'a' && str[i] <= 'f') {
            digit = str[i] - 'a' + 10;
        } else if (str[i] >= 'A' && str[i] <= 'F') {
            digit = str[i] - 'A' + 10;
        } else {
            digit = 0;
        }
        if (digit >= 0 && digit < base) {
            result = result * base + digit;
        }
    }
    num = result;
    
    result = 0;
    base = 8;
    len = 4;
    for (i = 0; i < len; i = i + 1) {
        digit = str[i] - '0';
        if (digit >= 0 && digit < base) {
            result = result * base + digit;
        }
    }
    num = result;
    
    return;
}
