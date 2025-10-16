int frequency[26];
void count_letters(int input_chars[1000], int input_len) {
    int ch;
    int i;
    for (ch = 0; ch < 26; ch = ch + 1) {
        frequency[ch] = 0;
    }
    for (i = 0; i < input_len; i = i + 1) {
        ch = input_chars[i];
        if ('a' <= ch && ch <= 'z') {
            frequency[ch - 'a'] = frequency[ch - 'a'] + 1;
        }
        else if ('A' <= ch && ch <= 'Z') {
            frequency[ch - 'A'] = frequency[ch - 'A'] + 1;
        }
    }
    return;
}
