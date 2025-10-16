int func(int argC, char* argV[]) {
    int arr[100];
    int min;
    int max;
    int i;
    int len;
    int j;
    int temp;
    int is_comma;
    int num;
    int sign;
    int digit;
    
    if (argC > 1) {
        for (i = 1; i < argC; i = i + 1) {
            len = 0;
            while (argV[i][len] != '\0') {
                len = len + 1;
            }
            
            is_comma = 0;
            if (argV[i][len - 1] == ',') {
                is_comma = 1;
                len = len - 1;
            }
            
            num = 0;
            sign = 1;
            j = 0;
            if (argV[i][0] == '-') {
                sign = -1;
                j = j + 1;
            }
            
            for (; j < len; j = j + 1) {
                digit = argV[i][j] - '0';
                num = num * 10 + digit;
            }
            num = num * sign;
            
            arr[i - 1] = num;
            
            if (i == 1) {
                min = arr[i - 1];
                max = arr[i - 1];
            }
            else {
                if (min < arr[i - 1]) {
                    temp = min;
                }
                else {
                    temp = arr[i - 1];
                }
                min = temp;
                
                if (max > arr[i - 1]) {
                    temp = max;
                }
                else {
                    temp = arr[i - 1];
                }
                max = temp;
            }
        }
    }
    
    return;
}
