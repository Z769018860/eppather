int repstr(char* str) {
    int sl = 0;
    int len = 0;
    int match = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    
    if (str == 0) {
        return 0;
    }
    
    for (len = 0; str[len] != '\0'; len = len + 1) {
    }
    
    sl = len / 2;
    
    for (; sl > 0; sl = sl - 1) {
        match = 1;
        for (i = 0; i < sl; i = i + 1) {
            if (str[i] != str[sl + i]) {
                match = 0;
                break;
            }
        }
        if (match == 1) {
            return sl;
        }
    }
    
    return 0;
}
