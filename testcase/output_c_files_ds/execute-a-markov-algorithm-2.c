void markoved(char* text, char* output) {
    int i;
    int j;
    int len;
    for (len = 0; text[len] != '\0'; len = len + 1) {}
    for (i = 0; i < len; i = i + 1) {
        if (text[i] == 'B') {
            if (i + 1 < len && text[i + 1] == ' ') {
                output[i] = 'b';
                output[i + 1] = 'a';
                output[i + 2] = 'g';
                i = i + 2;
            } else {
                output[i] = 'm';
                output[i + 1] = 'o';
                output[i + 2] = 'n';
                output[i + 3] = 'e';
                output[i + 4] = 'y';
                i = i + 4;
            }
        } else if (text[i] == 'A') {
            output[i] = 'a';
            output[i + 1] = 'p';
            output[i + 2] = 'p';
            output[i + 3] = 'l';
            output[i + 4] = 'e';
            i = i + 4;
        } else if (text[i] == 'T' && i + 1 < len && text[i + 1] == ' ') {
            output[i] = 'm';
            output[i + 1] = 'y';
            output[i + 2] = ' ';
            output[i + 3] = 'b';
            output[i + 4] = 'r';
            output[i + 5] = 'o';
            output[i + 6] = 't';
            output[i + 7] = 'h';
            output[i + 8] = 'e';
            output[i + 9] = 'r';
            i = i + 9;
        } else if (text[i] == 'S' && i > 0 && text[i - 1] == ' ') {
            output[i] = 's';
            output[i + 1] = 'h';
            output[i + 2] = 'o';
            output[i + 3] = 'p';
            i = i + 3;
        } else if (text[i] == 'W' && i + 1 < len && text[i + 1] == ' ') {
            output[i] = 'w';
            output[i + 1] = 'i';
            output[i + 2] = 't';
            output[i + 3] = 'h';
            i = i + 3;
        } else if (text[i] == '_') {
            for (j = i; j < len && text[j] != '*'; j = j + 1) {
                output[j] = '1';
            }
            for (; j < len && text[j] != '_'; j = j + 1) {
                output[j] = '1';
            }
            i = j;
        } else if (text[i] == 'A' && i > 0 && text[i - 1] == '0') {
            output[i - 1] = '0';
            output[i] = '0';
            output[i + 1] = '0';
            output[i + 2] = '1';
            output[i + 3] = '1';
            output[i + 4] = 'H';
            output[i + 5] = '1';
            output[i + 6] = '1';
            output[i + 7] = '1';
            output[i + 8] = '0';
            output[i + 9] = '0';
            output[i + 10] = '0';
            i = i + 10;
        } else {
            output[i] = text[i];
        }
    }
    output[len] = '\0';
    return;
}
