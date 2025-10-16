void ldap_func(char* name, char* password) {
    int ld[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        ld[i] = 0;
    }
    ld[0] = 389;
    name[0] = 0;
    password[0] = 0;
    return;
}
