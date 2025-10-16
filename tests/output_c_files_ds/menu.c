const char* menu_select(const char* const* items, const char* prompt) {
    int i;
    int choice;
    int choice_max;
    int valid;
    char buf[1024];
    int j;
    int num;
    int sign;
    int digit;
    
    if (items == 0) {
        return 0;
    }
    
    valid = 0;
    choice = 0;
    for (i = 0; items[i] != 0; i = i + 1) {
    }
    choice_max = i;
    
    for (j = 0; j < 1024; j = j + 1) {
        buf[j] = '\0';
    }
    
    buf[0] = '1';
    buf[1] = '\0';
    
    num = 0;
    sign = 1;
    j = 0;
    if (buf[j] == '-') {
        sign = -1;
        j = j + 1;
    }
    for (; buf[j] != '\0'; j = j + 1) {
        if (buf[j] >= '0' && buf[j] <= '9') {
            digit = buf[j] - '0';
            num = num * 10 + digit;
        }
    }
    choice = num * sign;
    
    if (choice >= 1 && choice <= choice_max) {
        valid = 1;
    }
    
    if (valid) {
        return items[choice - 1];
    }
    
    return 0;
}
