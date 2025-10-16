int str_cmp(int l_len, int l_alloc, unsigned char* l_s, int r_len, int r_alloc, unsigned char* r_s) {
    int res;
    int len = l_len;
    if (len > r_len) {
        len = r_len;
    }
    int i;
    for (i = 0; i < len; i = i + 1) {
        if (l_s[i] != r_s[i]) {
            res = l_s[i] - r_s[i];
            return res;
        }
    }
    if (l_len > r_len) {
        return 1;
    } else {
        return -1;
    }
    return 0;
}

void str_append(int* s_len, int* s_alloc, unsigned char s_s[1024], unsigned char b) {
    if (*s_len >= *s_alloc) {
        *s_alloc = *s_alloc * 2;
        if (*s_alloc - *s_alloc / 2 > 1024) {
            *s_alloc = *s_alloc / 2 + 1024;
        }
    }
    s_s[*s_len] = b;
    *s_len = *s_len + 1;
    return;
}

void str_swap(int* a_len, int* a_alloc, unsigned char a_s[1024], int* b_len, int* b_alloc, unsigned char b_s[1024]) {
    int tz;
    unsigned char ts[1024];
    int i;
    tz = *a_alloc;
    *a_alloc = *b_alloc;
    *b_alloc = tz;
    tz = *a_len;
    *a_len = *b_len;
    *b_len = tz;
    for (i = 0; i < 1024; i = i + 1) {
        ts[i] = a_s[i];
        a_s[i] = b_s[i];
        b_s[i] = ts[i];
    }
    return;
}

void str_subst(int* tgt_len, int* tgt_alloc, unsigned char tgt_s[1024], int pat_len, int pat_alloc, unsigned char pat_s[1024], int repl_len, int repl_alloc, unsigned char repl_s[1024]) {
    int tmp_len = 0;
    int tmp_alloc = 8;
    unsigned char tmp_s[1024];
    int i = 0;
    int j;
    for (i = 0; i + pat_len <= *tgt_len; ) {
        int match = 1;
        for (j = 0; j < pat_len; j = j + 1) {
            if (tgt_s[i + j] != pat_s[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            for (j = 0; j < repl_len; j = j + 1) {
                str_append(&tmp_len, &tmp_alloc, tmp_s, repl_s[j]);
            }
            i = i + pat_len;
            if (pat_len == 0) {
                str_append(&tmp_len, &tmp_alloc, tmp_s, tgt_s[i]);
                i = i + 1;
            }
        } else {
            str_append(&tmp_len, &tmp_alloc, tmp_s, tgt_s[i]);
            i = i + 1;
        }
    }
    while (i < *tgt_len) {
        str_append(&tmp_len, &tmp_alloc, tmp_s, tgt_s[i]);
        i = i + 1;
    }
    str_swap(tgt_len, tgt_alloc, tgt_s, &tmp_len, &tmp_alloc, tmp_s);
    return;
}
