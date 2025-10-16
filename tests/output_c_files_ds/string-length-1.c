int func() {
    char string[13] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'w', 'o', 'r', 'l', 'd', '!'};
    int length = 0;
    for (int i = 0; i < 13; i = i + 1) {
        if (string[i] != 0) {
            length = length + 1;
        }
    }
    return;
}
