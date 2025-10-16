int func() {
    char str[24] = {'G', 'o', 'o', 'd', ' ', 'M', 'o', 'r', 'n', 'i', 'n', 'g', '\0'};
    char cstr[8] = {' ', 't', 'o', ' ', 'a', 'l', 'l', '\0'};
    char cstr2[5] = {' ', '!', '!', '!', '\0'};
    int x = 0;
    int len1 = 0;
    int len2 = 0;
    int len3 = 0;
    int i = 0;
    int j = 0;
    
    for (i = 0; str[i] != '\0'; i = i + 1) {
        len1 = len1 + 1;
    }
    for (i = 0; cstr[i] != '\0'; i = i + 1) {
        len2 = len2 + 1;
    }
    for (i = 0; cstr2[i] != '\0'; i = i + 1) {
        len3 = len3 + 1;
    }
    
    if (24 > len1 + len2 + len3) {
        for (i = len1, j = 0; cstr[j] != '\0'; i = i + 1, j = j + 1) {
            str[i] = cstr[j];
        }
        str[i] = '\0';
        
        x = 0;
        for (i = 0; str[i] != '\0'; i = i + 1) {
            x = x + 1;
        }
        
        for (i = x, j = 0; cstr2[j] != '\0'; i = i + 1, j = j + 1) {
            str[i] = cstr2[j];
        }
        str[i] = '\0';
    }
    
    return;
}
