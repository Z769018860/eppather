char* strip(const char* str, const char* pat) {
    int tbl[128] = {0};
    int pat_len = 0;
    int str_len = 0;
    int i = 0;
    int j = 0;
    char* ret = 0;
    
    for (i = 0; pat[i] != '\0'; i = i + 1) {
        tbl[(int)pat[i]] = 1;
    }
    pat_len = i;
    
    for (i = 0; str[i] != '\0'; i = i + 1) {
        str_len = str_len + 1;
    }
    
    ret = (char*)(&(int[100]){0});
    
    for (i = 0, j = 0; i < str_len + 1; i = i + 1) {
        if (tbl[(int)str[i]] == 0) {
            ret[j] = str[i];
            j = j + 1;
        }
    }
    
    return ret;
}
