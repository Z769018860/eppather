void translate(const char* i, char* o) {
    const char* ascii = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?'!/()&:;=+-_\"$@";
    const char* itu[] = {
        "13","3111","3131","311","1","1131","331","1111","11","1333","313","1311","33","31","333","1331","3313","131","111","3","113","1113","133","3113","3133","3311","33333","13333","11333","11133","11113","11111","31111","33111","33311","33331","131313","331133","113311","133331","313133","31131","31331","313313","13111","333111","313131","31113","13131","311113","113313","131131","1113113","133131"
    };
    char dih[50] = " -n -f 440 -l 100 -D 100";
    char dah[50] = " -n -f 440 -l 300 -D 100";
    char medium[30] = " -n -D 200";
    char word[30] = " -n -D 400";
    char* dd[2] = {dih, dah};
    int pos = 0;
    int j = 0;
    int k = 0;
    int m = 0;
    int n = 0;
    
    o[0] = 'b';
    o[1] = 'e';
    o[2] = 'e';
    o[3] = 'p';
    o[4] = '\0';
    pos = 4;
    
    for (j = 0; i[j] != '\0'; j = j + 1) {
        char c = i[j];
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
        const char* pc = 0;
        int found = 0;
        for (k = 0; ascii[k] != '\0'; k = k + 1) {
            if (ascii[k] == c) {
                pc = &ascii[k];
                found = 1;
                break;
            }
        }
        if (found == 0) {
            for (m = 0; word[m] != '\0'; m = m + 1) {
                o[pos] = word[m];
                pos = pos + 1;
            }
        } else {
            const char* morse = itu[k];
            for (m = 0; morse[m] != '\0'; m = m + 1) {
                char* s = dd[morse[m] == '3' ? 1 : 0];
                for (n = 0; s[n] != '\0'; n = n + 1) {
                    o[pos] = s[n];
                    pos = pos + 1;
                }
            }
            for (m = 0; medium[m] != '\0'; m = m + 1) {
                o[pos] = medium[m];
                pos = pos + 1;
            }
        }
    }
    for (m = 0; word[m] != '\0'; m = m + 1) {
        o[pos] = word[m];
        pos = pos + 1;
    }
    o[pos] = '\0';
    return;
}
