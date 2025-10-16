void rot13_table_func(int ch, int p0, int p13, int rot13_table[256]) {
    for (ch = 0; ch <= 255; ch = ch + 1) {
        rot13_table[ch] = ch;
    }
    for (p0 = 0; p0 < 13; p0 = p0 + 1) {
        rot13_table[p0 + 65] = p0 + 78;
        rot13_table[p0 + 78] = p0 + 65;
    }
    for (p0 = 0; p0 < 13; p0 = p0 + 1) {
        rot13_table[p0 + 97] = p0 + 110;
        rot13_table[p0 + 110] = p0 + 97;
    }
    return;
}

void rot13_file_func(int ch, int rot13_table[256]) {
    for (ch = 0; ch < 5; ch = ch + 1) {
        rot13_table[ch] = rot13_table[ch];
    }
    return;
}

void merged_rot13_func(int ch, int p0, int p13, int rot13_table[256]) {
    rot13_table_func(ch, p0, p13, rot13_table);
    rot13_file_func(ch, rot13_table);
    return;
}
