void scroll_it(int direction, int cx, int slen, int hello_len, char hello[13], char label_text[13]) {
    int new_cx;
    if (direction > 0) {
        new_cx = (cx + 1) % slen;
    } else {
        new_cx = (cx + slen - 1) % slen;
    }
    
    char rotated[13];
    int i;
    int j;
    int cl = hello_len;
    for (i = new_cx, j = 0; cl > 0; cl = cl - 1, i = (i + 1) % slen, j = j + 1) {
        rotated[j] = hello[i];
    }
    rotated[hello_len] = 0;
    
    for (i = 0; i < 13; i = i + 1) {
        label_text[i] = rotated[i];
    }
    
    return;
}
