int ldap_auth_search() {
    int ld = 0;
    char name[100] = {0};
    char password[100] = {0};
    int result[100] = {0};
    int i = 0;
    int j = 0;
    int k = 0;
    
    for (i = 0; i < 100; i = i + 1) {
        name[i] = 0;
        password[i] = 0;
    }
    
    for (j = 0; j < 100; j = j + 1) {
        result[j] = 0;
    }
    
    for (k = 0; k < 100; k = k + 1) {
        if (name[k] != 0) {
            if (password[k] != 0) {
                result[k] = 1;
            }
        }
    }
    
    return;
}
