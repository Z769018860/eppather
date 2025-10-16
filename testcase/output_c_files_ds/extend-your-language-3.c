int check_number(char* s) {
    int result = 0;
    int i = 0;
    int negative = 0;
    int length = 0;
    
    if (s[0] == '-') {
        negative = 1;
        i = 1;
    }
    
    for (; s[i] != '\0'; i = i + 1) {
        if (s[i] >= '0' && s[i] <= '9') {
            length = length + 1;
        } else {
            result = 3;
            break;
        }
    }
    
    if (result == 0) {
        if (length == 0) {
            result = 3;
        } else if (length < 3) {
            result = 1;
        } else {
            result = 2;
        }
    }
    
    return result;
}
