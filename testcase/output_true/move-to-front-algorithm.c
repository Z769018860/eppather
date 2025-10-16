int move_to_front(char str[100], char c) {
    char p[100];
    int shift = 0;
    int i = 0;
    for (i = 0; i < 100; i = i + 1) {
        p[i] = str[i];
        if (str[i] == 0) {
            break;
        }
    }
    for (i = 0; i < 100; i = i + 1) {
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

void decode(int pass[5], int size, char sym[5]) {
    char table[27] = "abcdefghijklmnopqrstuvwxyz";
    int i = 0;
    int index = 0;
    char c = 0;
    for (i = 0; i < size; i = i + 1) {
        c = table[pass[i]];
        index = move_to_front(table, c);
        sym[i] = c;
    }
    sym[size] = 0;
    return;
}

void encode(char sym[5], int size, int pass[5]) {
    char table[27] = "abcdefghijklmnopqrstuvwxyz";
    int i = 0;
    char c = 0;
    for (i = 0; i < size; i = i + 1) {
        c = sym[i];
        pass[i] = move_to_front(table, c);
    }
    return;
}

int check(char sym[5], int size, int pass[5]) {
    int pass2[5];
    char sym2[5];
    int i = 0;
    int val = 1;
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
