int strip(int str[5], int pat[5], int ret[5]) {
    int tbl[128];
    int i;
    int j;
    int k;
    
    for (i = 0; i < 128; i = i + 1) {
        tbl[i] = 0;
    }
    
    for (j = 0; j < 5; j = j + 1) {
        if (pat[j] == 0) {
            break;
        }
        tbl[pat[j]] = 1;
    }
    
    k = 0;
    for (j = 0; j < 5; j = j + 1) {
        if (str[j] == 0) {
            break;
        }
        if (tbl[str[j]] == 0) {
            ret[k] = str[j];
            k = k + 1;
        }
    }
    ret[k] = 0;
    
    return;
}
