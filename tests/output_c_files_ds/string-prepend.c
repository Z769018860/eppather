void rewrite_function() {
    char str[100] = "my String";
    char cstr[9] = "Changed ";
    char dup[100];
    int i;
    int j;
    
    for (i = 0; i < 9; i = i + 1) {
        if (cstr[i] == '\0') {
            break;
        }
        str[i] = cstr[i];
    }
    
    for (j = 0; j < 100; j = j + 1) {
        dup[j] = str[j];
        if (str[j] == '\0') {
            break;
        }
    }
    
    for (j = 0; j < 100; j = j + 1) {
        if (dup[j] == '\0') {
            break;
        }
        str[i + j] = dup[j];
    }
    str[i + j] = '\0';
    
    return;
}
