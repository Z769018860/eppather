void merged_function(int a, int b, double d, double vInit, char strInit[32]) {
    int sily[5];
    int c[5];
    int s[5];
    int str_length = 0;
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        sily[i] = 0;
        c[i] = 0;
        s[i] = 0;
    }
    
    sily[0] = (int)(vInit * 1000000);
    for (i = 0; i < 31; i = i + 1) {
        if (strInit[i] != 0) {
            str_length = str_length + 1;
        } else {
            break;
        }
    }
    
    int result1 = a + str_length;
    
    char temp_str[32];
    int num = b;
    int digits = 0;
    if (num == 0) {
        digits = 1;
    } else {
        while (num != 0) {
            num = num / 10;
            digits = digits + 1;
        }
    }
    
    num = b;
    for (i = digits - 1; i >= 0; i = i - 1) {
        temp_str[i] = (num % 10) + '0';
        num = num / 10;
    }
    temp_str[digits] = 0;
    
    double result3 = (sily[0] / 1000000.0) * d;
    
    return;
}
