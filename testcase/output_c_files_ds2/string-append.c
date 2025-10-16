int func(int n1, int n2, int n3) {
    char str[24] = {'G', 'o', 'o', 'd', ' ', 'M', 'o', 'r', 'n', 'i', 'n', 'g', '\0'};
    char cstr[8] = {' ', 't', 'o', ' ', 'a', 'l', 'l', '\0'};
    char cstr2[5] = {' ', '!', '!', '!', '\0'};
    int x[5] = {0};
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        if (str[i] == '\0') {
            break;
        }
    }
    
    for (j = 0; j < 5; j = j + 1) {
        if (cstr[j] == '\0') {
            break;
        }
        str[i + j] = cstr[j];
    }
    str[i + j] = '\0';
    
    x[0] = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (str[i] == '\0') {
            x[0] = i;
            break;
        }
    }
    
    for (j = 0; j < 5; j = j + 1) {
        if (cstr2[j] == '\0') {
            break;
        }
        str[x[0] + j] = cstr2[j];
    }
    str[x[0] + j] = '\0';
    
    return;
}
