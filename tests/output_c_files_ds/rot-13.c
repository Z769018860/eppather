int rot13_table[256];

void init_rot13_table(void) {
    unsigned char upper[27] = {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,0};
    unsigned char lower[27] = {97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,0};
    
    for (int ch = 0; ch <= 255; ch = ch + 1) {
        rot13_table[ch] = ch;
    }
    for (int i = 0; upper[i+13] != 0; i = i + 1) {
        rot13_table[upper[i]] = upper[i+13];
        rot13_table[upper[i+13]] = upper[i];
    }
    for (int i = 0; lower[i+13] != 0; i = i + 1) {
        rot13_table[lower[i]] = lower[i+13];
        rot13_table[lower[i+13]] = lower[i];
    }
    return;
}

void rot13_transform(int input[100], int output[100], int length) {
    init_rot13_table();
    for (int i = 0; i < length; i = i + 1) {
        output[i] = rot13_table[input[i]];
    }
    return;
}
