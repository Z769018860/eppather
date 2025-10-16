int repstr(char* str) {
    int sl;
    int sl_max;
    int i;
    int j;
    int k;
    int found;
    
    if (str == 0) {
        return 0;
    }
    
    sl_max = 0;
    while (str[sl_max] != 0) {
        sl_max = sl_max + 1;
    }
    
    for (sl = 1; sl < sl_max; sl = sl + 1) {
        found = 1;
        for (i = 0; i < sl_max - sl; i = i + 1) {
            if (str[i] != str[i + sl]) {
                found = 0;
                break;
            }
        }
        if (found == 1) {
            return sl;
        }
    }
    
    return 0;
}
