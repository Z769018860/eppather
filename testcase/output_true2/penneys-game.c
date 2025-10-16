int getseq(int s_len, char* s)
{
    int r[5];
    r[0] = 0;
    int i[5];
    i[0] = 1 << (s_len - 1);
    
    for (; *s && i[0]; s = s + 1) {
        if (*s == 'H' || *s == 'h') {
            r[0] = r[0] | i[0];
        } else {
            if (*s == 'T' || *s == 't') {
            } else {
                return -1;
            }
        }
        i[0] = i[0] >> 1;
    }
    
    return r[0];
}

int getai(int s_len, int user)
{
    int ai[5];
    
    if (user == -1) {
        ai[0] = rand() & ((1 << s_len) - 1);
    } else {
        ai[0] = (user >> 1) | ((~user << 1) & (1 << (s_len - 1)));
    }
    
    return ai[0];
}

int rungame(int s_len, int user, int ai)
{
    int last3[5];
    last3[0] = rand() & ((1 << s_len) - 1);
    
    for (;;) {
        if (user == last3[0]) {
            return 1;
        }
        
        if (ai == last3[0]) {
            return 0;
        }
        
        last3[0] = ((last3[0] << 1) & ((1 << s_len) - 2)) | (rand() & 1);
    }
    
    return 0;
}
