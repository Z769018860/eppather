int filter_and_extract(char buffer[16384], int lr) {
    int amatch_rm_so;
    int amatch_rm_eo;
    int bi;
    int found;
    int i;
    int j;
    
    for (i = 0; i < 16384; i = i + 1) {
        if (i >= lr) {
            break;
        }
    }
    
    amatch_rm_so = 0;
    amatch_rm_eo = 0;
    
    for (i = 0; i < lr - 3; i = i + 1) {
        found = 1;
        for (j = 0; j < 4; j = j + 1) {
            if (buffer[i + j] != " UTC"[j]) {
                found = 0;
                break;
            }
        }
        if (found) {
            amatch_rm_so = i;
            amatch_rm_eo = i + 4;
            break;
        }
    }
    
    bi = amatch_rm_so;
    while (bi > 0) {
        found = 1;
        for (j = 0; j < 4; j = j + 1) {
            if (buffer[bi - 1 + j] != "<BR>"[j]) {
                found = 0;
                break;
            }
        }
        if (found) {
            break;
        }
        bi = bi - 1;
    }
    
    for (i = bi + 4; i < amatch_rm_eo; i = i + 1) {
        buffer[i - (bi + 4)] = buffer[i];
    }
    buffer[amatch_rm_eo - (bi + 4)] = 0;
    
    return;
}
