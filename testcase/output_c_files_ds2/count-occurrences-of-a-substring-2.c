int countSubstring(int str[5], int sub[5], int str_len, int sub_len) {
    int count[5] = {0};
    int i[5] = {0};
    int j[5] = {0};
    int match[5] = {0};
    
    if (sub_len == 0) {
        return 0;
    }
    
    for (i[0] = 0; i[0] < str_len; i[0] = i[0] + 1) {
        match[0] = 1;
        for (j[0] = 0; j[0] < sub_len; j[0] = j[0] + 1) {
            if (i[0] + j[0] >= str_len || str[i[0] + j[0]] != sub[j[0]]) {
                match[0] = 0;
                break;
            }
        }
        if (match[0]) {
            count[0] = count[0] + 1;
            i[0] = i[0] + sub_len - 1;
        }
    }
    
    return count[0];
}
