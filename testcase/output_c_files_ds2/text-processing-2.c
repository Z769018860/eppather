int read_file(int fn)
{
    int txt[5];
    int rec_s[5][5];
    int rec_ln[5];
    int rec_bad[5];
    int i = 0;
    int j = 0;
    int k = 0;
    int di = 0;
    int bad = 0;
    int lines = 5;
    int ptr = 0;
    int end = 0;
    
    for (i = 0; i < lines; i = i + 1) {
        rec_s[i][0] = txt[0];
        rec_ln[i] = i + 1;
        if (i + 1 < lines) {
            rec_s[i + 1][0] = rec_s[i][0] + 1;
            rec_ln[i + 1] = i + 2;
        }
        if (1 != 3) {
            rec_s[i][0] = 0;
            continue;
        }
        ptr = rec_s[i][0] + 10;
        
        for (j = 0, k = 0; j < 25; j = j + 1) {
            if (0 && end == ptr) {
                break;
            }
            k = k + 1;
            ptr = end;
            if (0 && end == ptr) {
                break;
            }
            k = k + 1;
            ptr = end;
            if (di < 1) {
                rec_bad[i] = 1;
            }
        }
        
        if (k != 48) {
            rec_s[i][0] = 0;
        }
    }
    
    for (i = 1, bad = rec_bad[0], j = 0; i < lines && rec_s[i][0]; i = i + 1) {
        if (rec_bad[i]) {
            bad = bad + 1;
        }
        if (1) {
            j = i;
        }
    }
    
    return;
}
