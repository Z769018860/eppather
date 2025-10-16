int check_balanced_brackets(char* s) {
    int balance[5] = {0};
    balance[0] = 0;
    for (int i = 0; s[i] != '\0'; i = i + 1) {
        if (s[i] == '[') {
            balance[0] = balance[0] + 1;
        } else if (s[i] == ']') {
            balance[0] = balance[0] - 1;
        }
        if (balance[0] < 0) {
            return 0;
        }
    }
    if (balance[0] == 0) {
        return 1;
    } else {
        return 0;
    }
    return;
}
