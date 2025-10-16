int countSubstring(const char *str, const char *sub) {
    int count;
    int i;
    int j;
    int k;
    int match;
    int sub_len;
    int str_len;
    
    count = 0;
    sub_len = 0;
    str_len = 0;
    
    for (i = 0; sub[i] != '\0'; i = i + 1) {
        sub_len = sub_len + 1;
    }
    
    for (i = 0; str[i] != '\0'; i = i + 1) {
        str_len = str_len + 1;
    }
    
    if (sub_len == 0) {
        return 0;
    }
    
    for (i = 0; i <= str_len - sub_len; i = i + 1) {
        match = 1;
        for (j = 0, k = i; j < sub_len; j = j + 1, k = k + 1) {
            if (str[k] != sub[j]) {
                match = 0;
                break;
            }
        }
        if (match == 1) {
            count = count + 1;
            i = i + sub_len - 1;
        }
    }
    
    return count;
}
