int move_to_front(char str[100], char c) {
    char p[100];
    int shift;
    int i;
    int len;
    len = 0;
    for (i = 0; i < 100; i = i + 1) {
        if (str[i] == '\0') {
            break;
        }
        p[i] = str[i];
        len = len + 1;
    }
    p[len] = '\0';
    shift = 0;
    for (i = 0; i < len; i = i + 1) {
        if (p[i] == c) {
            shift = i;
            break;
        }
    }
    for (i = shift; i > 0; i = i - 1) {
        str[i] = str[i - 1];
    }
    str[0] = c;
    return shift;
}

void decode(int pass[100], int size, char sym[100]) {
    char table[27] = "abcdefghijklmnopqrstuvwxyz";
    int i;
    char c;
    int index;
    for (i = 0; i < size; i = i + 1) {
        c = table[pass[i]];
        index = move_to_front(table, c);
        sym[i] = c;
    }
    sym[size] = '\0';
    return;
}

void encode(char sym[100], int size, int pass[100]) {
    char table[27] = "abcdefghijklmnopqrstuvwxyz";
    int i;
    char c;
    for (i = 0; i < size; i = i + 1) {
        c = sym[i];
        pass[i] = move_to_front(table, c);
    }
    return;
}

int check(char sym[100], int size, int pass[100]) {
    int pass2[100];
    char sym2[100];
    int i;
    int val;
    val = 1;
    encode(sym, size, pass2);
    for (i = 0; i < size; i = i + 1) {
        if (pass[i] != pass2[i]) {
            val = 0;
            break;
        }
    }
    decode(pass, size, sym2);
    for (i = 0; i < size; i = i + 1) {
        if (sym[i] != sym2[i]) {
            val = 0;
            break;
        }
    }
    return val;
}
