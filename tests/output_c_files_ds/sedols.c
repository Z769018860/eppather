int sedol_checksum(const char *sedol6)
{
    int len = 0;
    int sum = 0;
    int i;
    int j;
    int found;
    int sedol_weights[6] = {1, 3, 1, 7, 3, 9};
    char reject[10] = {'A','E','I','O','U','a','e','i','o','u'};
    
    for (len = 0; sedol6[len] != '\0'; len = len + 1) {}
    
    if (len == 7) {
        return sedol6[6] & 127;
    }
    
    if ((len > 7) || (len < 6)) {
        return -1;
    }
    
    found = 0;
    for (i = 0; i < 6; i = i + 1) {
        for (j = 0; j < 10; j = j + 1) {
            if (sedol6[i] == reject[j]) {
                found = 1;
            }
        }
    }
    if (found != 0) {
        return -1;
    }
    
    for (i = 0; i < 6; i = i + 1) {
        if (sedol6[i] >= '0' && sedol6[i] <= '9') {
            sum = sum + (sedol6[i] - '0') * sedol_weights[i];
        } else if ((sedol6[i] >= 'A' && sedol6[i] <= 'Z') || (sedol6[i] >= 'a' && sedol6[i] <= 'z')) {
            int c = sedol6[i];
            if (c >= 'a' && c <= 'z') {
                c = c - 32;
            }
            sum = sum + ((c - 'A') + 10) * sedol_weights[i];
        } else {
            return -1;
        }
    }
    
    return ((10 - (sum % 10)) % 10) + '0';
}
