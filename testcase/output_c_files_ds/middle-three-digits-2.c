void midThree(char arg[50]) {
    char output[4];
    int midPoint;
    int len;
    int i;
    int isNegative;
    int num;
    
    len = 0;
    while (arg[len] != '\0') {
        len = len + 1;
    }
    
    isNegative = 0;
    if (arg[0] == '-') {
        isNegative = 1;
    }
    
    if (isNegative == 1) {
        midPoint = (len + 1) / 2;
    } else {
        midPoint = ((len + 1) / 2) - 1;
    }
    
    num = 0;
    for (i = 0; i < len; i = i + 1) {
        if (arg[i] >= '0' && arg[i] <= '9') {
            num = num * 10 + (arg[i] - '0');
        }
    }
    if (isNegative == 1) {
        num = -num;
    }
    
    if (len < 3) {
        return;
    } else if (len == 3 || len == 4) {
        return;
    } else {
        for (i = 0; i < 3; i = i + 1) {
            output[i] = arg[(midPoint - 1) + i];
        }
        output[3] = '\0';
    }
    return;
}
