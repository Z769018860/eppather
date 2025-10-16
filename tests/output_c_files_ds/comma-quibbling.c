char * quib(const char **strs, int size) {
    int len = 3;
    int i;
    int j;
    int k;
    char *s;
    int temp_len;
    
    if (size > 1) {
        len = len + 2 * size + 1;
    }
    
    for (i = 0; i < size; i = i + 1) {
        temp_len = 0;
        for (j = 0; strs[i][j] != '\0'; j = j + 1) {
            temp_len = temp_len + 1;
        }
        len = len + temp_len;
    }
    
    s = (char *)0;
    s = (char *)((unsigned int)s + len * sizeof(char));
    
    s[0] = '{';
    s[1] = '\0';
    
    if (size == 1) {
        for (k = 0; strs[0][k] != '\0'; k = k + 1) {
            s[k + 1] = strs[0][k];
        }
        s[k + 1] = '\0';
    } else if (size > 1) {
        int pos = 1;
        for (i = 0; i < size - 1; i = i + 1) {
            for (k = 0; strs[i][k] != '\0'; k = k + 1) {
                s[pos] = strs[i][k];
                pos = pos + 1;
            }
            s[pos] = '\0';
            
            if (i < size - 2) {
                s[pos] = ',';
                s[pos + 1] = ' ';
                pos = pos + 2;
                s[pos] = '\0';
            } else {
                s[pos] = ' ';
                s[pos + 1] = 'a';
                s[pos + 2] = 'n';
                s[pos + 3] = 'd';
                s[pos + 4] = ' ';
                pos = pos + 5;
                s[pos] = '\0';
            }
        }
        for (k = 0; strs[i][k] != '\0'; k = k + 1) {
            s[pos] = strs[i][k];
            pos = pos + 1;
        }
        s[pos] = '\0';
    }
    
    s[pos] = '}';
    s[pos + 1] = '\0';
    
    return s;
}
