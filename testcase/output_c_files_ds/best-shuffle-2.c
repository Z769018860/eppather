int count_letters(const char *s, int all_letters_count[26], char all_letters_char[26], int letters[26]) {
    int i;
    int c;
    for (i = 0; i < 26; i = i + 1) {
        all_letters_count[i] = 0;
        all_letters_char[i] = i + 'a';
    }
    while (*s != '\0') {
        i = *s;
        s = s + 1;
        if (i < 'a' || i > 'z') {
            return -1;
        }
        all_letters_count[i - 'a'] = all_letters_count[i - 'a'] + 1;
    }
    c = 0;
    for (i = 0; i < 26; i = i + 1) {
        if (all_letters_count[i] > 0) {
            letters[c] = i;
            c = c + 1;
        }
    }
    return c;
}

void permutate(int n_letters, int pos, int overlap, int least_overlap, int* seq_no, char out[100], char orig[100], char best[100], int letters_count[26], char letters_char[26], int letters_index[26]) {
    int i;
    int ol;
    if (pos < 0) {
        if (overlap < least_overlap) {
            least_overlap = overlap;
            *seq_no = 0;
        }
        *seq_no = *seq_no + 1;
        if (*seq_no <= 1) {
            for (i = 0; i < 100; i = i + 1) {
                best[i] = out[i];
            }
        }
        return;
    }
    for (i = 0; i < n_letters; i = i + 1) {
        if (letters_count[letters_index[i]] == 0) {
            continue;
        }
        out[pos] = letters_char[letters_index[i]];
        letters_count[letters_index[i]] = letters_count[letters_index[i]] - 1;
        if (letters_char[letters_index[i]] == orig[pos]) {
            ol = overlap + 1;
        } else {
            ol = overlap;
        }
        if (ol <= least_overlap) {
            permutate(n_letters, pos - 1, ol, least_overlap, seq_no, out, orig, best, letters_count, letters_char, letters_index);
        }
        letters_count[letters_index[i]] = letters_count[letters_index[i]] + 1;
    }
    return;
}

void do_string(const char *str, char best[100], int* least_overlap) {
    int all_letters_count[26];
    char all_letters_char[26];
    int letters_index[26];
    char out[100];
    char orig[100];
    int seq_no;
    int len;
    int i;
    len = 0;
    while (str[len] != '\0') {
        len = len + 1;
    }
    *least_overlap = len;
    for (i = 0; i < len; i = i + 1) {
        orig[i] = str[i];
    }
    orig[len] = '\0';
    seq_no = 0;
    out[len] = '\0';
    *least_overlap = *least_overlap + 1;
    int n_letters = count_letters(str, all_letters_count, all_letters_char, letters_index);
    permutate(n_letters, len - 1, 0, *least_overlap, &seq_no, out, orig, best, all_letters_count, all_letters_char, letters_index);
    return;
}
