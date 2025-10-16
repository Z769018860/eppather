int copy_strings() {
    char src[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char dst1[80];
    char dst2[80];
    char dst3[6];
    char ref[6];
    int len;
    int i;
    
    for (i = 0; i < 6; i = i + 1) {
        dst1[i] = src[i];
    }
    
    len = 0;
    for (i = 0; src[i] != '\0'; i = i + 1) {
        len = len + 1;
    }
    
    if (len >= 80) {
        return;
    }
    
    for (i = 0; i < len + 1; i = i + 1) {
        dst2[i] = src[i];
    }
    
    for (i = 0; i < 6; i = i + 1) {
        dst3[i] = src[i];
    }
    
    for (i = 0; i < 6; i = i + 1) {
        ref[i] = src[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        src[i] = '-';
    }
    
    return;
}
