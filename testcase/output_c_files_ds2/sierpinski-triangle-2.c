void rule_90(char* evstr, int l) {
    int i;
    int cp[5];
    int s[3];
    int n1;
    int n2;
    int n3;
    
    for (i = 0; i < 5; i = i + 1) {
        cp[i] = evstr[i];
    }
    
    for (i = 0; i < l; i = i + 1) {
        s[1] = (cp[i] == 42) ? 1 : 0;
        if ((i - 1) < 0) {
            n1 = 0;
        } else {
            n1 = (cp[i - 1] == 42) ? 1 : 0;
        }
        s[0] = n1;
        if ((i + 1) < l) {
            n2 = (cp[i + 1] == 42) ? 1 : 0;
        } else {
            n2 = 0;
        }
        s[2] = n2;
        if ((s[0] && !s[2]) || (!s[0] && s[2])) {
            evstr[i] = 42;
        } else {
            evstr[i] = 32;
        }
    }
    return;
}
