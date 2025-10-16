int func(int n1, int n2) {
    char str[100];
    char cstr[100];
    char dup[100];
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        str[i] = "my String"[i];
    }
    str[5] = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        cstr[i] = "Changed "[i];
    }
    cstr[5] = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        dup[i] = str[i];
    }
    dup[5] = 0;
    
    for (i = 0; cstr[i] != 0; i = i + 1) {
        str[i] = cstr[i];
    }
    
    for (j = 0; dup[j] != 0; j = j + 1) {
        str[i + j] = dup[j];
    }
    str[i + j] = 0;
    
    return;
}
