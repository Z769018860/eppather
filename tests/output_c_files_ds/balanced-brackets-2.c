int check_balanced_brackets(char* s) {
    int balance = 0;
    int i = 0;
    for (i = 0; s[i] != '\0'; i = i + 1) {
        if (s[i] == '[') {
            balance = balance + 1;
        } else {
            balance = balance - 1;
        }
        if (balance < 0) {
            return 0;
        }
    }
    if (balance == 0) {
        return 1;
    } else {
        return 0;
    }
}
