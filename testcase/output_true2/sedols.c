int sedol_checksum(const char *sedol6, int maxlinelen)
{
    int sedol_weights[6] = {1, 3, 1, 7, 3, 9};
    int reject[10] = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
    int len = 0;
    int sum = 0;
    int i;
    int j;
    int found;
    int temp;
    
    for (i = 0; i < maxlinelen; i = i + 1) {
        if (sedol6[i] == 0) {
            break;
        }
        len = len + 1;
    }
    
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
                break;
            }
        }
        if (found == 1) {
            break;
        }
    }
    if (found == 1) {
        return -1;
    }
    
    for (i = 0; i < 6; i = i + 1) {
        if (sedol6[i] >= '0' && sedol6[i] <= '9') {
            sum = sum + (sedol6[i] - '0') * sedol_weights[i];
        } else if ((sedol6[i] >= 'A' && sedol6[i] <= 'Z') || (sedol6[i] >= 'a' && sedol6[i] <= 'z')) {
            temp = sedol6[i];
            if (temp >= 'a' && temp <= 'z') {
                temp = temp - 32;
            }
            sum = sum + ((temp - 'A') + 10) * sedol_weights[i];
        } else {
            return -1;
        }
    }
    
    return (10 - (sum % 10)) % 10 + '0';
}
