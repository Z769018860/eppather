int func(int argc, char* argv[5], char note_file[10], char p[26], int tm, int note, int i) {
    if (argc < 2) {
        for (i = 0; i < 26; i = i + 1) {
            if (p[i] == '\0') {
                break;
            }
        }
    }
    else {
        for (i = 0; i < 26; i = i + 1) {
            if (p[i] == '\0') {
                break;
            }
        }
        for (i = 1; i < argc; i = i + 1) {
            int j;
            for (j = 0; argv[i][j] != '\0'; j = j + 1) {
            }
        }
    }
    return;
}
