void permutate(int n_letters, int pos, int overlap, int letters_count[26], char letters_char[26], int orig_len, char orig[100], char out[100], char best[100], int* least_overlap, int* seq_no)
{
    int i;
    int ol;
    if (pos < 0) {
        if (overlap < (*least_overlap)) {
            (*least_overlap) = overlap;
            (*seq_no) = 0;
        }
        (*seq_no) = (*seq_no) + 1;
        for (i = 0; i < orig_len; i = i + 1) {
            best[i] = out[i];
        }
        best[orig_len] = '\0';
        return;
    }
    for (i = 0; i < n_letters; i = i + 1) {
        if (letters_count[i] == 0) {
            continue;
        }
        out[pos] = letters_char[i];
        letters_count[i] = letters_count[i] - 1;
        if (letters_char[i] == orig[pos]) {
            ol = overlap + 1;
        } else {
            ol = overlap;
        }
        if (ol <= (*least_overlap)) {
            permutate(n_letters, pos - 1, ol, letters_count, letters_char, orig_len, orig, out, best, least_overlap, seq_no);
        }
        letters_count[i] = letters_count[i] + 1;
    }
    return;
}

void do_string(char str[100], int str_len, char best[100], int* least_overlap, int* seq_no, char orig[100], char out[100])
{
    int letters_count[26];
    char letters_char[26];
    int i;
    int c;
    int n_letters;
    (*least_overlap) = str_len;
    for (i = 0; i < str_len; i = i + 1) {
        orig[i] = str[i];
    }
    orig[str_len] = '\0';
    (*seq_no) = 0;
    out[str_len] = '\0';
    (*least_overlap) = (*least_overlap) + 1;
    for (i = 0; i < 26; i = i + 1) {
        letters_count[i] = 0;
        letters_char[i] = i + 97;
    }
    for (i = 0; i < str_len; i = i + 1) {
        letters_count[str[i] - 97] = letters_count[str[i] - 97] + 1;
    }
    n_letters = 0;
    for (i = 0; i < 26; i = i + 1) {
        if (letters_count[i] > 0) {
            letters_count[n_letters] = letters_count[i];
            letters_char[n_letters] = letters_char[i];
            n_letters = n_letters + 1;
        }
    }
    permutate(n_letters, str_len - 1, 0, letters_count, letters_char, str_len, orig, out, best, least_overlap, seq_no);
    return;
}
