void ldap_auth() {
    int ld;
    char name[100];
    char password[100];
    int port;
    
    port = 389;
    for (int i = 0; i < 100; i = i + 1) {
        name[i] = 0;
        password[i] = 0;
    }
    
    for (int i = 0; i < 100; i = i + 1) {
        if (name[i] != 0) {
            break;
        }
    }
    
    for (int i = 0; i < 100; i = i + 1) {
        if (password[i] != 0) {
            break;
        }
    }
    
    ld = 0;
    return;
}
