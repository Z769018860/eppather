void stripcomments(int s_len, char s[5], int ca_len, char ca[5], int cb_len, char cb[5], int al, int bl) {
    int a_pos;
    int b_pos;
    int len;
    int i;
    int j;
    int k;
    
    len = s_len;
    for (i = 0; i < 5; i = i + 1) {
        a_pos = -1;
        for (j = 0; j < len - ca_len + 1; j = j + 1) {
            int match = 1;
            for (k = 0; k < ca_len; k = k + 1) {
                if (s[j + k] != ca[k]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                a_pos = j;
                break;
            }
        }
        if (a_pos == -1) {
            break;
        }
        b_pos = -1;
        for (j = a_pos + al; j < len - cb_len + 1; j = j + 1) {
            int match = 1;
            for (k = 0; k < cb_len; k = k + 1) {
                if (s[j + k] != cb[k]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                b_pos = j;
                break;
            }
        }
        if (b_pos == -1) {
            break;
        }
        b_pos = b_pos + bl;
        for (j = a_pos; j < len - (b_pos - a_pos); j = j + 1) {
            s[j] = s[j + (b_pos - a_pos)];
        }
        len = len - (b_pos - a_pos);
    }
    return;
}
