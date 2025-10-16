int deranged(const char *s1, const char *s2) {
    int i;
    for (i = 0; s1[i] != 0; i = i + 1) {
        if (s1[i] == s2[i]) {
            return 0;
        }
    }
    return 1;
}

int count_letters(const char *s, unsigned char *c) {
    int i;
    int len;
    for (i = 0; i < 26; i = i + 1) {
        c[i] = 0;
    }
    len = 0;
    for (i = 0; s[i] != 0; i = i + 1) {
        if (s[i] < 'a' || s[i] > 'z') {
            return 0;
        }
        len = len + 1;
        c[(unsigned char)s[i] - 'a'] = c[(unsigned char)s[i] - 'a'] + 1;
    }
    return len;
}

void process_words() {
    int char_to_idx[128];
    int i;
    int j;
    int best_len;
    const char *b1;
    const char *b2;
    unsigned char cnt[26];
    int root_down[10][10];
    int root_list[10];
    int words[10000];
    int st_size;
    int fd;
    int match_found;

    for (i = 0; i < 128; i = i + 1) {
        char_to_idx[i] = 0;
    }
    for (i = 0; i < 10; i = i + 1) {
        for (j = 0; j < 10; j = j + 1) {
            root_down[i][j] = 0;
        }
        root_list[i] = 0;
    }
    for (i = 0; i < 10000; i = i + 1) {
        words[i] = 0;
    }
    st_size = 0;
    fd = 0;
    best_len = 0;
    b1 = 0;
    b2 = 0;
    match_found = 0;

    for (i = 0; i < 26; i = i + 1) {
        char_to_idx["zqxjkvbpygfwmucldrhsnioate"[i]] = i;
    }

    for (i = 0, j = 0; i < st_size; i = i + 1) {
        if (words[i] != '\n') {
            continue;
        }
        words[i] = 0;

        if (i - j > best_len) {
            count_letters((const char *)(words + j), cnt);
            match_found = deranged((const char *)(words + j), (const char *)(words + j + 1));
            if (match_found) {
                best_len = i - j;
                b1 = (const char *)(words + j);
                b2 = (const char *)(words + j + 1);
            }
        }
        j = i + 1;
        i = i + 1;
    }
    return;
}
